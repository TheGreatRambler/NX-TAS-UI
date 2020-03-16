#pragma once

#include <rapidjson/document.h>
#include <wx/utils.h>
#include <wx/wx.h>

#include "drawingCanvas.hpp"

// This class handles both opening up a savestate and creating the first savestate
class SavestateSelection : public wxFrame {
private:
	wxBoxSizer* imageSizer;
	wxBoxSizer* buttonSizer;
	wxBoxSizer* fullSizer;

	rapidjson::Document* mainSettings;

	// Used to block input to everything while this is open
	wxWindowDisabler* windowDisabler;

	// Will be set if the dialog is supposed to load savestates, not create the first one
	bool savestateLoadDialog;

	// To view the frames, will use if needed
	DrawingCanvasBitmap* currentScreen;
	// Only use with savestate loading
	DrawingCanvasBitmap* savestateFrameTarget;

	void onIdle(wxIdleEvent& event);

public:
	SavestateSelection(rapidjson::Document* settings, bool isSavestateLoadDialog);

	void open() {
		// This exists apparently
		// https://docs.wxwidgets.org/3.0/classwx_window.html#a596b1715edfc7609f352b2e000ecbaec
		Show();
		// Disable every window but ourselves
		windowDisabler = new windowDisabler(this);
	}

	void close() {
		Hide();
		// Deleting the window disabler enables all other windows
		delete windowDisabler;
	}

	void onIdle(wxIdleEvent& event);

	DECLARE_EVENT_TABLE();
}