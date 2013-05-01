//--------------------------------------------------------------------------------------
// File: MeshLoader.cpp
//
// Wrapper class for ID3DXMesh interface. Handles loading mesh data from an .obj file
// and resource management for material textures.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma warning(disable: 4995)
#include "mesh.h"
#pragma warning(default: 4995)

//--------------------------------------------------------------------------------------
CMesh::CMesh()
	: prog(NULL)
{
	meshHandle = NULL;

	rawVerts = NULL;
	rawIndices = NULL;
	rawNorms = NULL;
	rawTexCoords = NULL;

    ZeroMemory( m_strMediaDir, sizeof( m_strMediaDir ) );

	world = glm::mat4(1.0f);
	lightpos = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}


//--------------------------------------------------------------------------------------
CMesh::~CMesh()
{
    Destroy();
}


//--------------------------------------------------------------------------------------
void CMesh::Destroy()
{
	for( int iMaterial = 0; iMaterial < m_Materials.size(); iMaterial++ )
    {
		Material* pMaterial = m_Materials.at( iMaterial );

        // Avoid releasing the same texture twice
		for( int x = iMaterial + 1; x < m_Materials.size(); x++ )
        {
			Material* pCur = m_Materials.at( x );
			if( pCur->tex == pMaterial->tex)
				pCur->tex = 0;
        }

        SAFE_DELETE( pMaterial );
    }

	m_Materials.clear();
    m_Vertices.clear();
    m_Indices.clear();
    m_Attributes.clear();
	DeleteCache();

	SAFE_DELETE_ARRAY(rawVerts);
	SAFE_DELETE_ARRAY(rawIndices);
	SAFE_DELETE_ARRAY(rawNorms);
	SAFE_DELETE_ARRAY(rawTexCoords);
}


//--------------------------------------------------------------------------------------
int CMesh::Create( const char* strFilename )
{
    // Start clean
    Destroy();

    // Load the vertex buffer, index buffer, and subset information from a file. In this case, 
    // an .obj file was chosen for simplicity, but it's meant to illustrate that ID3DXMesh objects
    // can be filled from any mesh file format once the necessary data is extracted from file.
    if( LoadGeometryFromOBJ( strFilename ) )
		return 1;

    // Load material textures
	for( int iMaterial = 0; iMaterial < m_Materials.size(); iMaterial++ )
    {
		Material* pMaterial = m_Materials.at( iMaterial );
		if( !pMaterial->strTexture.empty() )
        {
            // Avoid loading the same texture twice
            bool bFound = false;
            for( int x = 0; x < iMaterial; x++ )
            {
                Material* pCur = m_Materials.at( x );
				if( pCur->strTexture.compare(pMaterial->strTexture) == 0 )
                {
                    bFound = true;
					pMaterial->tex = pCur->tex;
                    break;
                }
            }

            // Not found, load the texture
            if( !bFound )
            {
				pMaterial->tex->LoadFromFile( pMaterial->strTexture );
            }
        }
    }

	//Load raw vertex data
	rawVerts = new float[3*m_Vertices.size()];
	for(int i=0; i<m_Vertices.size(); i++)
	{
		rawVerts[3*i+0] = m_Vertices.at(i).position.x;
		rawVerts[3*i+1] = m_Vertices.at(i).position.y;
		rawVerts[3*i+2] = m_Vertices.at(i).position.z;
	}
	//Load raw index data
	rawIndices = new GLuint[m_Indices.size()];
	for(int i=0; i<m_Indices.size(); i++)
	{
		rawIndices[i] = m_Indices.at(i);
	}
	//Load raw normals data
	rawNorms = new float[3*m_Vertices.size()];
	for(int i=0; i<m_Vertices.size(); i++)
	{
		rawNorms[3*i+0] = m_Vertices.at(i).normal.x;
		rawNorms[3*i+1] = m_Vertices.at(i).normal.y;
		rawNorms[3*i+2] = m_Vertices.at(i).normal.z;
	}
	//Load raw texture coordinates data
	rawTexCoords = new float[2*m_Vertices.size()];
	for(int i=0; i<m_Vertices.size(); i++)
	{
		rawTexCoords[2*i+0] = m_Vertices.at(i).texcoord.x;
		rawTexCoords[2*i+1] = m_Vertices.at(i).texcoord.y;
	}

	glGenVertexArrays( 1, &meshHandle );
    glBindVertexArray(meshHandle);

    unsigned int handle[4];
    glGenBuffers(4, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * 3 * sizeof(float), rawVerts, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * 3 * sizeof(float), rawNorms, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // Vertex normal

    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * 2 * sizeof(float), rawTexCoords, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // texture coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), rawIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return 0;
}


//--------------------------------------------------------------------------------------
int CMesh::LoadGeometryFromOBJ( const char* strFileName )
{
	std::string strMaterialFilename;
    // Create temporary storage for the input data. Once the data has been loaded into
    // a reasonable format we can create a D3DXMesh object and load it with the mesh data.
	std::vector <glm::vec3> Positions;
    std::vector <glm::vec2> TexCoords;
    std::vector <glm::vec3> Normals;

    // The first subset uses the default material
    Material* pMaterial = new Material();
    if( pMaterial == NULL )
        return 1;

    InitMaterial( pMaterial );
    strcpy_s( pMaterial->strName, MAX_PATH - 1, "default" );
	m_Materials.push_back( pMaterial );

    DWORD dwCurSubset = 0;

    // File input
    char strCommand[256] = {0};
    std::ifstream InFile( strFileName );
    if( !InFile )
	{
		wxLogError("Can't open input file!");
		return 1;
	}

    for(; ; )
    {
        InFile >> strCommand;
        if( !InFile )
            break;

        if( 0 == strcmp( strCommand, "#" ) )
        {
            // Comment
        }
        else if( 0 == strcmp( strCommand, "v" ) )
        {
            // Vertex Position
            float x, y, z;
            InFile >> x >> y >> z;
			Positions.push_back( glm::vec3( x, y, z ) );
        }
        else if( 0 == strcmp( strCommand, "vt" ) )
        {
            // Vertex TexCoord
            float u, v;
            InFile >> u >> v;
			TexCoords.push_back( glm::vec2( u, v ) );
        }
        else if( 0 == strcmp( strCommand, "vn" ) )
        {
            // Vertex Normal
            float x, y, z;
            InFile >> x >> y >> z;
			Normals.push_back( glm::vec3( x, y, z ) );
        }
        else if( 0 == strcmp( strCommand, "f" ) )
        {
            // Face
            UINT iPosition, iTexCoord, iNormal;
            VERTEX vertex;

            for( UINT iFace = 0; iFace < 3; iFace++ )
            {
                ZeroMemory( &vertex, sizeof( VERTEX ) );

                // OBJ format uses 1-based arrays
                InFile >> iPosition;
                vertex.position = Positions[ iPosition - 1 ];

                if( '/' == InFile.peek() )
                {
                    InFile.ignore();

                    if( '/' != InFile.peek() )
                    {
                        // Optional texture coordinate
                        InFile >> iTexCoord;
                        vertex.texcoord = TexCoords[ iTexCoord - 1 ];
                    }

                    if( '/' == InFile.peek() )
                    {
                        InFile.ignore();

                        // Optional vertex normal
                        InFile >> iNormal;
                        vertex.normal = Normals[ iNormal - 1 ];
                    }
                }

                // If a duplicate vertex doesn't exist, add this vertex to the Vertices
                // list. Store the index in the Indices array. The Vertices and Indices
                // lists will eventually become the Vertex Buffer and Index Buffer for
                // the mesh.
                DWORD index = AddVertex( iPosition, &vertex );
                if ( index == (DWORD)-1 )
                    return 1;

                m_Indices.push_back( index );
            }
			m_Attributes.push_back( dwCurSubset );
        }
        else if( 0 == strcmp( strCommand, "mtllib" ) )
        {
            // Material library
            InFile >> strMaterialFilename;
        }
        else if( 0 == strcmp( strCommand, "usemtl" ) )
        {
            // Material
            char strName[MAX_PATH] = {0};
            InFile >> strName;

            bool bFound = false;
			for( int iMaterial = 0; iMaterial < m_Materials.size(); iMaterial++ )
            {
                Material* pCurMaterial = m_Materials.at( iMaterial );
                if( 0 == strcmp( pCurMaterial->strName, strName ) )
                {
                    bFound = true;
                    dwCurSubset = iMaterial;
                    break;
                }
            }

            if( !bFound )
            {
                pMaterial = new Material();
                if( pMaterial == NULL )
                    return 1;

				dwCurSubset = m_Materials.size();

                InitMaterial( pMaterial );
                strcpy_s( pMaterial->strName, MAX_PATH - 1, strName );

				m_Materials.push_back( pMaterial );
            }
        }
        else
        {
            // Unimplemented or unrecognized command
        }

        InFile.ignore( 1000, '\n' );
    }

    // Cleanup
    InFile.close();
    DeleteCache();

    // If an associated material file was found, read that in as well.
    if( strMaterialFilename[0] )
    {
		if( LoadMaterialsFromMTL( strMaterialFilename.c_str() ) )
			return 1; //error
    }

    return 0;
}


//--------------------------------------------------------------------------------------
DWORD CMesh::AddVertex( UINT hash, VERTEX* pVertex )
{
    // If this vertex doesn't already exist in the Vertices list, create a new entry.
    // Add the index of the vertex to the Indices list.
    bool bFoundInList = false;
    DWORD index = 0;

    // Since it's very slow to check every element in the vertex list, a hashtable stores
    // vertex indices according to the vertex position's index as reported by the OBJ file
	if( ( UINT )m_VertexCache.size() > hash )
    {
		CacheEntry* pEntry = m_VertexCache.at( hash );
        while( pEntry != NULL )
        {
			VERTEX* pCacheVertex = m_Vertices.data() + pEntry->index;

            // If this vertex is identical to the vertex already in the list, simply
            // point the index buffer to the existing vertex
            if( 0 == memcmp( pVertex, pCacheVertex, sizeof( VERTEX ) ) )
            {
                bFoundInList = true;
                index = pEntry->index;
                break;
            }

            pEntry = pEntry->pNext;
        }
    }

    // Vertex was not found in the list. Create a new entry, both within the Vertices list
    // and also within the hashtable cache
    if( !bFoundInList )
    {
        // Add to the Vertices list
        index = m_Vertices.size();
		m_Vertices.push_back( *pVertex );

        // Add this to the hashtable
        CacheEntry* pNewEntry = new CacheEntry;
        if( pNewEntry == NULL )
            return (DWORD)-1;

        pNewEntry->index = index;
        pNewEntry->pNext = NULL;

        // Grow the cache if needed
		while( ( UINT )m_VertexCache.size() <= hash )
        {
			m_VertexCache.push_back( NULL );
        }

        // Add to the end of the linked list
        CacheEntry* pCurEntry = m_VertexCache.at( hash );
        if( pCurEntry == NULL )
        {
            // This is the head element
			m_VertexCache.at( hash ) = pNewEntry;
        }
        else
        {
            // Find the tail
            while( pCurEntry->pNext != NULL )
            {
                pCurEntry = pCurEntry->pNext;
            }

            pCurEntry->pNext = pNewEntry;
        }
    }

    return index;
}


//--------------------------------------------------------------------------------------
void CMesh::DeleteCache()
{
    // Iterate through all the elements in the cache and subsequent linked lists
    for( int i = 0; i < m_VertexCache.size(); i++ )
    {
        CacheEntry* pEntry = m_VertexCache.at( i );
        while( pEntry != NULL )
        {
            CacheEntry* pNext = pEntry->pNext;
            SAFE_DELETE( pEntry );
            pEntry = pNext;
        }
    }

    m_VertexCache.clear();
}


//--------------------------------------------------------------------------------------
int CMesh::LoadMaterialsFromMTL( const char* strFileName )
{
    // File input
    char strCommand[256] = {0};
    std::ifstream InFile( strFileName );
    if( !InFile )
	{
		wxLogError("Can't open input file!");
		return 1;
	}

    Material* pMaterial = NULL;

    for(; ; )
    {
        InFile >> strCommand;
        if( !InFile )
            break;

        if( 0 == strcmp( strCommand, "newmtl" ) )
        {
            // Switching active materials
            char strName[MAX_PATH] = {0};
            InFile >> strName;

            pMaterial = NULL;
            for( int i = 0; i < m_Materials.size(); i++ )
            {
                Material* pCurMaterial = m_Materials.at( i );
                if( 0 == strcmp( pCurMaterial->strName, strName ) )
                {
                    pMaterial = pCurMaterial;
                    break;
                }
            }
        }

        // The rest of the commands rely on an active material
        if( pMaterial == NULL )
            continue;

        if( 0 == strcmp( strCommand, "#" ) )
        {
            // Comment
        }
        else if( 0 == strcmp( strCommand, "Ka" ) )
        {
            // Ambient color
            float r, g, b;
            InFile >> r >> g >> b;
			pMaterial->vAmbient = glm::vec3( r, g, b );
        }
        else if( 0 == strcmp( strCommand, "Kd" ) )
        {
            // Diffuse color
            float r, g, b;
            InFile >> r >> g >> b;
			pMaterial->vDiffuse = glm::vec3( r, g, b );
        }
        else if( 0 == strcmp( strCommand, "Ks" ) )
        {
            // Specular color
            float r, g, b;
            InFile >> r >> g >> b;
            pMaterial->vSpecular = glm::vec3( r, g, b );
        }
        else if( 0 == strcmp( strCommand, "d" ) ||
                 0 == strcmp( strCommand, "Tr" ) )
        {
            // Alpha
            InFile >> pMaterial->fAlpha;
        }
        else if( 0 == strcmp( strCommand, "Ns" ) )
        {
            // Shininess
            int nShininess;
            InFile >> nShininess;
            pMaterial->nShininess = nShininess;
        }
        else if( 0 == strcmp( strCommand, "illum" ) )
        {
            // Specular on/off
            int illumination;
            InFile >> illumination;
            pMaterial->bSpecular = ( illumination == 2 );
        }
        else if( 0 == strcmp( strCommand, "map_Kd" ) )
        {
            // Texture
            InFile >> pMaterial->strTexture;
        }

        else
        {
            // Unimplemented or unrecognized command
        }

        InFile.ignore( 1000, L'\n' );
    }

    InFile.close();

    return 0;
}


//--------------------------------------------------------------------------------------
void CMesh::InitMaterial( Material* pMaterial )
{
	pMaterial->vAmbient = glm::vec3( 0.2f, 0.2f, 0.2f );
    pMaterial->vDiffuse = glm::vec3( 0.8f, 0.8f, 0.8f );
    pMaterial->vSpecular = glm::vec3( 1.0f, 1.0f, 1.0f );
    pMaterial->nShininess = 0;
    pMaterial->fAlpha = 1.0f;
    pMaterial->bSpecular = false;
}

void CMesh::Render()
{
	if( prog )
	{
		prog->use();

		glActiveTexture(GL_TEXTURE0);
		UINT lastMaterial = GetNumMaterials()-1;
		glBindTexture(GL_TEXTURE_2D, GetMaterial(lastMaterial)->tex->GetTextureHandle());   
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		prog->setUniform("Tex1", 0);
	
		prog->setUniform("Light.Intensity", vec3(1.0f, 1.0f, 1.0f));
		prog->setUniform("Light.Position", lightpos );
		prog->setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
		prog->setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
		prog->setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
		prog->setUniform("Material.Shininess", 100.0f);

		mat4 mv = view * world;
		prog->setUniform("ModelViewMatrix", mv);
		prog->setUniform("NormalMatrix", mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
		prog->setUniform("MVP", proj * mv);
	}

	glBindVertexArray(meshHandle);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}

void CMesh::setLightPos(const glm::vec4& lpos)
{
	lightpos = lpos;
}