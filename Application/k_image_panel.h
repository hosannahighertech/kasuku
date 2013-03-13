#ifndef KIMAGEPANEL_H
#define KIMAGEPANEL_H

#include <wx/wx.h>
#include <wx/sizer.h>

class KImagePanel : public wxPanel {
	
private:
	wxImage m_image;
	wxBitmap m_resized;
	int m_bmpWidth, m_bmpHeight;
	bool m_paintImage;

public:
	KImagePanel(wxWindow* parent, wxString file=wxString(), wxBitmapType format=wxBITMAP_TYPE_ANY);

	void PaintEvent(wxPaintEvent & evt);
	void EraseBGEvent(wxEraseEvent & evt);
	void PaintNow();
	void OnSize(wxSizeEvent& event);
	void Render(wxDC& dc);

	void InitBindEvents();
	void SetPaintImage(bool paintImage=true);

};

#endif // KIMAGEPANEL_H
