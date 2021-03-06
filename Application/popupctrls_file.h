//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef POPUPCTRLS_FILE_BASE_CLASSES_H
#define POPUPCTRLS_FILE_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/popupwin.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/bmpbuttn.h>

class VideoCtrlPopupBase : public wxPopupWindow
{
protected:
    wxPanel* m_ctrlPanel;
    wxSlider* m_positionctrl;
    wxBitmapButton* m_previousButton;
    wxBitmapButton* m_playPauseButton;
    wxBitmapButton* m_stopButton;
    wxBitmapButton* m_nextButton;
    wxBitmapButton* m_toggleVideoButton;
    wxSlider* m_volumeCtrl;

protected:
    virtual void OnLeaveWindow(wxMouseEvent& event) { event.Skip(); }
    virtual void OnRightClick(wxMouseEvent& event) { event.Skip(); }
    virtual void OnPositionChanged(wxScrollEvent& event) { event.Skip(); }
    virtual void OnPrevious(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPlayPause(wxCommandEvent& event) { event.Skip(); }
    virtual void OnStop(wxCommandEvent& event) { event.Skip(); }
    virtual void OnNext(wxCommandEvent& event) { event.Skip(); }
    virtual void OnFullVideoToggle(wxCommandEvent& event) { event.Skip(); }
    virtual void OnVolumeChanged(wxScrollEvent& event) { event.Skip(); }

public:
    VideoCtrlPopupBase(wxWindow* parent, long style = wxBORDER_NONE);
    virtual ~VideoCtrlPopupBase();
};

#endif
