#ifndef BASEAPP_H
#define BASEAPP_H

#include "AppGLContext.h"

class BaseApp : public wxApp
{
public:
	BaseApp() : glContext(NULL) {}

	AppGLContext& GetContext(wxGLCanvas	*canvas);

	virtual bool OnInit();
	virtual int OnExit();
private:
	AppGLContext	*glContext;
};

#endif //BASEAPP_H