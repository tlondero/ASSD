#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked1)
	EVT_BUTTON(10002, AddWavToList)
	EVT_BUTTON(10003, AddWavToList)
	EVT_BUTTON(10004, DeleteWavFromList)
wxEND_EVENT_TABLE()



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Tuvi recargada", wxPoint(30,30), wxSize(800,600))
{
	m_btn1 = new wxButton(this, 10001, "Click 4 sex!", wxPoint(20,20), wxSize(150,50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	m_btn2 = new wxButton(this, 10002, "Add archive", wxPoint(340, 20), wxSize(150, 50));
	m_ddm = new wxComboBox(this, 10003, "", wxPoint(340, 80), wxSize(300, 30));
	m_btn3 = new wxButton(this, 10004, "Delete from list", wxPoint(340, 150), wxSize(150, 50));
}

cMain::~cMain() {

}

void cMain::OnButtonClicked1(wxCommandEvent& evt)
{
	m_list1->AppendString(m_txt1->GetValue());
	evt.Skip();
}

void cMain::AddWavToList(wxCommandEvent& evt)
{
	wxFileDialog openFileDialog(this, _("Open WAV file"), "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);  //Abro explorador de archivos
	bool addString = true;

	if (openFileDialog.ShowModal() == wxID_CANCEL) {			//Esto está por si se cierra el explorador sin elegir archivos
		return;
	}

	wxFileInputStream input_stream(openFileDialog.GetPath());	//Verifico que todo ande joya
	
	string pathSelected = openFileDialog.GetPath();				//Path completo

	string stringSelected = pathSelected.substr(pathSelected.find_last_of('\\') + 1);					
	stringSelected = stringSelected.substr(stringSelected.find_last_of('\\') + 1, stringSelected.size() - 4);		//Solo el nombre sin el .wav

	if (!input_stream.IsOk()) {
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());				
	}
	else {
		for (int i = 0; i < choices.size(); i++) {
			if (choices[i] == stringSelected) {			//verifico si el string ya está dentro de vector
				addString = false;
				i = choices.size();
			}
		}
		if (addString) {
			choices.push_back(stringSelected);		//agrego el string al vector
			m_ddm->Append(stringSelected);			//agrego el string al DDM
		}
	}

	evt.Skip();
}

void cMain::DeleteWavFromList(wxCommandEvent& evt)
{
	if (!(m_ddm->IsTextEmpty()))
	{
		bool removeString = false;							//existe la posibilidad que el usuario escriba cualquier cosa en el ddm

		for (int i = 0; i < choices.size(); i++) {
			if (choices[i] == m_ddm->GetStringSelection() ) {		//verifico si el nombre está dentro de vector
				removeString = true;
				i = choices.size();
			}
		}
		if (removeString) {
			choices.erase(choices.begin() + m_ddm->GetCurrentSelection());
			m_ddm->Delete(m_ddm->GetCurrentSelection());
		}
	}

	evt.Skip();
}