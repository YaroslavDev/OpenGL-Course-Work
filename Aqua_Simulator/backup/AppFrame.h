#ifndef __AppFrame__
#define __AppFrame__

/**
@file
Subclass of BaseFrame, which is generated by wxFormBuilder.
*/

#include "gui.h"
#include "AppGLCanvas.h"
#include "AppGLContext.h"
//// end generated include

class AppGLContext;

/** Implementing BaseFrame */
class AppFrame : public BaseFrame
{
	protected:
		// Handlers for BaseFrame events.
		void onLoadMeshClicked( wxCommandEvent& event );
	public:
		/** Constructor */
		AppFrame( wxWindow* parent );
	//// end generated class members


	//GUI getters
	AppGLCanvas* getGLCanvas() const;
	wxStatusBar* getStatusBar() const;
private:
	AppGLCanvas	*frameCanvas;
};

#endif // __AppFrame__
