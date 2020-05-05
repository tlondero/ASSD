#pragma once


#include "wx/wx.h"

class cMain:public wxFrame{
public:
	cMain();
	~cMain();
public:
	wxButton *addMidBtn = nullptr;
	wxTextCtrl * textBoxMid = nullptr;
	wxListBox * midiListBox = nullptr;
	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

