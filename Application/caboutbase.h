///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CABOUTBASE_H__
#define __CABOUTBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/html/htmlwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/aui/auibook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CAboutBase
///////////////////////////////////////////////////////////////////////////////
class CAboutBase : public wxDialog 
{
	private:
	
	protected:
		wxAuiNotebook* m_aboutNB;
		wxPanel* m_aboutPanel;
		wxHtmlWindow* m_about;
		wxPanel* m_licencePanel;
		wxTextCtrl* m_licence;
		wxPanel* m_creditsPanel;
		wxHtmlWindow* m_credits;
	
	public:
		
		CAboutBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About Kasuku"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 377,373 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~CAboutBase();
	
};

#endif //__CABOUTBASE_H__
