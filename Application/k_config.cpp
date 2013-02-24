#include "k_config.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

KConfig* KConfig::ms_instance = 0;

KConfig::KConfig()
{
	//configs dir does not exists?
	//create Dir and copy defaults
	//copy licence file
	if(!wxDirExists(wxStandardPaths::Get().GetUserDataDir()))
	{
		wxString copy = wxStandardPaths::Get().GetExecutablePath()+wxFileName::GetPathSeparator()+wxT("gpl-3.0.txt");
		m_licence = wxStandardPaths::Get().GetUserDataDir()+wxFileName::GetPathSeparator()+wxT("gpl-3.0.txt");
		wxMkdir(wxStandardPaths::Get().GetUserDataDir());
		wxCopyFile(copy, m_licence, true);
	}
}

KConfig::~KConfig()
{
}

KConfig* KConfig::Instance()
{
	if (ms_instance == 0) {
		ms_instance = new KConfig();
	}
	return ms_instance;
}

void KConfig::Release()
{
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = 0;
}

wxString KConfig::GetLicenceFile()
{
	return m_licence;
}
