///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "caboutbase.h"

///////////////////////////////////////////////////////////////////////////

CAboutBase::CAboutBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_aboutNB = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_BOTTOM );
	m_aboutPanel = new wxPanel( m_aboutNB, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_about = new wxHtmlWindow( m_aboutPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer3->Add( m_about, 1, wxALL|wxEXPAND, 5 );
	
	
	m_aboutPanel->SetSizer( bSizer3 );
	m_aboutPanel->Layout();
	bSizer3->Fit( m_aboutPanel );
	m_aboutNB->AddPage( m_aboutPanel, _("About"), true, wxNullBitmap );
	m_licencePanel = new wxPanel( m_aboutNB, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_licence = new wxTextCtrl( m_licencePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	bSizer2->Add( m_licence, 1, wxALL|wxEXPAND, 5 );
	
	
	m_licencePanel->SetSizer( bSizer2 );
	m_licencePanel->Layout();
	bSizer2->Fit( m_licencePanel );
	m_aboutNB->AddPage( m_licencePanel, _("Licence"), false, wxNullBitmap );
	m_creditsPanel = new wxPanel( m_aboutNB, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	m_credits = new wxHtmlWindow( m_creditsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer31->Add( m_credits, 1, wxALL|wxEXPAND, 5 );
	
	
	m_creditsPanel->SetSizer( bSizer31 );
	m_creditsPanel->Layout();
	bSizer31->Fit( m_creditsPanel );
	m_aboutNB->AddPage( m_creditsPanel, _("Credits"), false, wxNullBitmap );
	
	mainSizer->Add( m_aboutNB, 1, wxEXPAND | wxALL, 0 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

CAboutBase::~CAboutBase()
{
}
