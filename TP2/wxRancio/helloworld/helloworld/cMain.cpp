
#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(1000,OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain():wxFrame(nullptr,wxID_ANY,"Bro",wxPoint(30,30),wxSize(800,600))
{
	
	addMidBtn = new wxButton(this,1000,"Add Midi",wxPoint(200,20),wxSize(100,25));
	textBoxMid = new wxTextCtrl(this,1001,"", wxPoint(20, 20), wxSize(150, 25));
	midiListBox = new wxListBox(this,1002,wxPoint(20,110),wxSize(300,300));
}


cMain::~cMain()
{
}

void cMain::OnButtonClicked(wxCommandEvent &evt) {
	midiListBox->AppendString(textBoxMid->GetValue());
	evt.Skip();
}