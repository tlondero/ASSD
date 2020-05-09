#include "cMainMenu.h"

wxBEGIN_EVENT_TABLE(cMainMenu, wxFrame)
	EVT_BUTTON(10001, AddMidiToProgram)
	EVT_BUTTON(10002, AddTrack)
	EVT_TEXT(10003, detectInstrumentChange)
	EVT_MENU(10005, OnMenuExit)
	EVT_MENU(10006, OnMenuFullsecreen)
	
wxEND_EVENT_TABLE()

/*
	TO DO:
	- Colocar bein las cosas (GridBagSizer u otra forma)
	- Cargar imagenes dinamicamente
	- Cambiar las fonts y sizes
	- HACER APARECER LA TOOLBAR EN FULLSCREEN PORQUE NO SE PEUDE SALIR
	- Armar funciones jajaaaa
*/

cMainMenu::cMainMenu() : wxFrame(nullptr, wxID_ANY, "MAGT Synthesizer", wxPoint(30,30), wxSize(1080,720))
{
	//Menu y tool bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10006, "Fullscreen");
	menuFile->Append(wxID_ANY, "Help");
	menuFile->Append(10005, "Exit");
	m_MenuBar->Append(menuFile, "More");

	//Botones
	b_cargarMidi = new wxButton(this, 10001, "Load MIDI file", wxPoint(BUTTON_SP, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_crearWav = new wxButton(this, wxID_ANY, "Create WAV file", wxPoint(BUTTON_SP, BUTTON_Y + 2*BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_addTrack = new wxButton(this, 10002, "Add track", wxPoint(COL2, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_removeTrack = new wxButton(this, wxID_ANY, "Remove track", wxPoint(COL2 + BUTTON_SP + BUTTON_X, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_preview = new wxButton(this, wxID_ANY, "Listen preview track", wxPoint(COL2, 6 * BUTTON_SP + BUTTON_Y + TEXT_Y + LB_Y/2), wxSize(2*BUTTON_X, BUTTON_Y));
	b_addEffWav = new wxButton(this, wxID_ANY, "Add effect to WAV", wxPoint(COL2, 12 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_removeEffWav = new wxButton(this, wxID_ANY, "Remove effect from WAV", wxPoint(COL2 + BUTTON_SP + BUTTON_X, 12 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_toggleMic = new wxButton(this, wxID_ANY, "MIC On / Off ", wxPoint(COL3, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_addEffMic = new wxButton(this, wxID_ANY, "Add effect to Mic", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_removeEffMic = new wxButton(this, wxID_ANY, "Remove effect from Mic", wxPoint(COL3 + BUTTON_X + BUTTON_SP, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	//b_generateSpect = nullptr;

	
	//Drop Down Menu (Combo Box)
	ddm_track = new wxComboBox(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 4 * BUTTON_SP + TEXT_Y), wxSize(DDM_X, DDM_Y));
	ddm_instrumento = new wxComboBox(this, 10003, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + 2 * DDM_Y), wxSize(DDM_X, DDM_Y));
	ddm_wavEff = new wxComboBox(this, wxID_ANY, "", wxPoint(COL2, 10 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2), wxSize(DDM_X, DDM_Y));
	ddm_micEff = new wxComboBox(this, wxID_ANY, "", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y), wxSize(DDM_X, DDM_Y));


	//Lists Box
	//lb_trackParam = new wxListBox(this, wxID_ANY, wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(LB_X/2, LB_Y));
	lb_tracks = new wxListBox(this, wxID_ANY, wxPoint(COL2, 4 * BUTTON_SP + BUTTON_Y + TEXT_Y), wxSize(LB_X, LB_Y/2));
	lb_wavEff = new wxListBox(this, wxID_ANY, wxPoint(COL2, 14 * BUTTON_SP + 3 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(LB_X, LB_Y/2));
	lb_micEff = new wxListBox(this, wxID_ANY, wxPoint(COL3, 3 * BUTTON_SP + 2 * BUTTON_Y + TEXT_Y + DDM_Y), wxSize(300, 300));

		
	//Images
	//wxStaticBitmap* img_Spectogram = nullptr;


	//Text
	t_tackDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(BUTTON_SP, 2*BUTTON_Y + 4*BUTTON_SP), wxSize(TEXT_X, TEXT_Y));
	t_instrumentoDdm = new wxStaticText(this, wxID_ANY, "Instruments:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + DDM_Y), wxSize(TEXT_X, TEXT_Y));
	t_paramList = new wxStaticText(this, wxID_ANY, "Parameters:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + 3 * DDM_Y), wxSize(TEXT_X, TEXT_Y));
	t_previewDdm = new wxStaticText(this, wxID_ANY, "Lista de tracks agregados:", wxPoint(COL2, 4 * BUTTON_SP + BUTTON_Y), wxSize(TEXT_X, TEXT_Y));
	t_effectWavDdm = new wxStaticText(this, wxID_ANY, "WAV Effects:", wxPoint(COL2, 6 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2), wxSize(TEXT_X, TEXT_Y));
	t_effectMicDdm = new wxStaticText(this, wxID_ANY, "MIC Effects:", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y), wxSize(TEXT_X, TEXT_Y));



	//Dynamic TextCtrl
	tx_organA = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_organR = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 10 * BUTTON_SP + 3 * DDM_Y + 4 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_organS = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 12 * BUTTON_SP + 3 * DDM_Y + 6 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_guitarRf = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	tx_toShow.push_back(tx_organA);
	tx_toShow.push_back(tx_organR);
	tx_toShow.push_back(tx_organS);
	tx_toShow.push_back(tx_guitarRf);

	t_organA = new wxStaticText(this, wxID_ANY, "A:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_organR = new wxStaticText(this, wxID_ANY, "R:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 9 * BUTTON_SP + 3 * DDM_Y + 3 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_organS = new wxStaticText(this, wxID_ANY, "S:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 11 * BUTTON_SP + 3 * DDM_Y + 5 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_guitarRf = new wxStaticText(this, wxID_ANY, "RL:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_toShow.push_back(t_organA);
	t_toShow.push_back(t_organR);
	t_toShow.push_back(t_organS);
	t_toShow.push_back(t_guitarRf);

	
	for (int i = 0; i < tx_toShow.size(); i++) {
		tx_toShow[i]->Hide();
		t_toShow[i]->Hide();
	}

	////Grid Sizer

	//wxGridBagSizer* grid = new wxGridBagSizer();

	//grid->Add(b_cargarMidi, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, BUTTON_SP);		//Cargo en el grid los elementos
	//grid->Add(b_crearWav, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_addTrack, wxGBPosition(2, 3), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_removeTrack, wxGBPosition(2, 4), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_preview, wxGBPosition(0, 3), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_addEffWav, wxGBPosition(7, 3), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_removeEffWav, wxGBPosition(7, 4), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_toggleMic, wxGBPosition(3, 6), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_addEffMic, wxGBPosition(5, 6), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(b_removeEffMic, wxGBPosition(5, 7), wxGBSpan(1, 1), wxALL, BUTTON_SP);

	//grid->Add(ddm_track, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(ddm_instrumento, wxGBPosition(6, 0), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(ddm_wavEff, wxGBPosition(14, 3), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(ddm_micEff, wxGBPosition(6, 6), wxGBSpan(1, 2), wxALL, BUTTON_SP);

	//grid->Add(t_tackDdm, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(t_instrumentoDdm, wxGBPosition(5, 0), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(t_paramList, wxGBPosition(9, 0), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(t_valueList, wxGBPosition(9, 1), wxGBSpan(1, 1), wxALL, BUTTON_SP);
	//grid->Add(t_previewDdm, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(t_effectWavDdm, wxGBPosition(13, 3), wxGBSpan(1, 2), wxALL, BUTTON_SP);
	//grid->Add(t_effectMicDdm, wxGBPosition(6, 6), wxGBSpan(1, 2), wxALL, BUTTON_SP);

	//grid->AddGrowableCol(0, 0);

	////int gridSize = 10;
	////for (int i = 0; i < gridSize; i++) {
	////	grid->AddGrowableCol(i, 0);
	////	grid->AddGrowableRow(i, 0);
	////}

	//this->SetSizer(grid);

	//CARGAR LOS DDM

	ddm_instrumento->AppendString(GUITAR);		//FORMA RUDIMENTARIA PARA DEBUGGEAR
	ddm_instrumento->AppendString(ORGANO);


}

void cMainMenu::OnMenuFullsecreen(wxCommandEvent& evt) {
	this->ShowFullScreen(!fullscreen, wxFULLSCREEN_ALL ^ wxFULLSCREEN_NOSTATUSBAR);
	fullscreen = !fullscreen;
	evt.Skip();
}

void cMainMenu::OnMenuExit(wxCommandEvent & evt) {
	Close();
	evt.Skip();
}

void cMainMenu::AddTrack(wxCommandEvent& evt) {
	if (!(ddm_instrumento->IsTextEmpty()) && !(ddm_track->IsTextEmpty())) {
		ddm_instrumento->GetStringSelection();
		ddm_track->GetStringSelection();
	}
	evt.Skip();
}

void cMainMenu::detectInstrumentChange(wxCommandEvent& evt) {
	for (int i = 0; i < tx_toShow.size(); i++) {
		tx_toShow[i]->Clear();
		tx_toShow[i]->Hide();
		t_toShow[i]->Hide();
	}
	string intrumentoElegido = ddm_instrumento->GetStringSelection();						//verificar que el imput esté en la lista de esa mierda
	
	if (intrumentoElegido == GUITAR) {
		tx_guitarRf->Show();
		t_guitarRf->Show();
	}
	else if (intrumentoElegido == ORGANO) {
		tx_organA->Show();
		tx_organS->Show();
		tx_organR->Show();
		t_organA->Show();
		t_organS->Show();
		t_organR->Show();	
	}
	evt.Skip();
}

/*
void cMainMenu::addValueToParam(wxCommandEvent& evt) {
	string track = ddm_track->GetStringSelection();
	string instrument = ddm_instrumento->GetStringSelection();
	string param = lb_trackParam->GetStringSelection();
	double value = stod(string(tx_trackValue->GetStringSelection()));
	UserChoice uc;

	if (instrument == GUITAR) {

	}
	else if (instrument == ORGANO) {
		if (param == "A") {
			uc.params.A = value;
		}
		else if (param == "D") {
			uc.params.D = value;
		}
		else if (param == "R") {
			uc.params.R = value;
		}
	}

	this->ui.pairTrackInst.push_back(uc);
}
*/


void cMainMenu::AddMidiToProgram(wxCommandEvent& evt) {

	wxFileDialog openFileDialog(this, _("Open MIDI file"), "", "", "MIDI files (*.mid)|*.mid", wxFD_OPEN | wxFD_FILE_MUST_EXIST);  //Abro explorador de archivos
	bool addString = true;
	if (openFileDialog.ShowModal() == wxID_CANCEL) {			//Esto está por si se cierra el explorador sin elegir archivos
		return;
	}

	wxFileInputStream input_stream(openFileDialog.GetPath());	//Verifico que todo ande joya

	string pathSelected = openFileDialog.GetPath();				//Path completo

	//string stringSelected = pathSelected.substr(pathSelected.find_last_of('\\') + 1);
	//stringSelected = stringSelected.substr(stringSelected.find_last_of('\\') + 1, stringSelected.size() - 4);		//Solo el nombre sin el .wav

	if (!input_stream.IsOk()) {
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
	}
	else if (selecetedMidi != pathSelected) {			//verifico si el string ya está dentro de vector
		ddm_track->Clear();
		selecetedMidi = pathSelected;
		if (this->midi.addMidi(this->selecetedMidi)) {
				this->midiTranslated=this->midi.getTracks();
				addToDdm(midiToStringDdm(this->midiTranslated), ddm_track);
		}
		else {
			//algun tipo de error;
		}
		
	}
	evt.Skip();
}

cMainMenu::~cMainMenu() {

}

void cMainMenu::addToDdm(vector<string> tracks, wxComboBox* ddm) {
	for (int i = 0; i < tracks.size(); i++) {
		ddm->Append(tracks[i]);
	}
}


vector<string> cMainMenu::midiToStringDdm(vector<Tracks> MidiParsed) {
	vector<string> myddmtext;
	for (unsigned int i = 0; i < MidiParsed.size(); i++) {
		myddmtext.push_back("Track " + to_string(i) + " [" + MidiParsed[i].instrumentName + "] " + "(Notes : " + to_string(MidiParsed[i].Notes.size()) + ")");
	}
	return myddmtext;
}

/*
void cMainMenu::AddTrackToDdm(wxCommandEvent& evt)
{
	wxFileDialog openFileDialog(this, _("Open MIDI file"), "", "", "MIDI files (*.mid)|*.mid", wxFD_OPEN | wxFD_FILE_MUST_EXIST);  //Abro explorador de archivos
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
		for (int i = 0; i < selecetedMidi.size(); i++) {
			if (selecetedMidi[i] == stringSelected) {			//verifico si el string ya está dentro de vector
				addString = false;
				i = selecetedMidi.size();
			}
		}
		if (addString) {
			selecetedMidi.push_back(stringSelected);		//agrego el string al vector
			ddm_track->Append(stringSelected);			//agrego el string al DDM
		}
	}

	evt.Skip();
}

void cMainMenu::DeleteTrackToDdm(wxCommandEvent& evt){

	if (!(ddm_track->IsTextEmpty()))
	{
		bool removeString = false;							//existe la posibilidad que el usuario escriba cualquier cosa en el ddm

		for (int i = 0; i < selecetedMidi.size(); i++) {
			if (selecetedMidi[i] == ddm_track->GetStringSelection() ) {		//verifico si el nombre está dentro de vector
				removeString = true;
				i = selecetedMidi.size();
			}
		}
		if (removeString) {
			selecetedMidi.erase(selecetedMidi.begin() + ddm_track->GetCurrentSelection());
			ddm_track->Delete(ddm_track->GetCurrentSelection());
		}
	}

	evt.Skip();
}
*/


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