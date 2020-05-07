#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked1)
	EVT_BUTTON(10002, OnButtonClicked2)
wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Tuvi recargada", wxPoint(30,30), wxSize(800,600))
{
	m_btn1 = new wxButton(this, 10001, "Click 4 sex!", wxPoint(20,20), wxSize(150,50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	m_btn2 = new wxButton(this, 10002, "This won't work!", wxPoint(340, 20), wxSize(150, 50));
}

cMain::~cMain()
{

}

void cMain::OnButtonClicked1(wxCommandEvent& evt)
{
	m_list1->AppendString(m_txt1->GetValue());
	evt.Skip();
}

void cMain::OnButtonClicked2(wxCommandEvent& evt)
{
	wxFileDialog openFileDialog(this, _("Open WAV file"), "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);  //Abro explorador de archivos

	
	if (openFileDialog.ShowModal() == wxID_CANCEL) {
		cout << "Error opening file explorer." << endl;
		evt.Skip();
	}
	

	string filePath = openFileDialog.GetPath();

	wxFileInputStream input_stream(openFileDialog.GetPath());	//Verifico que todo ande joya
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		evt.Skip();
	}
	else {
		
	}
	
	evt.Skip();
}