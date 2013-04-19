#ifndef APPGLCANVAS_H
#define APPGLCANVAS_H

#include "Util.h"

class AppGLContext;

class AppGLCanvas : public wxGLCanvas
{
public:
	AppGLCanvas(wxWindow *parent, wxSize size);

	void setGLContext(AppGLContext*	glContext);
	AppGLContext* getGLContext() const;
private:
	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnSpinTimer(wxTimerEvent& WXUNUSED(event));
	void OnMouseEvent(wxMouseEvent &e);

	wxTimer			connectTimer;
	wxStopWatch		deltaTimer;

	AppGLContext	*glContext;

	DECLARE_EVENT_TABLE()
};

#endif //APPGLCANVAS_H