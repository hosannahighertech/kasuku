#include "c_application.h" 
#include "cmainframe.h"


IMPLEMENT_APP(CApplication);

bool CApplication::OnInit()
{
	 wxInitAllImageHandlers() ;
	SetTopWindow(new CMainFrame(NULL));
	//GetTopWindow()->Show(); commented 'cause this will be done by splashscreen
	return true;
}
