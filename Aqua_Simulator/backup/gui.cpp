///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

BaseFrame::BaseFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	file = new wxMenu();
	wxMenuItem* open;
	open = new wxMenuItem( file, ID_OPEN, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( open );
	
	wxMenuItem* saveAs;
	saveAs = new wxMenuItem( file, ID_SAVE_AS, wxString( wxT("Save As") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( saveAs );
	
	wxMenuItem* save;
	save = new wxMenuItem( file, ID_SAVE, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( save );
	
	file->AppendSeparator();
	
	wxMenuItem* exit;
	exit = new wxMenuItem( file, ID_EXIT, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	file->Append( exit );
	
	m_menubar1->Append( file, wxT("File") ); 
	
	tools = new wxMenu();
	wxMenuItem* hammer;
	hammer = new wxMenuItem( tools, ID_HAMMER, wxString( wxT("Hammer") ) , wxEmptyString, wxITEM_NORMAL );
	tools->Append( hammer );
	
	wxMenuItem* spanner;
	spanner = new wxMenuItem( tools, ID_SPANNER, wxString( wxT("Spanner") ) , wxEmptyString, wxITEM_NORMAL );
	tools->Append( spanner );
	
	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( tools, wxID_ANY, wxString( wxT("Load Mesh") ) , wxEmptyString, wxITEM_NORMAL );
	tools->Append( m_menuItem7 );
	
	m_menubar1->Append( tools, wxT("Tools") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_panel2 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer5->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText7 = new wxStaticText( m_panel1, wxID_ANY, wxT("Aquatic Surface Menu"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer6->Add( m_staticText7, 0, wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( m_panel1, wxID_ANY, wxT("Current Wave"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer7->Add( m_staticText8, 0, wxALL, 5 );
	
	m_comboBox2 = new wxComboBox( m_panel1, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox2->Append( wxT("1") );
	m_comboBox2->Append( wxT("2") );
	m_comboBox2->Append( wxT("3") );
	m_comboBox2->Append( wxT("4") );
	m_comboBox2->Append( wxT("5") );
	m_comboBox2->SetSelection( 0 );
	fgSizer7->Add( m_comboBox2, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel1, wxID_ANY, wxT("IsActive"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer7->Add( m_staticText10, 0, wxALL, 5 );
	
	m_checkBox1 = new wxCheckBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer7->Add( m_checkBox1, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( m_panel1, wxID_ANY, wxT("Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer7->Add( m_staticText9, 0, wxALL, 5 );

	m_spinCtrlDouble1 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble1, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, wxT("Amplitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer7->Add( m_staticText11, 0, wxALL, 5 );

	m_spinCtrlDouble2 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble2, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( m_panel1, wxID_ANY, wxT("Angular wave number"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer7->Add( m_staticText12, 0, wxALL, 5 );
	
	m_spinCtrlDouble3 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble3, 0, wxALL, 5 );

	m_staticText13 = new wxStaticText( m_panel1, wxID_ANY, wxT("Phase"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer7->Add( m_staticText13, 0, wxALL, 5 );

	m_spinCtrlDouble4 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble4, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( m_panel1, wxID_ANY, wxT("Position_X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer7->Add( m_staticText19, 0, wxALL, 5 );
	
	m_spinCtrlDouble5 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble5, 0, wxALL, 5 );

	m_staticText20 = new wxStaticText( m_panel1, wxID_ANY, wxT("Position_Z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer7->Add( m_staticText20, 0, wxALL, 5 );

	m_spinCtrlDouble6 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer7->Add( m_spinCtrlDouble6, 0, wxALL, 5 );
	
	
	bSizer6->Add( fgSizer7, 1, wxEXPAND, 5 );
	
	m_staticText25 = new wxStaticText( m_panel1, wxID_ANY, wxT("Light Menu"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer6->Add( m_staticText25, 0, wxALL, 5 );
	
	m_staticline4 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText26 = new wxStaticText( m_panel1, wxID_ANY, wxT("Pos X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer3->Add( m_staticText26, 0, wxALL, 5 );

	m_spinCtrlDouble7 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer3->Add( m_spinCtrlDouble7, 0, wxALL, 5 );
	
	m_staticText27 = new wxStaticText( m_panel1, wxID_ANY, wxT("Pos Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer3->Add( m_staticText27, 0, wxALL, 5 );

	m_spinCtrlDouble8 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer3->Add( m_spinCtrlDouble8, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( m_panel1, wxID_ANY, wxT("Pos Z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer3->Add( m_staticText28, 0, wxALL, 5 );

	m_spinCtrlDouble9 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0, 0.5 );
	fgSizer3->Add( m_spinCtrlDouble9, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( m_panel1, wxID_ANY, wxT("Intensity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer3->Add( m_staticText29, 0, wxALL, 5 );
	
	m_spinCtrl8 = new wxSpinCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( m_spinCtrl8, 0, wxALL, 5 );
	
	
	bSizer6->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer6, 0, wxALIGN_RIGHT|wxEXPAND, 1 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText21 = new wxStaticText( m_panel1, wxID_ANY, wxT("Light Menu"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer4->Add( m_staticText21, 0, wxALL, 5 );
	
	m_staticline3 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline3, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText22 = new wxStaticText( m_panel1, wxID_ANY, wxT("Position X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel1, wxID_ANY, wxT("Position Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( m_panel1, wxID_ANY, wxT("Position Z"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer2->Add( m_staticText24, 0, wxALL, 5 );
	
	
	bSizer4->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BaseFrame::onLoadMeshClicked ) );
}

BaseFrame::~BaseFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( BaseFrame::onLoadMeshClicked ) );
	
}
