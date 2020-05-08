#include "cMainMenu.h"

wxBEGIN_EVENT_TABLE(cMainMenu, wxFrame)
	//EVT_BUTTON(10001, OnButtonClicked1)
	//EVT_BUTTON(10002, AddWavToList)
	//EVT_BUTTON(10003, AddWavToList)
	//EVT_BUTTON(10004, DeleteWavFromList)
wxEND_EVENT_TABLE()

/*
	TO DO:
	- Averiguar como poner un "grid sizer" que no sea "uniforme" (bloques de distintos tamaños)
	- Averiguar como cargar imagenes dinamicamente
	- Averiguar como cambiar las fonts y sizes
	- Armar funciones jajaaaa
*/

cMainMenu::cMainMenu() : wxFrame(nullptr, wxID_ANY, "MAGT Synthesizer", wxPoint(30,30), wxSize(1080,720))
{
	//wxSize displaySize = wxGetDisplaySize();
	//gbSize = new wxGridBagSizer(0, 0);
	//gbSize->SetFlexibleDirection(wxBOTH);
	//gbSize.SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	//wxSize mainWindowSize = cMainMenu->GetSize();
	
	//Botones
	b_cargarMidi = new wxButton(this, wxID_ANY, "Load MIDI file", wxPoint(20, 20), wxSize(150, 50));
	b_crearWav = new wxButton(this, wxID_ANY, "Create WAV file", wxPoint(20, 90), wxSize(150, 50));
	//b_addTrack = new wxButton(this, wxID_ANY, "Add track", wxPoint(190, 160), wxSize(75, 50));
	//b_removeTrack = new wxButton(this, wxID_ANY, "Remove track", wxPoint(20, 20), wxSize(150, 50));
	//b_preview = new wxButton(this, wxID_ANY, "Listen preview track", wxPoint(20, 20), wxSize(150, 50));
	//b_addEffWav = new wxButton(this, wxID_ANY, "Add effect to WAV", wxPoint(20, 20), wxSize(150, 50));
	//b_removeEffWav = new wxButton(this, wxID_ANY, "Remove effect from WAV", wxPoint(20, 20), wxSize(150, 50));
	//b_toggleMic = new wxButton(this, wxID_ANY, "On / Off ", wxPoint(20, 20), wxSize(150, 50));
	//b_addEffMic = new wxButton(this, wxID_ANY, "Add effect to Mic", wxPoint(20, 20), wxSize(150, 50));
	//b_removeEffMic = new wxButton(this, wxID_ANY, "Remove effect from Mic", wxPoint(20, 20), wxSize(150, 50));

	//b_generateSpect = nullptr;

	//Drop Down Menu (Combo Box)
	ddm_track = new wxComboBox(this, wxID_ANY, "", wxPoint(20, 175), wxSize(300, 30));
	//ddm_instrumento = new wxComboBox(this, wxID_ANY, "", wxPoint(340, 80), wxSize(300, 30));
	//ddm_wavEff = new wxComboBox(this, wxID_ANY, "", wxPoint(340, 80), wxSize(300, 30));
	//ddm_micEff = new wxComboBox(this, wxID_ANY, "", wxPoint(340, 80), wxSize(300, 30));

	//Lists Box
	//lb_trackParam = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	//lb_trackValue = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	//lb_tracks = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	//lb_wavEff = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));
	//lb_micEff = new wxListBox(this, wxID_ANY, wxPoint(20, 120), wxSize(300, 300));

	//Images
	//wxStaticBitmap* img_Spectogram = nullptr;

	//Text
	t_tackDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_instrumentoDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_paramList = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_valueList = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_previewDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_effectWavDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));
	//t_effectMicDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(20, 150), wxSize(300, 15));

}

cMainMenu::~cMainMenu() {

}
//
//void cMainMenu::OnButtonClicked1(wxCommandEvent& evt)
//{
//	m_list1->AppendString(m_txt1->GetValue());
//	evt.Skip();
//}
//
//void cMainMenu::AddWavToList(wxCommandEvent& evt)
//{
//	wxFileDialog openFileDialog(this, _("Open WAV file"), "", "", "WAV files (*.wav)|*.wav", wxFD_OPEN | wxFD_FILE_MUST_EXIST);  //Abro explorador de archivos
//	bool addString = true;
//
//	if (openFileDialog.ShowModal() == wxID_CANCEL) {			//Esto está por si se cierra el explorador sin elegir archivos
//		return;
//	}
//
//	wxFileInputStream input_stream(openFileDialog.GetPath());	//Verifico que todo ande joya
//	
//	string pathSelected = openFileDialog.GetPath();				//Path completo
//
//	string stringSelected = pathSelected.substr(pathSelected.find_last_of('\\') + 1);					
//	stringSelected = stringSelected.substr(stringSelected.find_last_of('\\') + 1, stringSelected.size() - 4);		//Solo el nombre sin el .wav
//
//	if (!input_stream.IsOk()) {
//		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());				
//	}
//	else {
//		for (int i = 0; i < choices.size(); i++) {
//			if (choices[i] == stringSelected) {			//verifico si el string ya está dentro de vector
//				addString = false;
//				i = choices.size();
//			}
//		}
//		if (addString) {
//			choices.push_back(stringSelected);		//agrego el string al vector
//			m_ddm->Append(stringSelected);			//agrego el string al DDM
//		}
//	}
//
//	evt.Skip();
//}
//
//void cMainMenu::DeleteWavFromList(wxCommandEvent& evt)
//{
//	if (!(m_ddm->IsTextEmpty()))
//	{
//		bool removeString = false;							//existe la posibilidad que el usuario escriba cualquier cosa en el ddm
//
//		for (int i = 0; i < choices.size(); i++) {
//			if (choices[i] == m_ddm->GetStringSelection() ) {		//verifico si el nombre está dentro de vector
//				removeString = true;
//				i = choices.size();
//			}
//		}
//		if (removeString) {
//			choices.erase(choices.begin() + m_ddm->GetCurrentSelection());
//			m_ddm->Delete(m_ddm->GetCurrentSelection());
//		}
//	}
//
//	evt.Skip();
//}