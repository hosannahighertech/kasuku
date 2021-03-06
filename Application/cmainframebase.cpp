///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "cmainframebase.h"

///////////////////////////////////////////////////////////////////////////

CMainFrameBase::CMainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_menubar = new wxMenuBar( 0 );
	m_musicMenu = new wxMenu();
	wxMenuItem* m_m_openFile;
	m_m_openFile = new wxMenuItem( m_musicMenu, wxID_OPEN, wxString( _("Open File(s)") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_m_openFile );
	
	wxMenuItem* m_openStream;
	m_openStream = new wxMenuItem( m_musicMenu, wxID_ANY, wxString( _("Open Location") ) + wxT('\t') + wxT("CTRL+Shift+O"), wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_openStream );
	
	wxMenuItem* m_openDisk;
	m_openDisk = new wxMenuItem( m_musicMenu, wxID_ANY, wxString( _("Open Disc") ) , wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_openDisk );
	
	wxMenuItem* m_LoadFolder;
	m_LoadFolder = new wxMenuItem( m_musicMenu, wxID_ANY, wxString( _("Import Directory") ) + wxT('\t') + wxT("CTRL+I"), wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_LoadFolder );
	
	wxMenuItem* m_importPL;
	m_importPL = new wxMenuItem( m_musicMenu, wxID_ANY, wxString( _("Import Playlist") ) + wxT('\t') + wxT("CTRL+Shift+P"), wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_importPL );
	
	wxMenuItem* m_menuExit;
	m_menuExit = new wxMenuItem( m_musicMenu, wxID_EXIT, wxString( _("Quit") ) + wxT('\t') + wxT("Ctrl+Q"), wxEmptyString, wxITEM_NORMAL );
	m_musicMenu->Append( m_menuExit );
	
	m_menubar->Append( m_musicMenu, _("Media") ); 
	
	m_helpMenu = new wxMenu();
	wxMenuItem* m_about;
	m_about = new wxMenuItem( m_helpMenu, wxID_ANY, wxString( _("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_helpMenu->Append( m_about );
	
	wxMenuItem* m_help;
	m_help = new wxMenuItem( m_helpMenu, wxID_ANY, wxString( _("Manual") ) , wxEmptyString, wxITEM_NORMAL );
	m_helpMenu->Append( m_help );
	
	m_menubar->Append( m_helpMenu, _("Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	m_videoPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	m_videoPanel->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	
	m_mgr.AddPane( m_videoPanel, wxAuiPaneInfo() .Name( wxT("player_pane") ).Left() .CaptionVisible( false ).PinButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).CentrePane() );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_display = new wxPanel( m_videoPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	m_display->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	m_display->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	 m_displayEventCatcher= new KImagePanel( m_display);
	m_displayEventCatcher->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	m_displayEventCatcher->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	
	bSizer9->Add( m_displayEventCatcher, 1, wxALL|wxEXPAND, 0 );
	
	
	m_display->SetSizer( bSizer9 );
	m_display->Layout();
	bSizer9->Fit( m_display );
	bSizer2->Add( m_display, 1, wxALL|wxEXPAND, 0 );
	
	m_controlpanel = new wxPanel( m_videoPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_timeGone = new wxStaticText( m_controlpanel, wxID_ANY, _("-:-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_timeGone->Wrap( -1 );
	bSizer7->Add( m_timeGone, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_mediaPosition = new wxSlider( m_controlpanel, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer7->Add( m_mediaPosition, 1, wxALL|wxEXPAND, 5 );
	
	m_timeLength = new wxStaticText( m_controlpanel, wxID_ANY, _("-:-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_timeLength->Wrap( -1 );
	bSizer7->Add( m_timeLength, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_playPauseButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	m_playPauseButton->SetDefault(); 
	bSizer8->Add( m_playPauseButton, 0, wxALL, 5 );
	
	m_previousButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_previousButton, 0, wxALL, 5 );
	
	m_stopButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_stopButton, 0, wxALL, 5 );
	
	m_nextButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_nextButton, 0, wxALL, 5 );
	
	m_toggleVideoButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_toggleVideoButton, 0, wxALL, 5 );
	
	m_showPlayListButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_showPlayListButton, 0, wxALL, 5 );
	
	m_loopButton = new wxBitmapButton( m_controlpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer8->Add( m_loopButton, 0, wxALL, 5 );
	
	
	bSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_volumeSlider = new wxSlider( m_controlpanel, wxID_ANY, 10, 0, 200, wxDefaultPosition, wxSize( 100,-1 ), wxSL_AUTOTICKS|wxSL_HORIZONTAL );
	bSizer8->Add( m_volumeSlider, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	m_controlpanel->SetSizer( bSizer6 );
	m_controlpanel->Layout();
	bSizer6->Fit( m_controlpanel );
	bSizer2->Add( m_controlpanel, 0, wxEXPAND | wxALL, 5 );
	
	m_plPanel = new wxPanel( m_videoPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_plPanel, wxID_ANY, _("Filter (By Album, Author, Date etc.)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer4->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_comboBox1 = new wxComboBox( m_plPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer4->Add( m_comboBox1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );
	
	m_fileList = new wxListCtrl( m_plPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	bSizer3->Add( m_fileList, 1, wxALL|wxEXPAND, 5 );
	
	
	m_plPanel->SetSizer( bSizer3 );
	m_plPanel->Layout();
	bSizer3->Fit( m_plPanel );
	bSizer2->Add( m_plPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	m_videoPanel->SetSizer( bSizer2 );
	m_videoPanel->Layout();
	bSizer2->Fit( m_videoPanel );
	
	m_mgr.Update();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CMainFrameBase::OnQuitApp ) );
	this->Connect( m_m_openFile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnOpenFile ) );
	this->Connect( m_openStream->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnOpenStream ) );
	this->Connect( m_LoadFolder->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnLoadDir ) );
	this->Connect( m_importPL->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnLoadDir ) );
	this->Connect( m_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnAboutUs ) );
	m_displayEventCatcher->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( CMainFrameBase::OnKeyPressed ), NULL, this );
	m_displayEventCatcher->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CMainFrameBase::OnFullVideoView ), NULL, this );
	m_displayEventCatcher->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CMainFrameBase::OnHoverCtrl ), NULL, this );
	m_displayEventCatcher->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CMainFrameBase::OnRightClickMenu ), NULL, this );
	m_playPauseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPlayPause ), NULL, this );
	m_previousButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPrevious ), NULL, this );
	m_stopButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnStop ), NULL, this );
	m_nextButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnNext ), NULL, this );
	m_toggleVideoButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnToggleVideo ), NULL, this );
	m_showPlayListButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPlayListShowHide ), NULL, this );
	m_loopButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnLoop ), NULL, this );
	m_fileList->Connect( wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler( CMainFrameBase::OnBeginDragFiles ), NULL, this );
	m_fileList->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( CMainFrameBase::OnMediaDClicked ), NULL, this );
}

CMainFrameBase::~CMainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CMainFrameBase::OnQuitApp ) );
	this->Disconnect( wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnOpenFile ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnOpenStream ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnLoadDir ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnLoadDir ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnAboutUs ) );
	m_displayEventCatcher->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( CMainFrameBase::OnKeyPressed ), NULL, this );
	m_displayEventCatcher->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CMainFrameBase::OnFullVideoView ), NULL, this );
	m_displayEventCatcher->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CMainFrameBase::OnHoverCtrl ), NULL, this );
	m_displayEventCatcher->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( CMainFrameBase::OnRightClickMenu ), NULL, this );
	m_playPauseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPlayPause ), NULL, this );
	m_previousButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPrevious ), NULL, this );
	m_stopButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnStop ), NULL, this );
	m_nextButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnNext ), NULL, this );
	m_toggleVideoButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnToggleVideo ), NULL, this );
	m_showPlayListButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnPlayListShowHide ), NULL, this );
	m_loopButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnLoop ), NULL, this );
	m_fileList->Disconnect( wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler( CMainFrameBase::OnBeginDragFiles ), NULL, this );
	m_fileList->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( CMainFrameBase::OnMediaDClicked ), NULL, this );
	
	m_mgr.UnInit();
	
}
