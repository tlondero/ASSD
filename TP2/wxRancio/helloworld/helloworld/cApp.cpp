
#include "cApp.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}


cApp::~cApp()
{

}

bool cApp::OnInit() {
	this->m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}
