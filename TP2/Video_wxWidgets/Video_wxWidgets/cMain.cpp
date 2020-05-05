#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Tuvi recargada", wxPoint(30,30), wxSize(800,600))
{
	m_btn1 = new wxButton(this, 10001, "Click 4 sex!", wxPoint(20,20), wxSize(150,50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));

}

cMain::~cMain()
{

}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	m_list1->AppendString(m_txt1->GetValue());
	evt.Skip();
}