#include "cmainframe.h"
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include <wx/textfile.h>
#include <wx/clipbrd.h>
#include <wx/url.h>
#include <wx/app.h>
#include <wx/sysopt.h>
#include <wx/dnd.h>
#include "images.h"
#include "k_config.h"
#include "k_file_importer.h"
#include "k_drop_target.h"

wxDEFINE_EVENT(KEVT_MEDIA_PLAY_ON_PROGRESS, wxCommandEvent);
wxDEFINE_EVENT(KEVT_MEDIA_PLAY_FINISHED, wxCommandEvent);
wxDEFINE_EVENT(KEVT_MEDIA_LIST_NEXT_ITEM_SET, wxCommandEvent);
wxDEFINE_EVENT(KEVT_MEDIA_PLAY_PLAYING, wxCommandEvent);

CMainFrame::CMainFrame(wxWindow* parent):CMainFrameBase(parent)
{
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

	//popup
	m_ctrlPopup = new VideoCtrlPopup(this);
	m_ctrlPopup->m_volumeCtrl->SetRange(0, m_volumeSlider->GetMax());
	m_ctrlPopup->m_positionctrl->SetRange(0, m_mediaPosition->GetMax());
	m_ctrlPopup->Hide();

	//VLC Stuffs
	InitVLC();
	m_pbMode = libvlc_playback_mode_default;

	InitBindEvents();
	InitConfig();
	Maximize();

	m_splash->Destroy();//destroy splash and show the app

	//system options
	wxSystemOptions::SetOption(wxT("msw.window.no-clip-children"), 1);

	//set drop target to receive dropped files
	KDropTarget* dnd = new KDropTarget(m_fileList);
	dnd->InitVLCArgs(m_vlcInst, m_vlcMediaList);
	m_fileList->SetDropTarget(dnd);

}

void CMainFrame::OnMediaDClicked(wxListEvent& e)
{
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
	libvlc_media_add_option(libvlc_media_player_get_media(m_mediaPlayer), " --audio-visual=visualizer");
	wxSleep(1);
	SetLabels();
}

void CMainFrame::OnLoadDir(wxCommandEvent& event)
{
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

	//should we recurse in subfolders?
	if(dir.HasSubDirs()) {
		wxMessageDialog* confirmdlg = new wxMessageDialog(this, _("Do you want to add media in subfolders also?"), _("Confirm Recursing"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT);
		if(confirmdlg->ShowModal()!=wxID_YES) {
			wxArrayString filenames;
			wxDir::GetAllFiles(path, &filenames, wxT("*.*"));
			wxMessageDialog* confirmdlg = new wxMessageDialog(this, _("Clear The Playlist Before Append?"), _("Confirm Action"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT);
			if(confirmdlg->ShowModal()!=wxID_YES) {
				LoadFiles(filenames, true);
			} else
				LoadFiles(filenames, false);

		} else {
			KFileImporter traverser(m_fileList, m_vlcInst, m_vlcMediaList);
			dir.Traverse(traverser);
		}
	} else {
		wxArrayString filenames;
		wxDir::GetAllFiles(path, &filenames, wxT("*.*"));
		wxMessageDialog* confirmdlg = new wxMessageDialog(this, _("Clear The Playlist Before Append?"), _("Confirm Action"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT);
		if(confirmdlg->ShowModal()!=wxID_YES) {
			LoadFiles(filenames, true);
		} else
			LoadFiles(filenames, false);
	}
}


void CMainFrame::OnVideoSizeChanged(wxSizeEvent& e)
{

	e.Skip(true);
}

void CMainFrame::InitBindEvents()
{
	Bind(KEVT_MEDIA_PLAY_ON_PROGRESS, &CMainFrame::OnUpdateMediaPosition, this, wxID_ANY);
	Bind(KEVT_MEDIA_LIST_NEXT_ITEM_SET, &CMainFrame::OnPListItemChanged, this, wxID_ANY);
	Bind(KEVT_MEDIA_PLAY_FINISHED, &CMainFrame::OnPlayerEndReached, this, wxID_ANY);
	Bind(KEVT_MEDIA_PLAY_PLAYING, &CMainFrame::OnPlayerPlaying, this, wxID_ANY);

	m_volumeSlider->Bind(wxEVT_COMMAND_SLIDER_UPDATED, &CMainFrame::OnVolumeChanging, this);
	m_mediaPosition->Bind(wxEVT_COMMAND_SLIDER_UPDATED, &CMainFrame::OnMediaSliderMoved, this);

	Bind(wxEVT_COMMAND_MENU_SELECTED, &CMainFrame::OnCloseApp, this, wxID_EXIT);
}

void CMainFrame::OnFullVideoView(wxMouseEvent& event)
{
	ToggleScreen();
}

void CMainFrame::OnRightClickMenu(wxMouseEvent& event)
{
}

void CMainFrame::OnMediaSliderMoved(wxCommandEvent& event)
{
	libvlc_media_player_set_position(m_mediaPlayer, (float) event.GetInt() / (float) TIMELINE_MAX);
	//syc the popup controls
	m_ctrlPopup->m_positionctrl->SetValue(m_mediaPosition->GetValue());
}

void CMainFrame::OnLoop(wxCommandEvent& event)
{
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

void CMainFrame::OnNext(wxCommandEvent& event)
{
	libvlc_media_list_player_next(m_vlcMediaListPlayer);
	SetLabels();
}


void CMainFrame::OnPrevious(wxCommandEvent& event)
{
	libvlc_media_list_player_previous(m_vlcMediaListPlayer);
	SetLabels();
}


void CMainFrame::OnPlayListShowHide(wxCommandEvent& event)
{
	if(m_plPanel->IsShown() && m_display->IsShown())//playlist is shown and video is shown--hide PL
		m_plPanel->Show(false);
	else if(!m_plPanel->IsShown() && m_display->IsShown()) { //PL hidden but vide shown-- hide Video
		m_display->Show(false);
		m_plPanel->Show(true);
	} else {
		m_display->Show(true);
		m_plPanel->Show(true);
	}

	Layout();
}

void CMainFrame::OnPlayPause(wxCommandEvent& event)
{
	if(libvlc_media_list_player_is_playing(m_vlcMediaListPlayer)==1) {
		//is playing change the icon to play and pause
		m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));
		//pause
		libvlc_media_list_player_pause(m_vlcMediaListPlayer);
	} else {
		//is playing change the icon to pause and play
		m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_pause));
		//play
		libvlc_media_list_player_play(m_vlcMediaListPlayer);

	}
	SetLabels();
}

void CMainFrame::OnRandom(wxCommandEvent& event)
{
}

void CMainFrame::OnVolumeChanging(wxCommandEvent& event)
{
	//int vol = event.GetPosition();
	int vol = m_volumeSlider->GetValue();

	m_ctrlPopup->m_volumeCtrl->SetValue(vol);//sync popup ctrl

	if(libvlc_audio_set_volume(m_mediaPlayer, vol)!=0)
		wxMessageBox(_("Failed to Set Volume!"), _("Error!"));
}


void CMainFrame::OnStop(wxCommandEvent& event)
{
	libvlc_media_list_player_stop(m_vlcMediaListPlayer);
	//change button to player
	m_playPauseButton->SetBitmap(wxBITMAP_PNG(control_play));
	m_mediaPosition->SetValue(0);
	SetLabels();
	//show display image
	m_displayEventCatcher->SetPaintImage(true);
	m_displayEventCatcher->Refresh();
}

void CMainFrame::OnToggleVideo(wxCommandEvent& event)
{
	ToggleScreen();
}

void CMainFrame::ToggleScreen()
{
	if(m_plPanel->IsShown() || m_controlpanel->IsShown()) {
		//the Window is not full so hide them and make it full
		m_plPanel->Show(false);
		m_controlpanel->Show(false);
		ShowFullScreen(true);//full screen view
		//hide its borders also

	} else {
		m_plPanel->Show(true);
		m_controlpanel->Show(true);
		ShowFullScreen(false);//full screen view
		if(m_ctrlPopup)
			m_ctrlPopup->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_BOTTOM, 900);//hide the window
	}
}

void CMainFrame::PlayMedia(const wxString& path)
{
	libvlc_media_player_stop(m_mediaPlayer);
	SetLabels();
}

CMainFrame::~CMainFrame()
{
	libvlc_media_list_player_release(m_vlcMediaListPlayer);//release media list Player!
	libvlc_media_list_release(m_vlcMediaList);//release media list!
	libvlc_release(m_vlcInst);
}

void CMainFrame::InitVLC()
{
	//create media player instance
	const char* argv[2] = {" --audio-visual visualizer --effect-list spectrum", NULL};  //NULL default
	m_vlcInst = libvlc_new(0, argv /*NULL*/);
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

void CMainFrame::OnUpdateMediaPosition(wxCommandEvent& e)
{
	float pos = libvlc_media_player_get_position(m_mediaPlayer);
	if(pos < 0.0) pos = 0.0;
	if(pos > 1.0) pos = 1.0;
	m_mediaPosition->SetValue((int)(pos * TIMELINE_MAX));
	m_ctrlPopup->m_positionctrl->SetValue(m_mediaPosition->GetValue());
	//count down
	int secs = libvlc_media_player_get_length(m_mediaPlayer)*pos/1000;
	int hour=(secs/60/60);
	int min=(secs/60)%60;
	int sec = secs % 60;
	wxString label = wxString::Format(wxT("%d:%d:%d"), hour, min, sec);
	m_timeGone->SetLabel(label);
	Layout();
}

void CMainFrame::SetLabels()
{
	int secs = libvlc_media_player_get_length(m_mediaPlayer)/1000;
	if(secs==-1) {
		//set lable empty
		m_timeLength->SetLabel(wxT(""));
		//end of game
		//just display image
		m_displayEventCatcher->SetPaintImage(true);
		m_displayEventCatcher->Refresh();
		return ;
	}
	int hour=(secs/60/60);
	int min=(secs/60)%60;
	int sec = secs % 60;
	wxString label = wxString::Format(wxT("%d:%d:%d"), hour, min, sec);
	m_timeLength->SetLabel(label);

	Layout();
}

void CMainFrame::OnAboutUs(wxCommandEvent& event)
{
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
	aboutInfo.AddArtist(_("Joe Nyandigira (C6) - (Lead Artist)"));
	//other contributors
	wxAboutBox(aboutInfo);
}


wxString CMainFrame::GetLicence()
{
	wxTextFile  input;
	wxString text=wxT("");
	/*input.Open(KConfig::Instance()->GetLicenceFile());
	if(input.IsOpened()) {
		while(!input.Eof())
			text=text+input.GetNextLine()+wxT("\n");
	}*/
	return text;
}

void CMainFrame::OnPListItemChanged(wxCommandEvent& e)
{
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
	m_fileList->EnsureVisible(idx);
	m_fileList->SetFocus();

	//if the panel have no video do show kasuku foto
	//XilasZ_work in vlc IRC:has_vout return the number of vout. it's not the same thing, you can have a vout but no video track (audio file with visualization for instance)
	wxSleep(1); //it indeed have to parse it!
	bool isVout = libvlc_media_player_has_vout(m_mediaPlayer);
	bool hasVTrack = libvlc_video_get_track_count(m_mediaPlayer);
	if(m_mediaPlayer && (isVout || hasVTrack)) {
		//just hide display image
		m_displayEventCatcher->SetPaintImage(false);
		m_displayEventCatcher->Refresh();
	} else {
		//show display image
		m_displayEventCatcher->SetPaintImage(true);
		m_displayEventCatcher->Refresh();
	}
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

void CMainFrame::OnCloseApp(wxCommandEvent& e)
{
	Close();
}

void CMainFrame::InitConfig()
{
	m_plPanel->Show(false);//should be according to settings
}

void CMainFrame::OnPlayerPlaying(wxCommandEvent& e)
{

}

void CMainFrame::OnPlayerEndReached(wxCommandEvent& e)
{
	//show display image
	m_displayEventCatcher->SetPaintImage(true);
	m_displayEventCatcher->Refresh();
}

void CMainFrame::OnOpenFile(wxCommandEvent& event)
{
	wxFileDialog dlg(this, _("Open Media Files"), "", "","Media Files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR|wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...
	wxArrayString paths ;
	dlg.GetPaths(paths);

	wxMessageDialog* confirmdlg = new wxMessageDialog(this, _("Clear The Playlist Before Append?"), _("Confirm Action"), wxYES_NO|wxICON_INFORMATION|wxNO_DEFAULT);
	if(confirmdlg->ShowModal()!=wxID_YES) {
		LoadFiles(paths, true);
	} else
		LoadFiles(paths, false);

}

void CMainFrame::OnOpenStream(wxCommandEvent& event)
{
	wxString strInit = wxT("");
	// Read some text
	if(wxTheClipboard->Open()) {
		if(wxTheClipboard->IsSupported(wxDF_TEXT)) {
			wxTextDataObject data;
			wxTheClipboard->GetData(data);
			strInit = data.GetText();
		}
		wxTheClipboard->Close();
	}

	wxString strUrl = wxGetTextFromUser(_("Please Enter the URL to stream"), _("Open Stream"), strInit);
	if(strUrl.IsEmpty()) {
		//wxMessageBox(_("Empty URLs are not allowed!"));
		return ;
	}
	wxURL url(strUrl);
	if(url.IsOk()) {
		//open libvlc urls
		m_media = libvlc_media_new_location(m_vlcInst, strUrl.ToStdString().c_str());
		libvlc_media_player_set_media(m_mediaPlayer, m_media);
		libvlc_media_player_play(m_mediaPlayer);
		libvlc_media_release(m_media);
		wxSleep(60);
		libvlc_media_list_t* list =  libvlc_media_subitems(libvlc_media_player_get_media(m_mediaPlayer));
		libvlc_media_list_lock(list);
		m_media = libvlc_media_list_item_at_index(list, 0);
		libvlc_media_list_unlock(list);
		libvlc_media_player_set_media(m_mediaPlayer, m_media);
		libvlc_media_player_play(m_mediaPlayer);
		libvlc_media_release(m_media);
	} else {
		wxMessageBox(_("URL Error: Cannot continue!"));
	}
}

void CMainFrame::OnBeginDragFiles(wxListEvent& e)
{
	wxFileDataObject files;
	for(int i=0; i<m_fileList->GetSelectedItemCount(); i++) {
		files.AddFile(m_fileList->GetItemText(i, 4)); //col with idx 4 contains path
	}

	wxDropSource ds(m_fileList);
	ds.SetData(files);
	ds.DoDragDrop();

}

void CMainFrame::OnHoverCtrl(wxMouseEvent& event)
{
	if(IsFullScreen()) {
		if(m_ctrlPopup->IsShown())
			m_ctrlPopup->Hide();//hide the window
		else {
			m_ctrlPopup->SetPosition(wxGetMousePosition());
			m_ctrlPopup->Show();
		}
	}

	event.Skip();
}

void CMainFrame::LoadFiles(const wxArrayString& paths, bool clearPList)
{
	//should we clear PList?
	if(clearPList) {
		//clear current Item
		m_fileList->DeleteAllItems();
		libvlc_media_list_player_stop(m_vlcMediaListPlayer);
		libvlc_media_list_lock(m_vlcMediaList);
		int mCount = libvlc_media_list_count(m_vlcMediaList);
		libvlc_media_list_unlock(m_vlcMediaList);
		for(int i=0; i<mCount; i++) {
			libvlc_media_list_lock(m_vlcMediaList);
			libvlc_media_list_remove_index(m_vlcMediaList, i);
			libvlc_media_list_unlock(m_vlcMediaList);
		}
	}
	//load the files
	for(size_t i=0; i<paths.GetCount(); i++) {
		if(paths[i].AfterLast('.').Lower()==wxT("mp3")||paths[i].AfterLast('.').Lower()==wxT("ogg")
		   ||paths[i].AfterLast('.').Lower()==wxT("flv")||paths[i].AfterLast('.').Lower()==wxT("mp4")
		   ||paths[i].AfterLast('.').Lower()==wxT("mov")||paths[i].AfterLast('.').Lower()==wxT("wmv")
		  ) {

			//Set up media for this path
			m_media = libvlc_media_new_path(m_vlcInst, paths[i].ToStdString().c_str());
			libvlc_media_parse(m_media);

			//add to media list
			//lock first
			libvlc_media_list_lock(m_vlcMediaList);
			libvlc_media_list_add_media(m_vlcMediaList, m_media);
			libvlc_media_list_unlock(m_vlcMediaList);

			long itemIndex = m_fileList->InsertItem(0, wxString(libvlc_media_get_meta(m_media,libvlc_meta_TrackNumber))); //Col 1 for track
			m_fileList->SetItem(itemIndex, 1, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Title))); //Col 1 for title
			m_fileList->SetItem(itemIndex, 2, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Artist))); //col 2 for artist
			m_fileList->SetItem(itemIndex, 3, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Album))); //col 3 for Album
			m_fileList->SetItem(itemIndex, 4, paths[i]); //col 4 for Full Path

		}
	}

//set col width
	m_fileList->SetColumnWidth(0, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(1, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(2, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(3, wxLIST_AUTOSIZE);
	m_fileList->SetColumnWidth(4, wxLIST_AUTOSIZE);
}

void CMainFrame::OnKeyPressed(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_ESCAPE)
	{
		//process escape key
		if(IsFullScreen())
			ToggleScreen();
	}
	event.Skip();
}



//===========+VLC Events!+=========================

void CatchMediaEvents(const libvlc_event_t* event, void* data)
{
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
	case libvlc_MediaPlayerPlaying   : {
		wxCommandEvent evt(KEVT_MEDIA_PLAY_PLAYING, wxID_ANY);
		//set number
		wxTheApp->GetTopWindow()->GetEventHandler()->AddPendingEvent(evt);
		break ;
	}
	}
}
