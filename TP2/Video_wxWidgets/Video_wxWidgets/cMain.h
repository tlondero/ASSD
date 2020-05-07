#pragma once
#include "wx/wx.h"
//#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/combobox.h>
#include <wx/clntdata.h>

using namespace std;

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox* m_list1 = nullptr;
	wxButton* m_btn2 = nullptr;
	wxComboBox* m_ddm = nullptr;

	vector<string> choices;			//vector de strings que tiene los mismos que el DDM y en el mismo orden

	void OnButtonClicked1(wxCommandEvent& evt);
	void AddWavToList(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

