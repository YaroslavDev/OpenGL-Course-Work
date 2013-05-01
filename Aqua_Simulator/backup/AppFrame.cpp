#include "AppFrame.h"

AppFrame::AppFrame( wxWindow* parent )
:
BaseFrame( parent )
{
	::wxTopLevelWindow::Maximize();
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



wxStatusBar* AppFrame::getStatusBar() const
{
	return m_statusBar1;
}

AppGLCanvas* AppFrame::getGLCanvas() const


{
	return frameCanvas;
}

