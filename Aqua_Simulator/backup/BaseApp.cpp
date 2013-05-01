#include "Util.h"

#include "BaseApp.h"
#include "AppFrame.h"

IMPLEMENT_APP(BaseApp)

bool BaseApp::OnInit()
{
	if( !wxApp::OnInit() )
		return false;

	AppFrame *mainframe = new AppFrame(NULL);

	glContext = new AppGLContext(mainframe->getGLCanvas());
	glContext->SetCurrent(*mainframe->getGLCanvas());
	glContext->setAppFrame(mainframe);
	mainframe->getGLCanvas()->setGLContext(glContext);

	mainframe->Show();

	return true;
}

int BaseApp::OnExit()
{
	SAFE_DELETE(glContext);

	return wxApp::OnExit();
}

AppGLContext& BaseApp::GetContext(wxGLCanvas	*canvas)
{
	if ( !glContext )
    {
        // Create the OpenGL context for the first window which needs it:
        // subsequently created windows will all share the same context.
        glContext = new AppGLContext(canvas);
    }

    glContext->SetCurrent(*canvas);

    return *glContext;
}