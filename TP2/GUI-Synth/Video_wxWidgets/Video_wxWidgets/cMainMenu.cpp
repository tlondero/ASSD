#include "cMainMenu.h"

wxBEGIN_EVENT_TABLE(cMainMenu, wxFrame)
	EVT_BUTTON(10001, AddMidiToProgram)
	EVT_BUTTON(10002, AddTrack)
	EVT_TEXT(10003, detectInstrumentChange)
	EVT_MENU(10005, OnMenuExit)
	EVT_MENU(10006, OnMenuFullscreen)
	EVT_BUTTON(10007, RemoveTrack)
	EVT_BUTTON(10008, CreateWav)
	EVT_BUTTON(10009, CreatePreview)
	EVT_KEY_DOWN(OnKeyDown)
	EVT_BUTTON(10010, savePreview)
	EVT_BUTTON(10011, Replay)

	EVT_BUTTON(10012, loadWavSpec)
	EVT_BUTTON(10013, createSpec)
	EVT_TEXT(10014, detectWindowChange)

wxEND_EVENT_TABLE()

/*
	TO DO:
	- Colocar bein las cosas (GridBagSizer u otra forma)
	- Cargar imagenes dinamicamente
	- Cambiar las fonts y sizes
	- HACER APARECER LA TOOLBAR EN FULLSCREEN PORQUE NO SE PEUDE SALIR
	- Armar funciones jajaaaa
*/

cMainMenu::cMainMenu() : wxFrame(nullptr, wxID_ANY, "MAGT Synthesizer", wxPoint(30, 30), wxSize(1080, 720))
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
	b_crearWav = new wxButton(this, 10008, "Create WAV file", wxPoint(BUTTON_SP, BUTTON_Y + 2 * BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_addTrack = new wxButton(this, 10002, "Add track", wxPoint(COL2, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_removeTrack = new wxButton(this, 10007, "Remove track", wxPoint(COL2 + BUTTON_SP + BUTTON_X, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_preview = new wxButton(this, 10009, "Listen preview track", wxPoint(COL2, 6 * BUTTON_SP + BUTTON_Y + TEXT_Y + LB_Y / 2), wxSize(2 * BUTTON_X, BUTTON_Y));
	b_addEffWav = new wxButton(this, wxID_ANY, "Add effect to WAV", wxPoint(COL2, 12 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_removeEffWav = new wxButton(this, wxID_ANY, "Remove effect from WAV", wxPoint(COL2 + BUTTON_SP + BUTTON_X, 12 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_toggleMic = new wxButton(this, wxID_ANY, "MIC On / Off ", wxPoint(COL3, BUTTON_SP), wxSize(BUTTON_X, BUTTON_Y));
	b_addEffMic = new wxButton(this, wxID_ANY, "Add effect to Mic", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_removeEffMic = new wxButton(this, wxID_ANY, "Remove effect from Mic", wxPoint(COL3 + BUTTON_X + BUTTON_SP, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y + DDM_Y), wxSize(BUTTON_X, BUTTON_Y));
	
	b_savePreview = new wxButton(this, 10010, "Save preview", wxPoint(COL4, COL2), wxSize(BUTTON_X, BUTTON_Y));
	b_replay = new wxButton(this, 10011, "Replay", wxPoint(COL4 + TEXT_X, COL2), wxSize(BUTTON_X, BUTTON_Y));

	b_loadSpec = new wxButton(this, 10012, "Load WAV for spectogram", wxPoint(COL4, 2 * BUTTON_SP + TEXT_Y), wxSize(BUTTON_X, BUTTON_Y));
	b_updateSpec = new wxButton(this, 10013, "Create spectogram", wxPoint(COL4 + TEXT_X, 2 * BUTTON_SP + TEXT_Y), wxSize(BUTTON_X, BUTTON_Y));

	//Drop Down Menu (Combo Box)
	ddm_track = new wxComboBox(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 4 * BUTTON_SP + TEXT_Y), wxSize(DDM_X, DDM_Y));
	ddm_instrumento = new wxComboBox(this, 10003, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + 2 * DDM_Y), wxSize(DDM_X, DDM_Y));
	ddm_wavEff = new wxComboBox(this, wxID_ANY, "", wxPoint(COL2, 10 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2), wxSize(DDM_X, DDM_Y));
	ddm_micEff = new wxComboBox(this, wxID_ANY, "", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y + TEXT_Y), wxSize(DDM_X, DDM_Y));

	ddm_spect = new wxComboBox(this, 10014, "", wxPoint(COL4, BUTTON_Y + 3 * TEXT_Y + BUTTON_SP), wxSize(DDM_X, DDM_Y));
	for (int i = 0; i < NUMBER_OF_WINDOWS; i++) {
		ddm_spect->AppendString(WindowsList[i]);
	}

	ddm_nfft = new wxComboBox(this, wxID_ANY, "", wxPoint(COL4, BUTTON_Y + 5 * TEXT_Y + DDM_Y + 3 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	ddm_overlap = new wxComboBox(this, wxID_ANY, "", wxPoint(COL4, BUTTON_Y + 7 * TEXT_Y + DDM_Y + 5 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	
	for (int i = 1; i <= 11; i++) {
		double n = pow(2.0, i);
		ddm_nfft->AppendString(to_string((int) pow(2.0, i) ));
		ddm_overlap->AppendString(to_string((int) pow(2.0, i) ));
	}
	ddm_nfft->AppendString(to_string(4096));

	//Lists Box
	lb_tracks = new wxListBox(this, wxID_ANY, wxPoint(COL2, 4 * BUTTON_SP + BUTTON_Y + TEXT_Y), wxSize(LB_X, LB_Y / 2));
	lb_wavEff = new wxListBox(this, wxID_ANY, wxPoint(COL2, 14 * BUTTON_SP + 3 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2 + DDM_Y), wxSize(LB_X, LB_Y / 2));
	lb_micEff = new wxListBox(this, wxID_ANY, wxPoint(COL3, 3 * BUTTON_SP + 2 * BUTTON_Y + TEXT_Y + DDM_Y), wxSize(300, 300));

	
	//Text
	t_tackDdm = new wxStaticText(this, wxID_ANY, "Tracks:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 4 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y));
	t_instrumentoDdm = new wxStaticText(this, wxID_ANY, "Instruments:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + DDM_Y), wxSize(TEXT_X, TEXT_Y));
	t_paramList = new wxStaticText(this, wxID_ANY, "Parameters:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 6 * BUTTON_SP + 3 * DDM_Y), wxSize(TEXT_X, TEXT_Y));
	t_previewDdm = new wxStaticText(this, wxID_ANY, "Lista de tracks agregados:", wxPoint(COL2, 4 * BUTTON_SP + BUTTON_Y), wxSize(TEXT_X, TEXT_Y));
	t_effectWavDdm = new wxStaticText(this, wxID_ANY, "WAV Effects:", wxPoint(COL2, 6 * BUTTON_SP + 2 * BUTTON_Y + 2 * TEXT_Y + LB_Y / 2), wxSize(TEXT_X, TEXT_Y));
	t_effectMicDdm = new wxStaticText(this, wxID_ANY, "MIC Effects:", wxPoint(COL3, 2 * BUTTON_SP + BUTTON_Y), wxSize(TEXT_X, TEXT_Y));

	t_playMusic = new wxStaticText(this, wxID_ANY, "Currently not playing music. Create a preview to listen!", wxPoint(COL4 - BUTTON_SP, COL2 - 3 * TEXT_Y), wxSize(TEXT_X, TEXT_Y));

	t_currentSpec = new wxStaticText(this, wxID_ANY, "No spectogram selected.", wxPoint(COL4, BUTTON_SP), wxSize(TEXT_X, TEXT_Y));
	t_specWindType = new wxStaticText(this, wxID_ANY, "Select window type:", wxPoint(COL4, BUTTON_Y + 2 * TEXT_Y + BUTTON_SP), wxSize(TEXT_X, TEXT_Y));
	t_specWindParam = new wxStaticText(this, wxID_ANY, "Select window parameter:", wxPoint(COL4, BUTTON_Y + 3 * TEXT_Y + DDM_Y + 2 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y));

	t_nfft = new wxStaticText(this, wxID_ANY, "NFFT:", wxPoint(COL4, BUTTON_Y + 4 * TEXT_Y + DDM_Y + 2 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y));
	t_overlap = new wxStaticText(this, wxID_ANY, "Overlap:", wxPoint(COL4, BUTTON_Y + 6 * TEXT_Y + DDM_Y + 5 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y));

	//Dinmac Control Texts (INSTRUMENTOS)
	tx_organA = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_organR = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 10 * BUTTON_SP + 3 * DDM_Y + 4 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_organS = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 12 * BUTTON_SP + 3 * DDM_Y + 6 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	tx_fluteA = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_fluteR = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 10 * BUTTON_SP + 3 * DDM_Y + 4 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_fluteS = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 12 * BUTTON_SP + 3 * DDM_Y + 6 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	tx_guitarRf = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_eguitarRf = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	tx_drumRf = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 8 * BUTTON_SP + 3 * DDM_Y + 2 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	tx_drumB = new wxTextCtrl(this, wxID_ANY, "", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 10 * BUTTON_SP + 3 * DDM_Y + 4 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	tx_toShow.push_back(tx_organA);
	tx_toShow.push_back(tx_organR);
	tx_toShow.push_back(tx_organS);

	tx_toShow.push_back(tx_fluteA);
	tx_toShow.push_back(tx_fluteR);
	tx_toShow.push_back(tx_fluteS);

	tx_toShow.push_back(tx_guitarRf);
	tx_toShow.push_back(tx_eguitarRf);

	tx_toShow.push_back(tx_drumRf);
	tx_toShow.push_back(tx_drumB);

	//Dinmac Control Texts (VENTANAS)
	tx_specWindParam = new wxTextCtrl(this, wxID_ANY, "", wxPoint(COL4, BUTTON_Y + 8 * TEXT_Y + 2 * DDM_Y + 6 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	tx_specWindParam->Hide();


	//Dinmac Static Texts (INSTRUMENTOS)
	t_organA = new wxStaticText(this, wxID_ANY, "A:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_organR = new wxStaticText(this, wxID_ANY, "R:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 9 * BUTTON_SP + 3 * DDM_Y + 3 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_organS = new wxStaticText(this, wxID_ANY, "S:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 11 * BUTTON_SP + 3 * DDM_Y + 5 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	t_fluteA = new wxStaticText(this, wxID_ANY, "A:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_fluteR = new wxStaticText(this, wxID_ANY, "R:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 9 * BUTTON_SP + 3 * DDM_Y + 3 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_fluteS = new wxStaticText(this, wxID_ANY, "S:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 11 * BUTTON_SP + 3 * DDM_Y + 5 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	t_guitarRf = new wxStaticText(this, wxID_ANY, "RL:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_eguitarRf = new wxStaticText(this, wxID_ANY, "RL:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	t_bell = new wxStaticText(this, wxID_ANY, "No parameters needed", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));		//Same for trumpet, trombone, clarinet and banjo

	t_drumRf = new wxStaticText(this, wxID_ANY, "RL:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 7 * BUTTON_SP + 3 * DDM_Y + TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));
	t_drumB = new wxStaticText(this, wxID_ANY, "B:", wxPoint(BUTTON_SP, 2 * BUTTON_Y + 9 * BUTTON_SP + 3 * DDM_Y + 3 * TEXT_Y), wxSize(TEXT_X, TEXT_Y + 5));

	t_toShow.push_back(t_organA);
	t_toShow.push_back(t_organR);
	t_toShow.push_back(t_organS);

	t_toShow.push_back(t_fluteA);
	t_toShow.push_back(t_fluteR);
	t_toShow.push_back(t_fluteS);

	t_toShow.push_back(t_guitarRf);
	t_toShow.push_back(t_eguitarRf);

	t_toShow.push_back(t_drumRf);
	t_toShow.push_back(t_drumB);

	t_toShow.push_back(t_bell);

	for (int i = 0; i < tx_toShow.size(); i++) {
		tx_toShow[i]->Hide();
	}
	for (int i = 0; i < t_toShow.size(); i++) {
		t_toShow[i]->Hide();
	}

	//Dinmac Static Texts (VENTANAS)
	t_specGauss = new wxStaticText(this, wxID_ANY, "Standar Deviation:", wxPoint(COL4, BUTTON_Y + 7 * TEXT_Y + 2 * DDM_Y + 5 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	t_specExp = new wxStaticText(this, wxID_ANY, "Decay Scale:", wxPoint(COL4, BUTTON_Y + 7 * TEXT_Y + 2 * DDM_Y + 5 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	t_specKaiser = new wxStaticText(this, wxID_ANY, "Beta:", wxPoint(COL4, BUTTON_Y + 7 * TEXT_Y + 2 * DDM_Y + 5 * BUTTON_SP), wxSize(TEXT_X, TEXT_Y + 5));
	
	t_specGauss->Hide();
	t_specExp->Hide();
	t_specKaiser->Hide();

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
	for (int i = 0; i < NUMBER_OF_INSTRUMETS; i++) {
		ddm_instrumento->AppendString(InstrumentList[i]);
	}
}

void cMainMenu::OnMenuFullscreen(wxCommandEvent& evt) {
	this->ShowFullScreen(!fullscreen, wxFULLSCREEN_ALL ^ wxFULLSCREEN_NOSTATUSBAR);
	fullscreen = !fullscreen;
	evt.Skip();
}

void cMainMenu::OnMenuExit(wxCommandEvent & evt) {
	Close();
	evt.Skip();
}

void cMainMenu::AddTrack(wxCommandEvent& evt) {
	string instrument = ddm_instrumento->GetStringSelection();
	string track = ddm_track->GetStringSelection();
	UserChoice uc;
	bool letsPush = true;
	
	if (!(ddm_instrumento->IsTextEmpty()) && !(ddm_track->IsTextEmpty())) {
		if (((instrument == InstrumentList[0]) && !(tx_guitarRf->IsEmpty())) || ((instrument == InstrumentList[9]) && !(tx_eguitarRf->IsEmpty()))) {							//GUITARRA
			uc.TrackInstrument = instrument;
			int n = track.size() - (track.substr(track.find('['))).size() - 7;
			uc.TrackNumber = stoi(track.substr(6, n));
			if (instrument == InstrumentList[0]) {
				uc.params.GuitarParam_rf = stod((string)tx_guitarRf->GetValue());
			}
			else {
				uc.params.GuitarParam_rf = stod((string)tx_eguitarRf->GetValue());
			}
			for (int i = 0; i < ui.pairTrackInst.size(); i++) {
				if (ui.pairTrackInst[i].TrackNumber == uc.TrackNumber) {
					letsPush = false;
				}
			}
			if (letsPush) {
				ui.pairTrackInst.push_back(uc);
				lb_tracks->Append(track + ' ' + instrument);
			}
		}
		else if ((instrument == InstrumentList[1]) && !(tx_organA->IsEmpty()) && !(tx_organS->IsEmpty()) && !(tx_organR->IsEmpty())) {							//ORGANO
			uc.TrackInstrument = instrument;
			int i = track.size() - (track.substr(track.find('['))).size() - 7;
			uc.TrackNumber = stoi(track.substr(6, i));
			uc.params.A = stod((string)tx_organA->GetValue());
			uc.params.S = stod((string)tx_organS->GetValue());
			uc.params.R = stod((string)tx_organR->GetValue());

			for (int i = 0; i < ui.pairTrackInst.size(); i++) {
				if (ui.pairTrackInst[i].TrackNumber == uc.TrackNumber) {
					letsPush = false;
				}
			}
			if (letsPush) {
				ui.pairTrackInst.push_back(uc);
				lb_tracks->Append(track + ' ' + instrument);
			}	
		}
		else if ((instrument == InstrumentList[2]) && !(tx_fluteA->IsEmpty()) && !(tx_fluteS->IsEmpty()) && !(tx_fluteR->IsEmpty())) {							//FLUTE
			uc.TrackInstrument = instrument;
			int i = track.size() - (track.substr(track.find('['))).size() - 7;
			uc.TrackNumber = stoi(track.substr(6, i));
			uc.params.A = stod((string)tx_fluteA->GetValue());
			uc.params.S = stod((string)tx_fluteS->GetValue());
			uc.params.R = stod((string)tx_fluteR->GetValue());

			for (int i = 0; i < ui.pairTrackInst.size(); i++) {
				if (ui.pairTrackInst[i].TrackNumber == uc.TrackNumber) {
					letsPush = false;
				}
			}
			if (letsPush) {
				ui.pairTrackInst.push_back(uc);
				lb_tracks->Append(track + ' ' + instrument);
			}
		}
		else if ((instrument == InstrumentList[3]) || (instrument == InstrumentList[4]) || (instrument == InstrumentList[5]) || (instrument == InstrumentList[6]) || (instrument == InstrumentList[8])) {							//BELL, CLARINET, TROMBONE, TRUMPET AND BANJO
			uc.TrackInstrument = instrument;
			int n = track.size() - (track.substr(track.find('['))).size() - 7;
			uc.TrackNumber = stoi(track.substr(6, n));
			
			for (int i = 0; i < ui.pairTrackInst.size(); i++) {
				if (ui.pairTrackInst[i].TrackNumber == uc.TrackNumber) {
					letsPush = false;
				}
			}
			if (letsPush) {
				ui.pairTrackInst.push_back(uc);
				lb_tracks->Append(track + ' ' + instrument);
			}
		}
		else if ((instrument == InstrumentList[7]) && !(tx_drumRf->IsEmpty()) && !(tx_drumB->IsEmpty())) {							//DRUM
			uc.TrackInstrument = instrument;
			int i = track.size() - (track.substr(track.find('['))).size() - 7;
			uc.TrackNumber = stoi(track.substr(6, i));
			uc.params.DrumParam_rf = stod((string)tx_drumRf->GetValue());
			uc.params.DrumProb = stod((string)tx_drumB->GetValue());

			for (int i = 0; i < ui.pairTrackInst.size(); i++) {
				if (ui.pairTrackInst[i].TrackNumber == uc.TrackNumber) {
					letsPush = false;
				}
			}
			if (letsPush) {
				ui.pairTrackInst.push_back(uc);
				lb_tracks->Append(track + ' ' + instrument);
			}
		}
		else {
			//Warning
			wxMessageDialog warning(this, "No parameters selected", "Can't add track");
			warning.Center();
			warning.SetExtendedMessage("The instrument selected requires specific parameters. Please, configure the parameters to add the track.");
			warning.ShowModal();
			warning.Hide();
		}
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No parameters selected", "Can't add track");
		warning.Center();
		warning.SetExtendedMessage("Please, select a track and an instrument to configure and add the track.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}

void cMainMenu::RemoveTrack(wxCommandEvent& evt) {
	if (lb_tracks->GetSelection() != wxNOT_FOUND) {
		ui.pairTrackInst.erase(ui.pairTrackInst.begin() + lb_tracks->GetSelection());
		lb_tracks->Delete(lb_tracks->GetSelection());
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No tracks selected", "Can't remove track");
		warning.Center();
		warning.SetExtendedMessage("Please, select a track to remove.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}

void cMainMenu::detectInstrumentChange(wxCommandEvent& evt) {
	for (int i = 0; i < tx_toShow.size(); i++) {
		tx_toShow[i]->Clear();
		tx_toShow[i]->Hide();
	}
	for (int i = 0; i < t_toShow.size(); i++) {
		t_toShow[i]->Hide();
	}

	string intrumentoElegido = ddm_instrumento->GetStringSelection();						//verificar que el imput esté en la lista de esa mierda
	
	if (intrumentoElegido == InstrumentList[0]) {								//GUITARRA
		tx_guitarRf->Show();
		t_guitarRf->Show();
	}
	else if (intrumentoElegido == InstrumentList[1]) {							//ORGANO
		tx_organA->Show();
		tx_organS->Show();
		tx_organR->Show();
		t_organA->Show();
		t_organS->Show();
		t_organR->Show();	
	}
	else if (intrumentoElegido == InstrumentList[2]) {							//FLUTE
		tx_fluteA->Show();
		tx_fluteS->Show();
		tx_fluteR->Show();
		t_fluteA->Show();
		t_fluteS->Show();
		t_fluteR->Show();
	}
	else if ((intrumentoElegido == InstrumentList[3]) || (intrumentoElegido == InstrumentList[4]) || (intrumentoElegido == InstrumentList[5]) || (intrumentoElegido == InstrumentList[6]) || (intrumentoElegido == InstrumentList[8])) {
		//BELL, CLARINET, TROMBONE, TRUMPET AND BANJO
		t_bell->Show();
	}
	else if (intrumentoElegido == InstrumentList[7]) {							//DRUM
		tx_drumRf->Show();
		tx_drumB->Show();
		t_drumRf->Show();
		t_drumB->Show();
	}
	else if (intrumentoElegido == InstrumentList[9]) {							//E GUITAR
		tx_eguitarRf->Show();
		t_eguitarRf->Show();
	}
	evt.Skip();
}

void cMainMenu::AddMidiToProgram(wxCommandEvent& evt) {
	this->ui.pairTrackInst.clear();
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
		lb_tracks->Clear();
		lb_wavEff->Clear();
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

void cMainMenu::CreateWav(wxCommandEvent& evt) {
	if (!(lb_tracks->IsEmpty())) {
		wxFileDialog saveFileDialog(this, _("Save WAV file"), "", "", "WAV files (*.wav)|*.wav", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {			//Esto está por si se cierra el explorador sin elegir archivos
			return;
		}

		string pathSelected = saveFileDialog.GetPath();				//Path completo
		wxFileOutputStream output_stream(saveFileDialog.GetPath());

		if (!output_stream.IsOk()) {
			wxLogError("Cannot save file '%s'.", pathSelected);
		}
		else {

			int cutFrom = pathSelected.find_first_of('.');
			int cutUpto = pathSelected.size() - cutFrom;
			pathSelected = pathSelected.erase(cutFrom, cutUpto);

			//Load Bar
			wxMessageDialog loadBar(this, "Creating WAV", "Loading");
			loadBar.Center();
			loadBar.SetExtendedMessage("This could take a few minutes, please wait.");
			loadBar.ShowModal();
			myWC.compileWav(myCC.sytnsynthesisProject(this->midiTranslated, this->ui), this->midi.getTotalDuration() + 1, pathSelected, 1000);
			myWC.makeWav();
			loadBar.Hide();
		}
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No tracks available", "Can't create WAV file");
		warning.Center();
		warning.SetExtendedMessage("Please, add some tracks to create a WAV file.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}

void cMainMenu::CreatePreview(wxCommandEvent& evt) {
	if (lb_tracks->GetSelection() != wxNOT_FOUND) {
		UserChoice ucPrev = ui.pairTrackInst[lb_tracks->GetSelection()];
		UserInput uiPrev;
		ucPrev.InstrumentPreview = true;
		uiPrev.pairTrackInst.push_back(ucPrev);

		myWC.compileWav(myCC.sytnsynthesisProject(this->midiTranslated, uiPrev), PREVIEW_DURATION, "Previews/prevTrack", 1000);
		myWC.makeWav();


		if (firstTime) {
			//soundPlayer = new wxSound("Previews/prevTrack.wav", wxSOUND_SYNC);
			firstTime = false;
		}

		//if (PlaySound(TEXT("Previews/prevTrack.wav"), NULL, SND_FILENAME | SND_ASYNC)){ //(soundPlayer->Play("Previews/prevTrack.wav")) {
		//	t_playMusic->SetLabel("Now playing: " + lb_tracks->GetStringSelection());
		//	t_playMusic->Refresh();
		//}
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No tracks selected", "Can't create a preview");
		warning.Center();
		warning.SetExtendedMessage("Please, select a track to listen the preview.");
		warning.ShowModal();
		warning.Hide();
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

void cMainMenu::OnKeyDown(wxKeyEvent& evt) {
	if (evt.GetKeyCode() == WXK_F11) {
		this->ShowFullScreen(!fullscreen, wxFULLSCREEN_ALL ^ wxFULLSCREEN_NOSTATUSBAR);
		fullscreen = !fullscreen;
	}
	evt.Skip();
}

void cMainMenu::savePreview(wxCommandEvent& evt) {
	if (!firstTime) {
		wxFileDialog saveFileDialog(this, _("Save WAV file"), "", "", "WAV files (*.wav)|*.wav", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {			//Esto está por si se cierra el explorador sin elegir archivos
			return;
		}

		string pathSelected = saveFileDialog.GetPath();				//Path completo
		wxFileOutputStream output_stream(saveFileDialog.GetPath());

		if (!output_stream.IsOk()) {
			wxLogError("Cannot save file '%s'.", pathSelected);
		}
		else {
			wxCopyFile("Previews/prevTrack.wav", pathSelected);
		}
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No preview created", "Can't play preview");
		warning.Center();
		warning.SetExtendedMessage("Please, add track a and create a preview.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}

void cMainMenu::Replay(wxCommandEvent& evt) {
	if (!firstTime) {
		//soundPlayer->Play("Previews/prevTrack.wav");
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No preview created", "Can't play preview");
		warning.Center();
		warning.SetExtendedMessage("Please, add track a and create a preview.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}

void cMainMenu::loadWavSpec(wxCommandEvent& evt) {
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
	else {			//verifico si el string ya está dentro de vector
		wavToSpecPath = pathSelected;
		wavToSpecName = stringSelected;
		t_currentSpec->SetLabel("Current WAV selected: " + wavToSpecName);
		t_currentSpec->Refresh();
	}
	evt.Skip();
}

void cMainMenu::createSpec(wxCommandEvent& evt) {
	string ventanaElegida = ddm_spect->GetStringSelection();
	if (!(wavToSpecName.empty())) {

		string nfft_s = ddm_nfft->GetStringSelection();
		string overlap_s = ddm_overlap->GetStringSelection();

		

		if (nfft_s.empty() || overlap_s.empty()) {
			//Warning
			wxMessageDialog warning(this, "No parameter chosen", "Can't create spectogram");
			warning.Center();
			warning.SetExtendedMessage("Please, write a valid parameter for this type of window.");
			warning.ShowModal();
			warning.Hide();
		}
		else {
			int nfft = stoi(nfft_s);
			int overlap = stoi(overlap_s);

			if (nfft < overlap) {
				//Warning
				wxMessageDialog warning(this, "Invalid parameter chosen", "Can't create spectogram");
				warning.Center();
				warning.SetExtendedMessage("NFFT must be greater than overlap.");
				warning.ShowModal();
				warning.Hide();
			}
			else {

				if (ventanaElegida.empty()) {
					//No se elegió ninguna ventana
					//Warning
					wxMessageDialog warning(this, "No window chosen", "Can't create spectogram");
					warning.Center();
					warning.SetExtendedMessage("Please, select a type of window to create a spectogram.");
					warning.ShowModal();
					warning.Hide();
				}
				else if (!(tx_specWindParam->IsEmpty())) {
					//Si el textbox tiene algo es porque está la 8, 9 o 10, porque solo se vacía si cambíe de ventana 
					double param = stod((string)tx_specWindParam->GetStringSelection());

					//LLAMAR A LA FUNCIÓN DE VENTANA CON PARAMETRO Y NOMBRE
					es.generateSpectrum(wavToSpecPath, nfft, overlap, ventanaElegida, param, param, param);
				}
				else if (!((ventanaElegida == WindowsList[8]) || (ventanaElegida == WindowsList[9]) || (ventanaElegida == WindowsList[10]))) {
					//Si el text box está vacío y si no es la ventana 8, 9 o 10, está todo joya, tengo una ventana sin parámetro

					//LLAMAR A LA FUNCIÓN DE VENTANA CON NOMBRE
					es.generateSpectrum(wavToSpecPath, nfft, overlap, ventanaElegida, 0, 0, 0);
				}
				else {
					//El text box está vacío y la ventana es la 8, 9 o 10...Falta parámetro
					//Warning
					wxMessageDialog warning(this, "No parameter chosen", "Can't create spectogram");
					warning.Center();
					warning.SetExtendedMessage("Please, write a valid parameter for this type of window.");
					warning.ShowModal();
					warning.Hide();
				}
			}
		}
	}
	else {
		//Warning
		wxMessageDialog warning(this, "No WAV file loaded", "Can't create spectogram");
		warning.Center();
		warning.SetExtendedMessage("Please, select a WAV file to create a spectogram.");
		warning.ShowModal();
		warning.Hide();
	}
	evt.Skip();
}
void cMainMenu::detectWindowChange(wxCommandEvent& evt) {
	t_specGauss->Hide();
	t_specExp->Hide();
	t_specKaiser->Hide();
	tx_specWindParam->Clear();
	tx_specWindParam->Hide();
	

	string ventanaElegida = ddm_spect->GetStringSelection();						//verificar que el imput esté en la lista de esa mierda

	if (ventanaElegida == WindowsList[8]) {
		t_specGauss->Show();
		tx_specWindParam->Show();
	}
	else if (ventanaElegida == WindowsList[9]) {
		t_specExp->Show();
		tx_specWindParam->Show();
	}
	else if (ventanaElegida == WindowsList[10]) {
		t_specKaiser->Show();
		tx_specWindParam->Show();
	}
	evt.Skip();
}

//bool cMainMenu::portAudioOpen(void) {
//	
//	PaStreamParameters outputParameters;
//
//	outputParameters.device = Pa_GetDefaultOutputDevice();
//	
//	outputParameters.channelCount = NUM_CHANNELS;
//	outputParameters.sampleFormat = BITS_PER_SAMPLE;
//	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
//
//	PaError ret = Pa_OpenStream(&stream, NULL, &outputParameters, 16, paFramesPerBufferUnspecified, 0, &paStreamCallback, NULL, void *userData);
//
//	if (ret != paNoError) {
//		fprintf(stderr, "Pa_OpenStream failed: (err %i) %s\n", ret, Pa_GetErrorText(ret));
//		if (stream)
//			Pa_CloseStream(stream);
//		return false;
//	}
//
//	return true;
//}
//
//int paStreamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
//	
//	size_t numRead = fread(output, BITS_PER_SAMPLE * NUM_CHANNELS, frameCount, fopen("Previews/prevTrack.wav"));
//	output = (uint8_t*)output + numRead * NUM_CHANNELS * BITS_PER_SAMPLE;
//	frameCount -= numRead;
//
//	if (frameCount > 0) {
//		memset(output, 0, frameCount * NUM_CHANNELS * BITS_PER_SAMPLE);
//		return paComplete;
//	}
//
//	return paContinue;
//}