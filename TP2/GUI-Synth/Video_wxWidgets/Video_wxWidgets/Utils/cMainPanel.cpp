#include "cMainPanel.h"

BEGIN_EVENT_TABLE(cMainPanel, wxPanel)
	EVT_KEY_DOWN(cMainPanel::OnKeyDown)
END_EVENT_TABLE()

cMainPanel::cMainPanel() {

}

cMainPanel::~cMainPanel() {

}

void cMainPanel::OnKeyDown(wxKeyEvent& evt) {
	int i;
	evt.Skip();
}