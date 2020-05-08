#pragma once

#include "wx/wx.h"
#include "cMainMenu.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

public:
	virtual bool OnInit();

private:
	cMainMenu* m_frame1 = nullptr;

};

