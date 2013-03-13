#include "videoctrlpopup.h"
#include "cmainframe.h"

VideoCtrlPopup::VideoCtrlPopup(wxWindow* parent) : VideoCtrlPopupBase(parent) {
	m_mainframe = dynamic_cast<CMainFrame*>(parent);
}

VideoCtrlPopup::~VideoCtrlPopup() {
}

void VideoCtrlPopup::OnFullVideoToggle(wxCommandEvent& event) {
	m_mainframe->ToggleScreen();
}

void VideoCtrlPopup::OnNext(wxCommandEvent& event) {
	wxCommandEvent e(wxEVT_COMMAND_BUTTON_CLICKED); 	
	m_mainframe->OnNext(e);
}

void VideoCtrlPopup::OnPlayPause(wxCommandEvent& event) {
	wxCommandEvent e(wxEVT_COMMAND_BUTTON_CLICKED); 	
	m_mainframe->OnPlayPause(e);
}

void VideoCtrlPopup::OnPositionChanged(wxScrollEvent& event) {		
	//sync the two handles 
	m_mainframe->m_mediaPosition->SetValue(m_positionctrl->GetValue());
	
	wxCommandEvent e(wxEVT_COMMAND_SLIDER_UPDATED); 	
	e.SetInt(m_positionctrl->GetValue()); 
	m_mainframe->OnMediaSliderMoved(e);
}

void VideoCtrlPopup::OnPrevious(wxCommandEvent& event) {
	wxCommandEvent e(wxEVT_COMMAND_BUTTON_CLICKED); 	
	m_mainframe->OnPrevious(e);
}

void VideoCtrlPopup::OnStop(wxCommandEvent& event) {
	wxCommandEvent e(wxEVT_COMMAND_BUTTON_CLICKED); 	
	m_mainframe->OnStop(e);
}

void VideoCtrlPopup::OnLeaveWindow(wxMouseEvent& event)
{
	event.Skip();
}

void VideoCtrlPopup::OnVolumeChanged(wxScrollEvent& event)
{
	//sync the two handles
	m_mainframe->m_volumeSlider->SetValue(m_volumeCtrl->GetValue());
	
	wxCommandEvent e(wxEVT_COMMAND_SLIDER_UPDATED);  
	m_mainframe->OnVolumeChanging(e); 
}
