#ifndef KSPLASH_H
#define KSPLASH_H

#include <wx/splash.h> // Base class: wxControl

class KSplash : public wxSplashScreen
{
public:
	KSplash(wxTopLevelWindow* parent, const wxBitmap& bitmap);
	~KSplash();
	
private:
	wxTopLevelWindow* m_parent;// parent frame that should be shown when splash dies

};

#endif // KSPLASH_H
