#ifndef __WXVLCBACKEND_H__
#define __WXVLCBACKEND_H__
 
 
#include <wx/wx.h>  
#include <vlc/vlc.h>
#include <wx/mediactrl.h>

class wxVLCBackend : public wxMediaBackendCommonBase
{
public:
	wxVLCBackend();
	
	~wxVLCBackend();
	
	virtual bool Play();
	
	virtual bool Pause();
	
	virtual bool Stop() ; 	

	virtual bool SetPosition(wxLongLong where) ;
	
	virtual wxLongLong GetPosition();
	
	virtual wxLongLong GetDuration() ;
	
	virtual wxSize GetVideoSize();

	virtual double GetPlaybackRate() ;
	
	virtual bool SetPlaybackRate(double dRate);

	virtual wxMediaState GetState();

	virtual double GetVolume() ;
	
	virtual bool SetVolume(double dVolume);

	virtual bool Load(const wxURI &uri);
	
	virtual bool Load(const wxString &fileName);
	
	virtual bool Load(const wxURI &uri, const wxURI &proxy);

	virtual wxLongLong GetDownloadProgress();
	
	virtual wxLongLong GetDownloadTotal();
	 
	
	DECLARE_DYNAMIC_CLASS(wxVLCBackend)


};



#endif // __WXVLCBACKEND_H__

/*
#include <stdio.h>
#include <stdlib.h>
#include <vlc/vlc.h>

int main(int argc, char* argv[])
{
 libvlc_instance_t * inst;
 libvlc_media_player_t *mp;
 libvlc_media_t *m;
 
  Load the VLC engine 
 inst = libvlc_new (0, NULL);

  Create a new item 
 m = libvlc_media_new_path (inst, "http://mycool.movie.com/test.mov");
	
  Create a media player playing environement 
 mp = libvlc_media_player_new_from_media (m);
 
  No need to keep the media now 
 libvlc_media_release (m);

#if 0
  This is a non working code that show how to hooks into a window,
  * if we have a window around 
  libvlc_media_player_set_xdrawable (mp, xdrawable);
  or on windows 
  libvlc_media_player_set_hwnd (mp, hwnd);
  or on mac os 
  libvlc_media_player_set_nsobject (mp, view);
#endif

  play the media_player 
 libvlc_media_player_play (mp);

 sleep (10);  Let it play a bit 

  Stop playing 
 libvlc_media_player_stop (mp);

  Free the media_player 
 libvlc_media_player_release (mp);

 libvlc_release (inst);

 return 0;
}
*/
 