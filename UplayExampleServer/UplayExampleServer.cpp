// UplayExampleServer.cpp : Defines the entry point for the console application.
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#include <wx/wx.h>

class MyApp : public wxApp
{
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};

enum
{
	ID_Quit=1,
	ID_About
};


bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
		wxSize(450, 350));

	frame->Connect( ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction) &MyFrame::OnQuit );
	frame->Connect( ID_About, wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction) &MyFrame::OnAbout );

	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

#define ID_LISTBOX 101

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame( NULL, -1, title, pos, size )
{
	wxMenuBar *menuBar = new wxMenuBar;

	wxMenu *menuFile = new wxMenu;

	menuFile->Append( ID_About, _("&About...") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, _("E&xit") );

	menuBar->Append(menuFile, _("&File") );

	wxString choices[] =
	{
		_T("This"),
		_T("is one of my"),
		_T("really"),
		_T("wonderful"),
		_T("examples.")
	};
	
	wxPanel *panel = new wxPanel(this, 0, 0, 10, 10);
	wxListBox *m_listbox = new wxListBox(panel, ID_LISTBOX,
		wxPoint(10,10), wxSize(320,270),
		5, choices, 0 );

	SetMenuBar(menuBar);

	CreateStatusBar();

	SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox( _("wxWidgets Hello World example."), 
		_("About Hello World"),
		wxOK|wxICON_INFORMATION, this );
}


std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}



/*
int main(int argc, char* argv[])
{
	Fl_Window *window = new Fl_Window(400,380);

	Fl_Button *button = new Fl_Button(10, 10, 100, 20, "button");

	Fl_Browser *browser = new Fl_Browser(20, 40, 360, 300);
	char buffer[32];
	for (int i = 0; i < 10; i++) {
		sprintf(buffer, "Client %d", i);
		browser->add(buffer);
	}
	browser->activate();
	browser->show();
	//browser->item_select("Client 0", 0);
	for (int i = 1; i < 10; i++)
		browser->select(i);

	window->end();
	window->show(argc, argv);
	return Fl::run();

	try
	{
		boost::asio::io_service io_service;

		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		for (;;)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
*/