#include "k_image_panel.h"
#include "images.h"

KImagePanel::KImagePanel(wxWindow* parent, wxString file, wxBitmapType format) :wxPanel(parent) {
	// load the file... ideally add a check to see if loading was successful
	//m_image.LoadFile(wxT("/home/stefano/Documents/developer/Hosanna/Kasuku/icons/splash.png"), wxBITMAP_TYPE_PNG, format);
	m_image = wxBITMAP_PNG(splash).ConvertToImage();
	m_bmpWidth = -1;
	m_bmpHeight = -1;

	//start with image visible
	m_paintImage=true;

	InitBindEvents();
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void KImagePanel::PaintEvent(wxPaintEvent & evt) {
	if(!m_paintImage) {
		//do nothing to make it transparent

	}
	else {
		// depending on your system you may need to look at double-buffered dcs
		wxPaintDC dc(this);
		Render(dc);
		evt.Skip();
	}
}


void KImagePanel::EraseBGEvent(wxEraseEvent& e) {
	if(!m_paintImage) {
		//do nothing to make it transparent

	}
	else
		e.Skip();
	 
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void KImagePanel::PaintNow() {
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	Render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void KImagePanel::Render(wxDC&  dc) {
	int neww, newh;
	dc.GetSize(&neww, &newh);

	if(neww != m_bmpWidth || newh != m_bmpHeight) {
		m_resized = wxBitmap(m_image.Scale(neww, newh , wxIMAGE_QUALITY_NEAREST));
		m_bmpWidth = neww;
		m_bmpHeight = newh;
		dc.DrawBitmap(m_resized, 0, 0, false);
	}
	else {
		dc.DrawBitmap(m_resized, 0, 0, false);
	}
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void KImagePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	//skip the event.
	event.Skip();
}

void KImagePanel::InitBindEvents() {
	// catch paint events
	//Size event
	Bind(wxEVT_PAINT, &KImagePanel::PaintEvent, this);
	Bind(wxEVT_SIZE, &KImagePanel::OnSize, this);
	Bind(wxEVT_ERASE_BACKGROUND, &KImagePanel::EraseBGEvent, this);
}

void KImagePanel::SetPaintImage(bool paintImage) {
	m_paintImage = paintImage;
}
