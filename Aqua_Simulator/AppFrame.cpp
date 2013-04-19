#include "AppFrame.h"

AppFrame::AppFrame( wxWindow* parent )
:
BaseFrame( parent )
{
	wxSize canvasSize = m_panel2->GetSize();
	frameCanvas = new AppGLCanvas(m_panel2, canvasSize);
}

void AppFrame::onLoadMeshClicked( wxCommandEvent& event )
{
	wxFileDialog fileDlg(this, "Selec OBJ file", "", "", 
		"OBJ Files (*.obj)|*.obj", wxFD_OPEN|wxFD_FILE_MUST_EXIST);;
	
	if( fileDlg.ShowModal() == wxID_CANCEL )
		return;

	wxString filepath = fileDlg.GetPath();
	frameCanvas->getGLContext()->reloadMesh(filepath.c_str());
}

void AppFrame::OnModulationColorChanged( wxColourPickerEvent& event )
{
	wxColour color = event.GetColour();
	frameCanvas->getGLContext()->setModulationColor(color.Red()/255.0f,
													color.Green()/255.0f,
													color.Blue()/255.0f,
													color.Alpha()/255.0f);
}


wxStatusBar* AppFrame::getStatusBar() const

{
	return m_statusBar1;
}

AppGLCanvas* AppFrame::getGLCanvas() const

{
	return frameCanvas;
}
