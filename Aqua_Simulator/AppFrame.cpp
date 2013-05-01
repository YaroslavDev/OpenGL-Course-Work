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

//Aqua menu callbacks
void AppFrame::onCurrentWaveChanged( wxCommandEvent& event )
{
	int currentWave = event.GetInt();
	frameCanvas->getGLContext()->updateAppFrame(currentWave);
}

void AppFrame::onIsActiveChecked( wxCommandEvent& event )
{
	int val = event.GetInt();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWaveActive(index-1, val);
	}
}
void AppFrame::onFrequencyChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWaveFrequency(index-1, val);
	}
}
void AppFrame::onAmplitudeChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWaveAmplitude(index-1, val);
	}
}
void AppFrame::onAngularNumberChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWaveAngularNumber(index-1, val);
	}
}
void AppFrame::onPhaseChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWavePhase(index-1, val);
	}
}
void AppFrame::onWavePosXChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWavePosX(index-1, val);
	}
}
void AppFrame::onWavePosZChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	wxString str = this->m_comboBox2->GetValue();	//get current wave
	unsigned long index = -1;
	if( str.ToULong(&index) )
	{
		frameCanvas->getGLContext()->setWavePosZ(index-1, val);
	}
}
//Light menu callbacks
void AppFrame::onLightPosXChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	frameCanvas->getGLContext()->setLightPosX(val);
}
void AppFrame::onLightPosYChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	frameCanvas->getGLContext()->setLightPosY(val);
}
void AppFrame::onLightPosZChanged( wxSpinDoubleEvent& event )
{
	double val = event.GetValue();
	frameCanvas->getGLContext()->setLightPosZ(val);
}
void AppFrame::onSpinCtrlValueChanged( wxSpinEvent& event )
{
}

void AppFrame::setIsActiveCheckBox(int isactive)
{
	this->m_checkBox1->SetValue(isactive);
}
void AppFrame::setFrequencySpin(double val)
{
	this->m_spinCtrlDouble1->SetValue(val);
}
void AppFrame::setAmplitudeSpin(double val)
{
	this->m_spinCtrlDouble2->SetValue(val);
}
void AppFrame::setAngularWaveSpin(double val)
{
	this->m_spinCtrlDouble3->SetValue(val);
}
void AppFrame::setPhaseSpin(double val)
{
	this->m_spinCtrlDouble4->SetValue(val);
}
void AppFrame::setWavePosXSpin(double val)
{
	this->m_spinCtrlDouble5->SetValue(val);
}
void AppFrame::setWavePosZSpin(double val)
{
	this->m_spinCtrlDouble6->SetValue(val);
}

void AppFrame::setLightPosXSpin(double val)
{
	this->m_spinCtrlDouble7->SetValue(val);
}
void AppFrame::setLightPosYSpin(double val)
{
	this->m_spinCtrlDouble8->SetValue(val);
}
void AppFrame::setLightPosZSpin(double val)
{
	this->m_spinCtrlDouble9->SetValue(val);
}