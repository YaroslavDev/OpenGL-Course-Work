///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_EXIT 1000

///////////////////////////////////////////////////////////////////////////////
/// Class BaseFrame
///////////////////////////////////////////////////////////////////////////////
class BaseFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* file;
		wxMenu* tools;
		wxStatusBar* m_statusBar1;
		wxPanel* m_panel1;
		wxPanel* m_panel2;
		wxStaticText* m_staticText7;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText8;
		wxComboBox* m_comboBox2;
		wxStaticText* m_staticText10;
		wxCheckBox* m_checkBox1;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxStaticText* m_staticText19;
		wxStaticText* m_staticText20;
		wxStaticText* m_staticText25;
		wxStaticLine* m_staticline4;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText27;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxSpinCtrl* m_spinCtrl2;
		
		//============================
		//Add Double Spin Ctrls manually as long as they are not implemented in wxFormBuilder :(
		wxSpinCtrlDouble* m_spinCtrlDouble1;
		wxSpinCtrlDouble* m_spinCtrlDouble2;
		wxSpinCtrlDouble* m_spinCtrlDouble3;
		wxSpinCtrlDouble* m_spinCtrlDouble4;
		wxSpinCtrlDouble* m_spinCtrlDouble5;
		wxSpinCtrlDouble* m_spinCtrlDouble6;
		wxSpinCtrlDouble* m_spinCtrlDouble7;
		wxSpinCtrlDouble* m_spinCtrlDouble8;
		wxSpinCtrlDouble* m_spinCtrlDouble9;
		//============================

		// Virtual event handlers, overide them in your derived class
		//Menubar callbacks
		virtual void onLoadMeshClicked( wxCommandEvent& event )			{ event.Skip(); }
		//Aqua menu callbacks
		virtual void onCurrentWaveChanged( wxCommandEvent& event )		{ event.Skip(); }
		virtual void onIsActiveChecked( wxCommandEvent& event )			{ event.Skip(); }
		virtual void onFrequencyChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onAmplitudeChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onAngularNumberChanged( wxSpinDoubleEvent& event ) { event.Skip(); }
		virtual void onPhaseChanged( wxSpinDoubleEvent& event )			{ event.Skip(); }
		virtual void onWavePosXChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onWavePosZChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		//Light menu callbacks
		virtual void onLightPosXChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onLightPosYChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onLightPosZChanged( wxSpinDoubleEvent& event )		{ event.Skip(); }
		virtual void onSpinCtrlValueChanged( wxSpinEvent& event )		{ event.Skip(); }
	
	public:
		
		BaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aquatic Surface Simulator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,487 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~BaseFrame();
	
};

#endif //__GUI_H__
