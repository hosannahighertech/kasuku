#include "backend.h"

IMPLEMENT_DYNAMIC_CLASS(wxVLCBackend, wxMediaBackendCommonBase)
 

wxLongLong wxVLCBackend::GetDownloadProgress()
{
}

wxLongLong wxVLCBackend::GetDownloadTotal()
{
}

wxLongLong wxVLCBackend::GetDuration()
{
}

double wxVLCBackend::GetPlaybackRate()
{
}

wxLongLong wxVLCBackend::GetPosition()
{
}

wxMediaState wxVLCBackend::GetState()
{
}

wxSize wxVLCBackend::GetVideoSize()
{
}

double wxVLCBackend::GetVolume()
{
}

bool wxVLCBackend::Load(const wxString& fileName)
{
}

bool wxVLCBackend::Load(const wxURI& location)
{
}

bool wxVLCBackend::Load(const wxURI& uri, const wxURI& proxy)
{
}

bool wxVLCBackend::Pause()
{
}

bool wxVLCBackend::Play()
{
}

bool wxVLCBackend::SetPlaybackRate(double dRate)
{
}

bool wxVLCBackend::SetPosition(wxLongLong where)
{
}

bool wxVLCBackend::SetVolume(double dVolume)
{
}

bool wxVLCBackend::Stop()
{
}

wxVLCBackend::wxVLCBackend()
{
}

wxVLCBackend::~wxVLCBackend()
{
}
