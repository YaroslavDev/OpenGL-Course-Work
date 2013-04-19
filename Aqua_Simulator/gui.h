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
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/listbox.h>
#include <wx/slider.h>
#include <wx/bmpcbox.h>
#include <wx/clrpicker.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define ID_OPEN 1000
#define ID_SAVE_AS 1001
#define ID_SAVE 1002
#define ID_EXIT 1003
#define ID_HAMMER 1004
#define ID_SPANNER 1005

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
		wxStaticText* m_staticText1;
		wxComboBox* m_comboBox1;
		wxStaticText* m_staticText2;
		wxListBox* m_listBox1;
		wxStaticText* m_staticText3;
		wxSlider* m_slider2;
		wxStaticText* m_staticText5;
		wxBitmapComboBox* m_bcomboBox2;
		wxStaticText* m_staticText51;
		wxColourPickerCtrl* m_colourPicker1;
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onLoadMeshClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnModulationColorChanged( wxColourPickerEvent& event ) { event.Skip(); }
		
	
	public:
		
		BaseFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Aquatic Surface Simulator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 582,487 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~BaseFrame();
	
};

#endif //__GUI_H__
