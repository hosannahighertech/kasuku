#include "k_splash.h"
 


KSplash::KSplash(wxTopLevelWindow* parent, const wxBitmap& bitmap): wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
												60000/*One minute so that we destroy it ourselves*/, 
												NULL, -1, wxDefaultPosition, 
												wxDefaultSize, wxBORDER_SIMPLE|wxSTAY_ON_TOP)
{
	m_parent = parent;
	m_parent->Show(false);//hide for now
	if(!CanSetTransparent())
		SetTransparent(wxIMAGE_ALPHA_TRANSPARENT);
	else
		SetBackgroundColour(wxColor(wxT("#0d0d0d")));// a hackish way to hide weakness ;)
}

KSplash::~KSplash()
{
	m_parent->Show();
}
