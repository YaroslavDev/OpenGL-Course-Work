//--------------------------------------------------------------------------------------
// File: MeshLoader.h
//
// Wrapper class for ID3DXMesh interface. Handles loading mesh data from an .obj file
// and resource management for material textures.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef _MESH_H_
#define _MESH_H_
#pragma once

#include "Util.h"


// Used for a hashtable vertex cache when creating the mesh from a .obj file
struct CacheEntry
{
    UINT index;
    CacheEntry* pNext;
};


class CMesh
{
public:
    CMesh();
    ~CMesh();

    int		Create( const char* strFilename );
    void    Destroy();
	void	Render();

    UINT    GetNumMaterials() const
    {
		return m_Materials.size();
    }
    Material* GetMaterial( UINT iMaterial )
    {
        return m_Materials.at( iMaterial );
    }
    char* GetMediaDirectory()
    {
        return m_strMediaDir;
    }

	void	setGLSLProgram(GLSLProgram	*p)
	{
		prog = p;
	}

	void	setViewProj(const glm::mat4& v, const glm::mat4& p)
	{
		view = v;
		proj = p;
	}
	void	setWorld(const glm::mat4& w)
	{
		world = w;
	}
	void	setLightPos(const glm::vec4& lpos);
private:

    int		LoadGeometryFromOBJ( const char* strFilename );
    int		LoadMaterialsFromMTL( const char* strFileName );
    void    InitMaterial( Material* pMaterial );

    DWORD   AddVertex( UINT hash, VERTEX* pVertex );
    void    DeleteCache();

	unsigned int meshHandle;

    std::vector<CacheEntry*> m_VertexCache;		// Hashtable cache for locating duplicate vertices
    std::vector<VERTEX> m_Vertices;				// Filled and copied to the vertex buffer
	float	*rawVerts;
	GLuint	*rawIndices;
	float	*rawNorms;
	float	*rawTexCoords;
    std::vector<DWORD> m_Indices;				// Filled and copied to the index buffer
    std::vector<DWORD> m_Attributes;			// Filled and copied to the attribute buffer
    std::vector<Material*> m_Materials;			// Holds material properties per subset

    char   m_strMediaDir[ MAX_PATH ];			// Directory where the mesh was found
	GLSLProgram	*prog;							// Assign to this mesh GLSL program
	//View Proj data
	glm::mat4 world;
	glm::mat4 view;
	glm::mat4 proj;
	//Light data
	glm::vec4 lightpos;
};

#endif // _MESH_H_

