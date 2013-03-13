#include "k_drop_target.h"

KDropTarget::KDropTarget(wxListCtrl* owner) {
	m_owner = owner;
}

KDropTarget::~KDropTarget() {
}

bool KDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames) {
	for(size_t i=0; i<filenames.GetCount(); i++) {
		if(filenames[i].AfterLast('.').Lower()==wxT("mp3")||filenames[i].AfterLast('.').Lower()==wxT("ogg")
		        ||filenames[i].AfterLast('.').Lower()==wxT("flv")||filenames[i].AfterLast('.').Lower()==wxT("mp4")
		        ||filenames[i].AfterLast('.').Lower()==wxT("mov")||filenames[i].AfterLast('.').Lower()==wxT("wmv")
		  ) {

			//Set up media for this path
			m_media = libvlc_media_new_path(m_vlcInst, (filenames[i]).ToStdString().c_str());
			libvlc_media_parse(m_media);

			//add to media list
			//lock first
			libvlc_media_list_lock(m_vlcMediaList);
			libvlc_media_list_add_media(m_vlcMediaList, m_media);
			libvlc_media_list_unlock(m_vlcMediaList);

			long itemIndex = m_owner->InsertItem(0, wxString(libvlc_media_get_meta(m_media,libvlc_meta_TrackNumber))); //Col 1 for track
			m_owner->SetItem(itemIndex, 1, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Title))); //Col 1 for title
			m_owner->SetItem(itemIndex, 2, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Artist))); //col 2 for artist
			m_owner->SetItem(itemIndex, 3, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Album))); //col 3 for Album
			m_owner->SetItem(itemIndex, 4, filenames[i]); //col 4 for Full Path

		}
	}
}

void KDropTarget::InitVLCArgs(libvlc_instance_t* vlcInst, libvlc_media_list_t* vlcMediaList)
{
	m_vlcInst = vlcInst;
	m_vlcMediaList = vlcMediaList;
}
