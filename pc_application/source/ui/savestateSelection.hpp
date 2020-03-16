#include "savestateSelection.hpp"

SavestateSelection::SavestateSlelection(bool isSavestateLoadDialog)
	: wxFrame(NULL, wxIDAny, "Savestate Selection") {
	// Parent is specifically null because this is a separate window that opens
	savestateLoadDialog = isSavestateLoadDialog;

	// Fill sizers
	// Have to have play, pause and frame advance buttons
	// Look to mainWindow for setting sizers
}

// clang-format off
BEGIN_EVENT_TABLE(SavestateSelection, wxFrame)
    EVT_IDLE(SavestateSelection::onIdle)
END_EVENT_TABLE()
// clang-format on

void SavestateSelection::onIdle(wxIdleEvent& event) {
	// Read network, TODO
	if(IsShown()) {
	}
}