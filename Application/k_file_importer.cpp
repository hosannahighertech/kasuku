#include "k_file_importer.h"

KFileImporter::KFileImporter(wxListCtrl* fileList, libvlc_instance_t* vlcInst, libvlc_media_list_t* mediaList) {
	m_fileList = fileList;
	m_vlcInst = vlcInst;
	m_vlcMediaList = mediaList;
}

KFileImporter::~KFileImporter() {
}

wxDirTraverseResult KFileImporter::OnDir(const wxString& dirname) {
	return wxDIR_CONTINUE;
}
wxDirTraverseResult KFileImporter::OnFile(const wxString& filename) {
	int idx=0;
	if(filename.AfterLast('.').Lower()==wxT("mp3")||filename.AfterLast('.').Lower()==wxT("ogg")
	        ||filename.AfterLast('.').Lower()==wxT("flv")||filename.AfterLast('.').Lower()==wxT("mp4")
	        ||filename.AfterLast('.').Lower()==wxT("mov")||filename.AfterLast('.').Lower()==wxT("wmv")
	  ) {

		//Set up media for this path
		m_media = libvlc_media_new_path(m_vlcInst, ( filename).ToStdString().c_str());
		libvlc_media_parse(m_media);

		//add to media list
		//lock first
		libvlc_media_list_lock(m_vlcMediaList);
		libvlc_media_list_add_media(m_vlcMediaList, m_media);
		libvlc_media_list_unlock(m_vlcMediaList);

		long itemIndex = m_fileList->InsertItem(idx, wxString(libvlc_media_get_meta(m_media,libvlc_meta_TrackNumber))); //Col 1 for track
		m_fileList->SetItem(itemIndex, idx+1, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Title))); //Col 1 for title
		m_fileList->SetItem(itemIndex, idx+2, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Artist))); //col 2 for artist
		m_fileList->SetItem(itemIndex, idx+3, wxString(libvlc_media_get_meta(m_media,libvlc_meta_Album))); //col 3 for Album
		m_fileList->SetItem(itemIndex, idx+4,  filename); //col 4 for Full Path

	}

	return wxDIR_CONTINUE;
}
