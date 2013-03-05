#ifndef __cmainframe__
#define __cmainframe__

/**
@file
Subclass of CMainFrameBase, which is generated by wxFormBuilder.
*/

#include "cmainframebase.h"

//// end generated include

#include <climits>
#include <vlc/vlc.h>
#include <wx/dirdlg.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include "k_splash.h"


#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif

wxDECLARE_EVENT(KEVT_MEDIA_PLAY_ON_PROGRESS, wxCommandEvent);
wxDECLARE_EVENT(KEVT_MEDIA_PLAY_FINISHED, wxCommandEvent);
wxDECLARE_EVENT(KEVT_MEDIA_LIST_NEXT_ITEM_SET, wxCommandEvent);

#define TIMELINE_MAX (INT_MAX-9)
#define VOLUME_MAX 200
#define MY_APP_VERSION_STRING _("1.0.0")

/** Implementing CMainFrameBase */
class CMainFrame : public CMainFrameBase {
protected:
	// Handlers for CMainFrameBase events.
	void OnMediaDClicked(wxListEvent& event);
	void OnLoadDir(wxCommandEvent& event);
	void OnAboutUs(wxCommandEvent& event);
public:
	/** Constructor */
	CMainFrame(wxWindow* parent);
	//// end generated class members
	~CMainFrame();

private:
	libvlc_instance_t* m_vlcInst;
	libvlc_media_player_t* m_mediaPlayer;
	libvlc_media_t* m_media;
	libvlc_event_manager_t* m_vlcEvtMgr;
	libvlc_media_list_t* m_vlcMediaList;//for auto player without user intervention
	libvlc_media_list_player_t* m_vlcMediaListPlayer;

	void InitBindEvents();
	void InitVLC();

	void OnVideoSizeChanged(wxSizeEvent& e);
	void OnFullVideoView(wxMouseEvent& event);  //Video window double Clicked
	void OnRightClickMenu(wxMouseEvent& event);

	void OnMediaSliderMoved(wxCommandEvent& event);
	void OnPlayPause(wxCommandEvent& event);
	void OnPrevious(wxCommandEvent& event);
	void OnStop(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);

	void OnToggleVideo(wxCommandEvent& event);
	void OnPlayListShowHide(wxCommandEvent& event);
	void OnLoop(wxCommandEvent& event);
	void OnRandom(wxCommandEvent& event);
	void OnVolumeChanging(wxCommandEvent& event) ;

	//internal catcher
	void OnUpdateMediaPosition(wxCommandEvent& e);
	void OnPListItemChanged(wxCommandEvent& e);
	void OnQuitApp(wxCloseEvent& e);

	//hackish but works for video full screen in windows
	void OnEraseBGEventCatcher(wxEraseEvent& event);
	void OnPaintEventCatecher(wxPaintEvent& event);


	void ToggleScreen();
	void PlayMedia(const wxString& path);

	void SetLabels();

	wxString GetLicence();

	libvlc_playback_mode_t m_pbMode;
	bool m_isRandom;

	/*GUI Components*/
	KSplash* m_splash;
};


/*Events from Media Player*/
void CatchMediaEvents(const libvlc_event_t *event, void *data);

#endif // __cmainframe__
