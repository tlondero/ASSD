#pragma once
#include "wx/wx.h"

class cMainPanel : public wxPanel
{
public:

    cMainPanel();
    ~cMainPanel();
    cMainPanel(wxFrame* parent);

    void OnKeyDown(wxKeyEvent& event);

    DECLARE_EVENT_TABLE()
};