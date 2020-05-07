#pragma once
#include "wx/wx.h"
//#include <wx/filedlg.h>
#include <wx/wfstream.h>

using namespace std;

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton *m_btn1 = nullptr;
	wxTextCtrl *m_txt1 = nullptr;
	wxListBox *m_list1 = nullptr;
	wxButton* m_btn2 = nullptr;

	void OnButtonClicked1(wxCommandEvent& evt);
	void OnButtonClicked2(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

