#ifndef KFILEIMPORTER_H
#define KFILEIMPORTER_H

#include <wx/dir.h> // Base class: wxDirTraverser
#include <wx/listctrl.h>  
#include <vlc/vlc.h>  

class KFileImporter : public wxDirTraverser {
public:
	KFileImporter(wxListCtrl* fileList, libvlc_instance_t* vlcInst, libvlc_media_list_t* mediaList);
	~KFileImporter();

	virtual wxDirTraverseResult OnDir(const wxString& dirname);
	virtual wxDirTraverseResult OnFile(const wxString& filename);

private:
	libvlc_instance_t* m_vlcInst; 
	libvlc_media_t* m_media; 
	libvlc_media_list_t* m_vlcMediaList;//for auto player without user intervention 
	wxListCtrl* m_fileList;
};

#endif // KFILEIMPORTER_H
