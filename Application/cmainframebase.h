///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CMAINFRAMEBASE_H__
#define __CMAINFRAMEBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/listctrl.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CMainFrameBase
///////////////////////////////////////////////////////////////////////////////
class CMainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_musicMenu;
		wxMenu* m_helpMenu;
		wxPanel* m_videoPanel;
		wxPanel* m_display;
		wxPanel* m_displayEventCatcher;
		wxPanel* m_controlpanel;
		wxStaticText* m_timeGone;
		wxSlider* m_mediaPosition;
		wxStaticText* m_timeLength;
		wxBitmapButton* m_playPauseButton;
		wxBitmapButton* m_previousButton;
		wxBitmapButton* m_stopButton;
		wxBitmapButton* m_nextButton;
		wxBitmapButton* m_toggleVideoButton;
		wxBitmapButton* m_showPlayListButton;
		wxBitmapButton* m_loopButton;
		wxSlider* m_volumeSlider;
		wxPanel* m_plPanel;
		wxStaticText* m_staticText1;
		wxComboBox* m_comboBox1;
		wxListCtrl* m_fileList;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuitApp( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnLoadDir( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAboutUs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVideoSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnEraseBGEventCatcher( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnFullVideoView( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPaintEventCatecher( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnRightClickMenu( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPlayPause( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrevious( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNext( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToggleVideo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlayListShowHide( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMediaDClicked( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		CMainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Kasuku Player - Welcome"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 649,510 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~CMainFrameBase();
	
};

#endif //__CMAINFRAMEBASE_H__
