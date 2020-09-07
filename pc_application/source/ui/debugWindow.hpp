#pragma once

#include <memory>
#include <wx/wx.h>

#include "../shared_network_code/networkInterface.hpp"

// Has a bunch of buttons for debugging purposes
class DebugWindow : public wxFrame {
private:
	std::shared_ptr<CommunicateWithNetwork> networkInstance;

	wxBoxSizer* buttonSizer;

	wxButton* pauseButton;
	wxButton* unpauseButton;
	wxButton* getFramebufferButton;

	void onPausePressed(wxCommandEvent& event);
	void onUnpausePressed(wxCommandEvent& event);
	void onGetFramebufferPressed(wxCommandEvent& event);
	void onClose(wxCloseEvent& event);

public:
	DebugWindow(wxFrame* parent, std::shared_ptr<CommunicateWithNetwork> networkImp);

	DECLARE_EVENT_TABLE();
};