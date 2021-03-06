#ifndef _INC_MAINFRAME
#define _INC_MAINFRAME

#include "wx/wx.h"
#include "wx/wfstream.h"
#include "wx/grid.h"
#include "wx/cmdline.h"
#include "wx/stopwatch.h"

#include "FourDOCanvas.hpp"

#include "types.h"
#include "Console.h"
#include "ISOBrowser.h"

#include "fourdo.xpm" // Include the application's icon

class MainFrame : public wxFrame
{
public:
	 MainFrame(wxCmdLineParser* parser);
	 ~MainFrame();

	void OnMenuFileOpenISO   ( wxCommandEvent &event );
	void OnMenuFileOpenCode  ( wxCommandEvent &event );
	void OnMenuFileExit      ( wxCommandEvent &event );
	void OnMenuToolsBrowseISO( wxCommandEvent &event );
	void OnMenuConsoleReset  ( wxCommandEvent &event );
	void OnMenuHelpAbout     ( wxCommandEvent &event );
	void OnMainTimer	     ( wxTimerEvent   &event );

private:
	void InitializeMenu ();
	void DoTest();
	void RunCycles();
	bool ParseCommandLineArgs();
	
	void BrowseIso();
	void BrowseIso(wxString fileName);

	void ConsoleReset();
	
	Console* m_con;
	bool     m_consoleRunning;

	FourDOCanvas*  ctlFourDOCanvas;
	wxTimer*	   tmrMain;
	
	bool     m_isDebug;
	bool     m_loadIso;
	wxString m_fileName;
	
	DECLARE_EVENT_TABLE ()
};

#endif //_INC_MAINFRAME
