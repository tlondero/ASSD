#pragma once

#include "wx/wx.h"
#include <wx/wfstream.h>
#include <wx/combobox.h>
#include <wx/clntdata.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/sound.h>

#include <fstream>
#include <vector>

#include "General.h"
#include "Utils/Tracks.h"
#include "MidiParser.h"
#include "UserInput/UserInput.h"
#include "Controllers/ControllerOfControllers.h"
#include "Controllers/WavController.h"
#include "Espectrograma/EspectroGenerator.h"

#define BUTTON_X 150
#define BUTTON_Y 50
#define BUTTON_SP 5

#define DDM_X 300
#define DDM_Y 30

#define TEXT_X 150
#define TEXT_Y 15

#define LB_X 300
#define LB_Y 300

#define COL2 450
#define COL3 2*450
#define COL4 3*450

using namespace std;

class cMainMenu : public wxFrame
{
public:
	cMainMenu();
	~cMainMenu();

private:
	
	//Toolbar
	wxToolBar* m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;
		
	//Botones
	wxButton* b_cargarMidi = nullptr;
	wxButton* b_crearWav = nullptr;
	wxButton* b_addTrack = nullptr;
	wxButton* b_removeTrack = nullptr;
	wxButton* b_preview = nullptr;
	wxButton* b_addEffTrack = nullptr;
	wxButton* b_removeEffTrack = nullptr;
	wxButton* b_addEffWav = nullptr;
	wxButton* b_removeEffWav = nullptr;
	wxButton* b_toggleMic = nullptr;
	wxButton* b_addEffMic = nullptr;
	wxButton* b_removeEffMic = nullptr;

	wxButton* b_savePreview = nullptr;
	wxButton* b_replay = nullptr;

	wxButton* b_loadSpec = nullptr;
	wxButton* b_updateSpec = nullptr;


	//Drop Down Menu (Combo Box)
	wxComboBox* ddm_track = nullptr;
	wxComboBox* ddm_instrumento = nullptr;
	wxComboBox* ddm_wavEff = nullptr;
	wxComboBox* ddm_micEff = nullptr;

	wxComboBox* ddm_spect = nullptr;

	wxComboBox* ddm_nfft = nullptr;
	wxComboBox* ddm_overlap = nullptr;

	//Lists Box
	wxListBox* lb_tracks = nullptr;
	wxListBox* lb_wavEff = nullptr;
	wxListBox* lb_micEff = nullptr;


	//Text
	wxStaticText* t_tackDdm = nullptr;
	wxStaticText* t_instrumentoDdm = nullptr;
	wxStaticText* t_paramList = nullptr;
	wxStaticText* t_previewDdm = nullptr;
	wxStaticText* t_effectWavDdm = nullptr;
	wxStaticText* t_effectMicDdm = nullptr;
	wxStaticText* t_specWindType = nullptr;
	wxStaticText* t_currentSpec = nullptr;
	wxStaticText* t_specWindParam = nullptr;

	wxStaticText* t_nfft = nullptr;
	wxStaticText* t_overlap = nullptr;

	
	//Text Control (INSTRUMENTOS)
	wxTextCtrl* tx_organA = nullptr;
	wxTextCtrl* tx_organR = nullptr;
	wxTextCtrl* tx_organS = nullptr;

	wxTextCtrl* tx_fluteA = nullptr;
	wxTextCtrl* tx_fluteR = nullptr;
	wxTextCtrl* tx_fluteS = nullptr;

	wxTextCtrl* tx_guitarRf = nullptr;
	wxTextCtrl* tx_eguitarRf = nullptr;

	wxTextCtrl* tx_drumRf = nullptr;
	wxTextCtrl* tx_drumB = nullptr;

	//Text Control (WavEff)
	wxTextCtrl* tx_effGEco = nullptr;
	wxTextCtrl* tx_effMEco = nullptr;
	wxTextCtrl* tx_effRev = nullptr;

	//Text Control (VENTANAS)
	wxTextCtrl* tx_specWindParam = nullptr;


	//Dinmac Texts (INSTRUMENTOS)
	wxStaticText* t_organA = nullptr;
	wxStaticText* t_organR = nullptr;
	wxStaticText* t_organS = nullptr;

	wxStaticText* t_fluteA = nullptr;
	wxStaticText* t_fluteR = nullptr;
	wxStaticText* t_fluteS = nullptr;

	wxStaticText* t_guitarRf = nullptr;
	wxStaticText* t_eguitarRf = nullptr;

	wxStaticText* t_drumRf = nullptr;
	wxStaticText* t_drumB = nullptr;

	wxStaticText* t_bell = nullptr;

	wxStaticText* t_playMusic = nullptr;

	//Dinamic Text (WavEff)
	wxStaticText* t_effGEco = nullptr;
	wxStaticText* t_effMEco = nullptr;
	wxStaticText* t_effRev = nullptr;

	//Dinamic Texts (VENTANAS)
	wxStaticText* t_specGauss = nullptr;
	wxStaticText* t_specExp = nullptr;
	wxStaticText* t_specKaiser = nullptr;

	//Clases de soporte y las que se nos hacian lindas poner acá
	bool fullscreen = false;

	MidiParser midi;
	vector<Tracks> midiTranslated;
	UserInput ui;
	UserInput uiPreview;
	ControllerOfControllers myCC;
	vector<wxStaticText*> t_toShow;
	vector<wxTextCtrl*> tx_toShow;

	vector<wxStaticText*> t_WavEfftoShow;
	vector<wxTextCtrl*> tx_WavEfftoShow;

	string selecetedMidi;											//vector de strings que tiene los mismos que el DDM y en el mismo orden
	WavController myWC;
	//string songPlaying;
	bool firstTime = true;
	string wavToSpecPath;
	string wavToSpecName;
	EspectroGenerator es;


	//Functions
	void OnKeyDown(wxKeyEvent& evt);

	void OnMenuFullscreen(wxCommandEvent& evt);			
	void OnMenuExit(wxCommandEvent& evt);	

	void AddMidiToProgram(wxCommandEvent& evt);
	void AddTrackToDdm(wxCommandEvent& evt);
	void DeleteTrackToDdm(wxCommandEvent& evt);
	void AddTrack(wxCommandEvent& evt);
	void detectInstrumentChange(wxCommandEvent& evt);
	void addValueToParam(wxCommandEvent& evt);
	void RemoveTrack(wxCommandEvent& evt);
	void CreateWav(wxCommandEvent& evt);
	void CreatePreview(wxCommandEvent& evt);
	void savePreview(wxCommandEvent& evt);
	void Replay(wxCommandEvent& evt);
	void loadWavSpec(wxCommandEvent& evt);
	void createSpec(wxCommandEvent& evt);
	void detectWindowChange(wxCommandEvent& evt);
	void addEffTrack(wxCommandEvent& evt);
	void removeEffTrack(wxCommandEvent& evt);
	void addEffWav(wxCommandEvent& evt);
	void removeEffWav(wxCommandEvent& evt);
	void detectWavEffChange(wxCommandEvent& evt);

	bool portAudioOpen(void);

	void addToDdm(vector<string> tracks, wxComboBox* ddm);
	vector<string> midiToStringDdm(vector<Tracks> MidiParsed);		//Funció que recibe el vector de tracks que devuelve el midi parser
																	//y devuelve el vector de strings que utilizará el ddm para mostrar los tracks.
	
	wxDECLARE_EVENT_TABLE();
};