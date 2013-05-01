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

		//Aqua menu callbacks
		void onCurrentWaveChanged( wxCommandEvent& event );
		void onIsActiveChecked( wxCommandEvent& event );
		void onFrequencyChanged( wxSpinDoubleEvent& event );
		void onAmplitudeChanged( wxSpinDoubleEvent& event );
		void onAngularNumberChanged( wxSpinDoubleEvent& event );
		void onPhaseChanged( wxSpinDoubleEvent& event );
		void onWavePosXChanged( wxSpinDoubleEvent& event );
		void onWavePosZChanged( wxSpinDoubleEvent& event );
		//Light menu callbacks
		void onLightPosXChanged( wxSpinDoubleEvent& event );
		void onLightPosYChanged( wxSpinDoubleEvent& event );
		void onLightPosZChanged( wxSpinDoubleEvent& event );
		void onSpinCtrlValueChanged( wxSpinEvent& event );
	public:
		/** Constructor */
		AppFrame( wxWindow* parent );
	//// end generated class members

		//GUI setters
		void setIsActiveCheckBox(int isactive);
		void setFrequencySpin(double val);
		void setAmplitudeSpin(double val);
		void setAngularWaveSpin(double val);
		void setPhaseSpin(double val);
		void setWavePosXSpin(double val);
		void setWavePosZSpin(double val);

		void setLightPosXSpin(double val);
		void setLightPosYSpin(double val);
		void setLightPosZSpin(double val);
	//GUI getters
	AppGLCanvas* getGLCanvas() const;
	wxStatusBar* getStatusBar() const;
private:
	AppGLCanvas	*frameCanvas;
};

#endif // __AppFrame__
