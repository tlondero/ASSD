#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp(){

}

bool cApp::OnInit()
{
	m_frame1 = new cMainMenu();
	//m_frame1->ShowFullScreen(true);
	//m_frame1->Maximize();
	m_frame1->Show();

	return true;
}
