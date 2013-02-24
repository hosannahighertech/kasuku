#ifndef KCONFIG_H
#define KCONFIG_H

#include <wx/wx.h>

class KConfig
{
	static KConfig* ms_instance;

public:
	static KConfig* Instance();
	static void Release();
	
	wxString GetLicenceFile();

private:
	KConfig();
	~KConfig();
	
	wxString m_licence;

};

#endif // KCONFIG_H
