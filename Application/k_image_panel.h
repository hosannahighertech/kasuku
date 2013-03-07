#ifndef KIMAGEPANEL_H
#define KIMAGEPANEL_H

#include <wx/wx.h>
#include <wx/sizer.h>
 
class KImagePanel : public wxPanel
{
    wxImage m_image;
    wxBitmap m_resized;
    int m_bmpWidth, m_bmpHeight;
    
public:
    KImagePanel(wxWindow* parent, wxString file=wxString(), wxBitmapType format=wxBITMAP_TYPE_ANY);
    
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
	
	void InitBindEvents(); 
     
}; 
 
#endif // KIMAGEPANEL_H
