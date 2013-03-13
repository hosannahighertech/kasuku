#ifndef KDROPTARGET_H
#define KDROPTARGET_H

#include <wx/dnd.h> // Base class: wxFileDropTarget
#include <vlc/vlc.h>
#include <wx/listctrl.h>

class KDropTarget : public wxFileDropTarget {
public:
	KDropTarget(wxListCtrl* owner);
	~KDropTarget();
	
	void InitVLCArgs(libvlc_instance_t* vlcInst, libvlc_media_list_t* vlcMediaList);

	bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames);//Override this function to receive dropped files. 

private:
	libvlc_instance_t* m_vlcInst; 
	libvlc_media_t* m_media; 
	libvlc_media_list_t* m_vlcMediaList;//for auto player without user intervention 
	wxListCtrl* m_owner;

};

#endif // KDROPTARGET_H
