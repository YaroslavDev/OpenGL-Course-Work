#include "BaseApp.h"
#include "AppGLCanvas.h"

// ----------------------------------------------------------------------------
// AppGLCanvas
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(AppGLCanvas, wxGLCanvas)
    EVT_PAINT(AppGLCanvas::OnPaint)
    EVT_KEY_DOWN(AppGLCanvas::OnKeyDown)
    EVT_TIMER(SpinTimer, AppGLCanvas::OnSpinTimer)
	EVT_MOUSE_EVENTS(AppGLCanvas::OnMouseEvent)
END_EVENT_TABLE()

AppGLCanvas::AppGLCanvas(wxWindow *parent, wxSize size)
	: wxGLCanvas(parent, wxID_ANY, NULL /* attribs */,
                 wxDefaultPosition, size,
                 wxFULL_REPAINT_ON_RESIZE),
	connectTimer(this, SpinTimer),
	glContext(NULL)
{
	connectTimer.Start(16);
	deltaTimer.Start();
}

void AppGLCanvas::setGLContext(AppGLContext*	context)
{
	glContext = context;
}

AppGLContext* AppGLCanvas::getGLContext() const
{
	return glContext;
}

void AppGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);

    // Set the OpenGL viewport according to the client size of this canvas.
    // This is done here rather than in a wxSizeEvent handler because our
    // OpenGL rendering context (and thus viewport setting) is used with
    // multiple canvases: If we updated the viewport in the wxSizeEvent
    // handler, changing the size of one canvas causes a viewport setting that
    // is wrong when next another canvas is repainted.
    //const wxSize ClientSize = GetClientSize();
	const wxSize ClientSize = GetParent()->GetSize();
    SetSize(ClientSize);
	glViewport(0, 0, ClientSize.x, ClientSize.y);


    // Render the graphics and swap the buffers.
	if( glContext )
	{
		glContext->setProjectionMatrix(60.0f, static_cast<float>(ClientSize.x)/ClientSize.y, 0.1f, 100.f);
		glContext->render();
	}

    SwapBuffers();
}

void AppGLCanvas::OnKeyDown(wxKeyEvent& event)
{
    float angle = 5.0;
    switch( event.GetKeyCode() )
    {
        //case WXK_RIGHT:
        //Parse keyboard input
        default:
            event.Skip();
            return;
    }
}

void AppGLCanvas::OnMouseEvent(wxMouseEvent &e)
{
	
}

void AppGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
	int ms_dt = deltaTimer.Time();
	float dt = (float)ms_dt / 1000.0f;
	deltaTimer.Start(0);
	if( glContext )
	{
		glContext->update(dt);
	}
	Refresh(false);
}