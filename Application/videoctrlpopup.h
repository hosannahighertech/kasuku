#ifndef VIDEOCTRLPOPUP_H
#define VIDEOCTRLPOPUP_H

#include "popupctrls_file.h"

class CMainFrame;

class VideoCtrlPopup : public VideoCtrlPopupBase {
public:
	VideoCtrlPopup(wxWindow* parent);
	virtual ~VideoCtrlPopup();
	
	friend class CMainFrame;
	
protected:
	virtual void OnFullVideoToggle(wxCommandEvent& event);
	virtual void OnNext(wxCommandEvent& event);
	virtual void OnPlayPause(wxCommandEvent& event);
	virtual void OnPositionChanged(wxScrollEvent& event);
	virtual void OnPrevious(wxCommandEvent& event);
	virtual void OnStop(wxCommandEvent& event);
	virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnVolumeChanged(wxScrollEvent& event);
	
	CMainFrame* m_mainframe;
	
};
#endif // VIDEOCTRLPOPUP_H
