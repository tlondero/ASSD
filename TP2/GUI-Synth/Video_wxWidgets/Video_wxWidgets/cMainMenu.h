#pragma once
#include "wx/wx.h"
//#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/combobox.h>
#include <wx/clntdata.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>

using namespace std;

class cMainMenu : public wxFrame
{
public:
	cMainMenu();
	~cMainMenu();

public:
	//Grid Bag Sizer
	wxSizer* gbSize = nullptr;

	//Botones
	wxButton* b_cargarMidi = nullptr;
	wxButton* b_crearWav = nullptr;
	wxButton* b_addTrack = nullptr;
	wxButton* b_removeTrack = nullptr;
	wxButton* b_preview = nullptr;
	wxButton* b_addEffWav = nullptr;
	wxButton* b_removeEffWav = nullptr;
	wxButton* b_toggleMic = nullptr;
	wxButton* b_addEffMic = nullptr;
	wxButton* b_removeEffMic = nullptr;

	wxButton* b_generateSpect = nullptr;

	//Drop Down Menu (Combo Box)
	wxComboBox* ddm_track = nullptr;
	wxComboBox* ddm_instrumento = nullptr;
	wxComboBox* ddm_wavEff = nullptr;
	wxComboBox* ddm_micEff = nullptr;

	//Lists Box
	wxListBox* lb_trackParam = nullptr;
	wxListBox* lb_trackValue = nullptr;
	wxListBox* lb_tracks = nullptr;
	wxListBox* lb_wavEff = nullptr;
	wxListBox* lb_micEff = nullptr;

	//Images
	wxStaticBitmap* img_Spectogram = nullptr;

	//Text
	wxStaticText* t_tackDdm = nullptr;
	wxStaticText* t_instrumentoDdm = nullptr;
	wxStaticText* t_paramList = nullptr;
	wxStaticText* t_valueList = nullptr;
	wxStaticText* t_previewDdm = nullptr;
	wxStaticText* t_effectWavDdm = nullptr;
	wxStaticText* t_effectMicDdm = nullptr;

	vector<string> choices;			//vector de strings que tiene los mismos que el DDM y en el mismo orden

	void OnButtonClicked1(wxCommandEvent& evt);
	void AddWavToList(wxCommandEvent& evt);
	void DeleteWavFromList(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};