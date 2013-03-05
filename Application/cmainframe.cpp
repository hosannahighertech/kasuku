#include "cmainframe.h"
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include <wx/textfile.h>
#include <wx/app.h>
#include <wx/sysopt.h>
#include "images.h"
#include "k_config.h"

wxDEFINE_EVENT(KEVT_MEDIA_PLAY_ON_PROGRESS, wxCommandEvent);
wxDEFINE_EVENT(KEVT_MEDIA_PLAY_FINISHED, wxCommandEvent);
wxDEFINE_EVENT(KEVT_MEDIA_LIST_NEXT_ITEM_SET, wxCommandEvent);

CMainFrame::CMainFrame(wxWindow* parent):CMainFrameBase(parent) {
	//splash
	wxBitmap bmpSplash = wxBITMAP_PNG(splash);
	wxIcon appIcon;
	//make icon from bitmap
	appIcon.CopyFromBitmap(wxBITMAP_PNG(aaaaaaaaa));
	//set app icon
	if(appIcon.IsOk())
		SetIcon(appIcon);
	//create and start splash
	m_splash = new KSplash(this, bmpSplash);
	wxYield();
	wxSleep(2); //show our splash at least two secs


	//button Images
	m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));
	m_previousButton->SetBitmap(wxBITMAP_PNG(control_start));
	m_stopButton->SetBitmap(wxBITMAP_PNG(control_stop));
	m_nextButton->SetBitmap(wxBITMAP_PNG(control_end));

	m_toggleVideoButton->SetBitmap(wxBITMAP_PNG(control_fullscreen));
	m_showPlayListButton->SetBitmap(wxBITMAP_PNG(control_panel));
	m_loopButton->SetBitmap(wxBITMAP_PNG(control_repeat));
	//file listctrl
	m_fileList->InsertColumn(0, _("Track"));
	m_fileList->InsertColumn(1, _("Title"));
	m_fileList->InsertColumn(2, _("Artist"));
	m_fileList->InsertColumn(3, _("Album"));
	m_fileList->InsertColumn(4, _("Full Path"));

	//Init controls
	m_mediaPosition->SetRange(0, TIMELINE_MAX);
	m_mediaPosition->SetValue(0);

	m_volumeSlider->SetRange(0, VOLUME_MAX);
	//VLC Stuffs
	InitVLC();
	m_pbMode = libvlc_playback_mode_default;

	InitBindEvents();
	Maximize();

	m_splash->Destroy();//destroy splash and show the app
	
	//system options
	wxSystemOptions::SetOption(wxT("msw.window.no-clip-children"), 1);
	//refresh panel to reflesct new color
	m_displayEventCatcher->Refresh(true);
}

void CMainFrame::OnMediaDClicked(wxListEvent& e) {
	/*wxListItem row_info = e.GetItem();
	wxString path;
	// Set what row it is (m_itemId is a member of the regular wxListCtrl class)
	row_info.m_itemId = e.GetIndex();
	// Set what column of that row we want to query for information.
	row_info.m_col = 3;//full path
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;
	// Get the info and store it in row_info variable.
	m_fileList->GetItem( row_info );
	// Extract the text out that cell
	path = row_info.m_text;

	PlayMedia(path);*/
	//media list add them in opposite way so that first in wxLC is last in media list
	int idx = libvlc_media_list_count(m_vlcMediaList) - e.GetIndex() - 1;//remember its zero indexed list?
	libvlc_media_list_player_play_item_at_index(m_vlcMediaListPlayer, idx);
	libvlc_media_add_option(libvlc_media_player_get_media(m_mediaPlayer), "--audio-visual visualizer --effect-list spectrum");
	wxSleep(1);
	SetLabels();
}

void CMainFrame::OnLoadDir(wxCommandEvent& event) {
	wxDirDialog dlg(NULL, "Choose Media Directory", "",
	                wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if(dlg.ShowModal()!=wxID_OK)
		return ;//user changed idea!

	wxString path = dlg.GetPath();

	wxDir dir(path);
	if(!dir.IsOpened()) {
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		return;
	}

	//clear current Item
	m_fileList->DeleteAllItems();
	libvlc_media_list_player_stop(m_vlcMediaListPlayer);
	for(int i=0; i<libvlc_media_list_count(m_vlcMediaList); i++)
		libvlc_media_list_remove_index(m_vlcMediaList, i);

	wxString filename;
	bool cont = dir.GetFirst(&filename, wxT("*.*"));
	int idx = 0;
	while(cont) {
		if(filename.AfterLast('.').Lower()==wxT("mp3")||filename.AfterLast('.').Lower()==wxT("ogg")
		        ||filename.AfterLast('.').Lower()==wxT("flv")||filename.AfterLast('.').Lower()==wxT("mp4")
		        ||filename.AfterLast('.').Lower()==wxT("mov")||filename.AfterLast('.').Lower()==wxT("wmv")
		  ) {

			//Set up media for this path
			m_media = libvlc_media_new_path(m_vlcInst, (path+wxFileName::GetPathSeparator()+filename).ToStdString().c_str());
			libvlc_media_parse(m_media);

			//add to media list
			//lock first
			libvlc_media_list_lock(m_vlcMediaList);
			libvlc_media_list_add_media(m_vlcMediaList, m_media);
			libvlc_media_list_unlock(m_vlcMediaList);

			long itemIndex = m_fileList->InsertItem(idx, wxString(libvlc_media_get_meta(m_media,libvlc_meta_TrackNumber))); //Col 1 for track
			m_fileList->SetItem(itemIndex, idx+1, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Title))); //Col 1 for title
			m_fileList->SetItem(itemIndex, idx+2, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Artist))); //col 2 for artist
			m_fileList->SetItem(itemIndex, idx+3, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Album))); //col 3 for Album
			m_fileList->SetItem(itemIndex, idx+4, path+wxFileName::GetPathSeparator()+filename); //col 4 for Full Path
 
		}
		cont = dir.GetNext(&filename);
	}

	//set col width
	m_fileList->SetColumnWidth(0, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(1, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(2, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(3, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(4, wxLIST_AUTOSIZE);
}


void CMainFrame::OnVideoSizeChanged(wxSizeEvent& e) {

	e.Skip(true);
}

void CMainFrame::InitBindEvents() {
	Bind(KEVT_MEDIA_PLAY_ON_PROGRESS, &CMainFrame::OnUpdateMediaPosition, this, wxID_ANY);
	Bind(KEVT_MEDIA_LIST_NEXT_ITEM_SET, &CMainFrame::OnPListItemChanged, this, wxID_ANY);

	m_volumeSlider->Bind(wxEVT_COMMAND_SLIDER_UPDATED, &CMainFrame::OnVolumeChanging, this);
	m_mediaPosition->Bind(wxEVT_COMMAND_SLIDER_UPDATED, &CMainFrame::OnMediaSliderMoved, this);
}

void CMainFrame::OnFullVideoView(wxMouseEvent& event) {
	ToggleScreen();
}

void CMainFrame::OnRightClickMenu(wxMouseEvent& event) {
}

void CMainFrame::OnMediaSliderMoved(wxCommandEvent& event) {
	libvlc_media_player_set_position(m_mediaPlayer, (float) event.GetInt() / (float) TIMELINE_MAX);
}

void CMainFrame::OnLoop(wxCommandEvent& event) {
	switch(m_pbMode) {
	case libvlc_playback_mode_default 	: {
		//its default mode move it to loop
		libvlc_media_list_player_set_playback_mode(m_vlcMediaListPlayer, libvlc_playback_mode_loop);
		m_pbMode = libvlc_playback_mode_loop;
		m_loopButton->SetToolTip(_("Loop Mode Active"));
		break;
	}
	case libvlc_playback_mode_loop 	: {
		//its loop mode move it to repeat
		libvlc_media_list_player_set_playback_mode(m_vlcMediaListPlayer, libvlc_playback_mode_repeat);
		m_pbMode = libvlc_playback_mode_repeat;
		m_loopButton->SetToolTip(_("Repeat Mode Active"));
		break;
	}
	case libvlc_playback_mode_repeat 	: {
		//its repeat mode move it to default
		libvlc_media_list_player_set_playback_mode(m_vlcMediaListPlayer, libvlc_playback_mode_default);
		m_pbMode = libvlc_playback_mode_default;
		m_loopButton->SetToolTip(_("Default Mode Active"));
		break;
	}
	}
}

void CMainFrame::OnNext(wxCommandEvent& event) {
	libvlc_media_list_player_next(m_vlcMediaListPlayer);
	SetLabels();
}


void CMainFrame::OnPrevious(wxCommandEvent& event) {
	libvlc_media_list_player_previous(m_vlcMediaListPlayer);
	SetLabels();
}


void CMainFrame::OnPlayListShowHide(wxCommandEvent& event) {
	if(m_plPanel->IsShown() && m_display->IsShown())//playlist is shown and video is shown--hide PL
		m_plPanel->Show(false);
	else if(!m_plPanel->IsShown() && m_display->IsShown()) { //PL hidden but vide shown-- hide Video
		m_display->Show(false);
		m_plPanel->Show(true);
	}
	else {
		m_display->Show(true);
		m_plPanel->Show(true);
	}

	Layout();
}

void CMainFrame::OnPlayPause(wxCommandEvent& event) {
	if(libvlc_media_list_player_is_playing(m_vlcMediaListPlayer)==1) {
		//is playing change the icon to play and pause
		m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));
		//pause
		libvlc_media_list_player_pause(m_vlcMediaListPlayer);
	}
	else {
		//is playing change the icon to pause and play
		m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_pause));
		//play
		libvlc_media_player_pause(m_mediaPlayer);

	}
}

void CMainFrame::OnRandom(wxCommandEvent& event) {
}

void CMainFrame::OnVolumeChanging(wxCommandEvent& event) {
	//int vol = event.GetPosition();
	int vol = m_volumeSlider->GetValue();
	if(libvlc_audio_set_volume(m_mediaPlayer, vol)!=0)
		wxMessageBox(_("Failed to Set Volume!"), _("Error!"));
}


void CMainFrame::OnStop(wxCommandEvent& event) {
	libvlc_media_player_stop(m_mediaPlayer);
	//change button to player
	m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));
	m_mediaPosition->SetValue(0);
}

void CMainFrame::OnToggleVideo(wxCommandEvent& event) {
	ToggleScreen();
}

void CMainFrame::ToggleScreen() {
	if(m_plPanel->IsShown() || m_controlpanel->IsShown()) {
		//the Window is not full so hide them and make it full
		m_plPanel->Show(false);
		m_controlpanel->Show(false);
		ShowFullScreen(true);//full screen view
		//hide its borders also

	}
	else {
		m_plPanel->Show(true);
		m_controlpanel->Show(true);
		ShowFullScreen(false);//full screen view
	}
}

void CMainFrame::PlayMedia(const wxString& path) {
	libvlc_media_list_player_play(m_vlcMediaListPlayer);
	SetLabels();
}

CMainFrame::~CMainFrame() {
	libvlc_media_list_player_release(m_vlcMediaListPlayer);//release media list Player!
	libvlc_media_list_release(m_vlcMediaList);//release media list!
	libvlc_release(m_vlcInst);
}

void CMainFrame::InitVLC() {
	//create media player instance
	//const char* argv[] = {" --audio-visual visualizer --effect-list spectrum"}; //NULL default
	m_vlcInst = libvlc_new(0, /*argv*/ NULL);
	m_mediaPlayer = libvlc_media_player_new(m_vlcInst);
	m_vlcEvtMgr = libvlc_media_player_event_manager(m_mediaPlayer);

	m_vlcMediaList = libvlc_media_list_new(m_vlcInst); //media List

	m_vlcMediaListPlayer = libvlc_media_list_player_new(m_vlcInst);//media List
	libvlc_media_list_player_set_media_player(m_vlcMediaListPlayer, m_mediaPlayer); //Replace media player in media_list_player with this instance.
	libvlc_media_list_player_set_media_list(m_vlcMediaListPlayer, m_vlcMediaList);

	libvlc_media_list_player_set_playback_mode(m_vlcMediaListPlayer, libvlc_playback_mode_default);
	m_pbMode = libvlc_playback_mode_default;

	m_loopButton->SetToolTip(_("Default Mode Active"));
	//volume settings
	libvlc_audio_set_volume(m_mediaPlayer, m_volumeSlider->GetValue()*VOLUME_MAX);//default volume


//Set Video Part
#ifdef __WXGTK__
	GtkWidget* widget =(GtkWidget*) m_display->GetHandle();
	gtk_widget_realize(widget);   // Mandatory. Otherwise it segfaults.
	//Display* display = GDK_WINDOW_XDISPLAY( widget->window);
	//Window wid = GDK_WINDOW_XWINDOW( widget->window );
	//libvlc_media_player_set_xwindow(m_mediaPlayer, wid);
	GdkDrawable *dra = GDK_DRAWABLE(GTK_WIDGET(widget)->window);
	libvlc_media_player_set_xwindow(m_mediaPlayer, gdk_x11_drawable_get_xid(dra));

#else
	libvlc_media_player_set_hwnd(m_mediaPlayer, this->m_display->GetHandle());
#endif


	libvlc_event_attach(m_vlcEvtMgr, libvlc_MediaPlayerEndReached,::CatchMediaEvents, NULL);
	libvlc_event_attach(m_vlcEvtMgr, libvlc_MediaPlayerPositionChanged,::CatchMediaEvents, NULL);
	libvlc_event_attach(libvlc_media_list_player_event_manager(m_vlcMediaListPlayer), libvlc_MediaListPlayerNextItemSet,::CatchMediaEvents, m_vlcMediaList);
}

void CMainFrame::OnUpdateMediaPosition(wxCommandEvent& e) {
	float pos = libvlc_media_player_get_position(m_mediaPlayer);
	if(pos < 0.0) pos = 0.0;
	if(pos > 1.0) pos = 1.0;
	m_mediaPosition->SetValue((int)(pos * TIMELINE_MAX));
	//count down
	int secs = libvlc_media_player_get_length(m_mediaPlayer)*pos/1000;
	int hour=(secs/60/60);
	int min=(secs/60)%60;
	int sec = secs % 60;
	wxString label = wxString::Format(wxT("%d:%d:%d"), hour, min, sec);
	m_timeGone->SetLabel(label);
	Layout();
}

void CMainFrame::SetLabels() {
	int secs = libvlc_media_player_get_length(m_mediaPlayer)/1000;
	if(secs==-1) {
		//set lable empty
		m_timeLength->SetLabel(wxT(""));
		//end of game
		return ;
	}
	int hour=(secs/60/60);
	int min=(secs/60)%60;
	int sec = secs % 60;
	wxString label = wxString::Format(wxT("%d:%d:%d"), hour, min, sec);
	m_timeLength->SetLabel(label);
	Layout();
}

void CMainFrame::OnAboutUs(wxCommandEvent& event) {
	//CAbout* dlg = new CAbout(this);
	//dlg->Show();
	wxAboutDialogInfo aboutInfo;
	aboutInfo.SetName(_("Kasuku Media Player (ALPHA VERSION) - "));
	aboutInfo.SetVersion(MY_APP_VERSION_STRING);
	aboutInfo.SetDescription(_("Sweet Kasuku Sound!"));
	aboutInfo.SetCopyright("(C) 2012-2013, Tanzania Developers Foundation (TanDF)");
	aboutInfo.SetWebSite("http://hosannahighertech.co.tz/board");
	aboutInfo.SetLicence(GetLicence());
	//aboutInfo.SetIcon(GetIcon());
	//developers
	aboutInfo.AddDeveloper(_("Stefano Mtangoo (Lead Developer)"));
	//artists
	aboutInfo.AddArtist(_("C6 (Lead Artist)"));
	//other contributors
	wxAboutBox(aboutInfo);
}


wxString CMainFrame::GetLicence() {
	wxTextFile  input;
	wxString text=wxT("");
	/*input.Open(KConfig::Instance()->GetLicenceFile());
	if(input.IsOpened()) {
		while(!input.Eof())
			text=text+input.GetNextLine()+wxT("\n");
	}*/
	return text;
}

void CMainFrame::OnPListItemChanged(wxCommandEvent& e) {
	//solve for LC index
	//int lcIdx = libvlc_media_list_count(m_vlcMediaList)-idx-1;
	//clear selection before setting new one
	int item = 0;
	for(; item<m_fileList->GetItemCount(); item++) {

		m_fileList->SetItemState(item, 0, wxLIST_STATE_SELECTED/*|wxLIST_STATE_FOCUSED*/);//clear selection
		//reset colors back to sys colors 
		m_fileList->SetItemBackgroundColour(item, wxSystemSettingsNative::GetColour(wxSYS_COLOUR_WINDOW));
		m_fileList->SetItemTextColour(item, wxSystemSettingsNative::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	}

	//libvlc_media_list_player_stop(m_vlcMediaListPlayer);
	//m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));

	int idx = libvlc_media_list_count(m_vlcMediaList) - e.GetInt() - 1;//remember its zero indexed list?	//set selection
	//m_fileList->SetItemState(idx, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	m_fileList->SetItemBackgroundColour(idx, *wxBLACK);
	m_fileList->SetItemTextColour(idx, *wxGREEN);
	m_fileList->SetFocus();
}

void CMainFrame::OnQuitApp(wxCloseEvent& e)
{
	Destroy();
}

void CMainFrame::OnEraseBGEventCatcher(wxEraseEvent& event)
{
}

void CMainFrame::OnPaintEventCatecher(wxPaintEvent& event)
{
}


//===========+VLC Events!+=========================

void CatchMediaEvents(const libvlc_event_t* event, void* data) {
	//see for list of events http://www.videolan.org/developers/vlc/doc/doxygen/html/group__libvlc__event.html#ga88990ac48895aa07caece9eb75c2f2da
	if(wxTheApp==NULL||wxTheApp->GetTopWindow()==NULL)
		return ; //no app instance to send event to (destroyed already!)
	switch(event->type) {
	case libvlc_MediaPlayerPositionChanged: {
		wxCommandEvent evt(KEVT_MEDIA_PLAY_ON_PROGRESS, wxID_ANY);
		wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(evt);
		break ;
	}
	case libvlc_MediaPlayerEndReached: {
		wxCommandEvent evt(KEVT_MEDIA_PLAY_FINISHED, wxID_ANY);
		wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(evt);
		break ;
	}
	case libvlc_MediaListPlayerNextItemSet : {
		wxCommandEvent evt(KEVT_MEDIA_LIST_NEXT_ITEM_SET, wxID_ANY);
		//Get Index
		libvlc_media_t* media = (libvlc_media_t *)event->u.media_list_player_next_item_set.item;
		int idx = libvlc_media_list_index_of_item((libvlc_media_list_t*)data, media);
		//set index
		evt.SetInt(idx);
		wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(evt);
		break ;
	}
	}
}
