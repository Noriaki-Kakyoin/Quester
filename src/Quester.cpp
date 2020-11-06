#include "Quester.h"

bool QuesterApp::OnInit() {

    Utils::OpenConsole();

    QuesterFrame *frame = new QuesterFrame();
    frame->Centre();
    frame->Show ( true );

    // Generate Cache & check for first app launch ;
    if ( Utils::GenerateCache() ) {
        wxMessageDialog* dial = new wxMessageDialog ( NULL,
                wxT ( "First use detected" ), wxT ( "Info" ), wxOK );
        dial->ShowModal();
    }

    return true;
}
QuesterFrame::QuesterFrame()
    : wxFrame ( NULL, wxID_ANY, "Quester", wxDefaultPosition, wxSize(500, 450), wxDEFAULT_FRAME_STYLE ) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append ( ID_New, "&New...\tCtrl-N",
                       "Create a new quest file" );
    menuFile->AppendSeparator();
    menuFile->Append ( wxID_EXIT );
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append ( wxID_ABOUT );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append ( menuFile, "&File" );
    menuBar->Append ( menuHelp, "&Help" );

    wxPanel *panel = new wxPanel ( this, wxID_ANY);

    wxBoxSizer *vbox1 = new wxBoxSizer ( wxVERTICAL );
    wxBoxSizer *vbox2 = new wxBoxSizer ( wxVERTICAL );
    wxBoxSizer *hbox1 = new wxBoxSizer ( wxHORIZONTAL );

    wxListCtrl * m_item_list = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 10000), wxLC_REPORT);
    
    m_item_list->InsertColumn(0,_("Name"),wxLIST_FORMAT_LEFT,100);
	m_item_list->InsertColumn(1,_("World"),wxLIST_FORMAT_LEFT,100);
	m_item_list->InsertColumn(2,_("Parent Quest"),wxLIST_FORMAT_LEFT,100);
	
    std::vector<Quest*> ResultQuestList = Utils::GetQuestsAsList();

    for (int i = 0; i < ResultQuestList.size(); i++) {
        m_item_list->InsertItem(i, wxEmptyString);

        m_item_list->SetItem(i, 0, ResultQuestList[i]->Name);
        m_item_list->SetItem(i, 1, ResultQuestList[i]->WorldName);
        m_item_list->SetItem(i, 2, ResultQuestList[i]->ParentQuestName);
    }


    wxSizerFlags flagsExpand(1);
    flagsExpand.Align(1).Expand().Border(wxRIGHT, 8);
    hbox1->Add ( m_item_list, flagsExpand);
    wxButton * CreateNewQuestButton = new wxButton ( panel, ID_OkButton, wxT ( "New Quest" ) );
    wxButton * DeleteQuestButton = new wxButton ( panel, ID_OkButton,    wxT ( "Delete Quest" ) );
    vbox2->Add(CreateNewQuestButton, 1, wxEXPAND);
    vbox2->Add(DeleteQuestButton, 1, wxEXPAND);
    hbox1->Add ( vbox2, 0, 0, 5 );

    vbox1->Add ( hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 8 );

    panel->SetSizerAndFit( vbox1 );

    SetMenuBar ( menuBar );
    CreateStatusBar();

    SetStatusText ( "Welcome to Quester!" );
    Bind ( wxEVT_MENU, &QuesterFrame::OnNewQuest, this, ID_New );
    Bind ( wxEVT_MENU, &QuesterFrame::OnAbout, this, wxID_ABOUT );
    Bind ( wxEVT_MENU, &QuesterFrame::OnExit, this, wxID_EXIT );
}
void QuesterFrame::OnExit ( wxCommandEvent& event ) {
    Close ( true );
}

void QuesterFrame::OnAbout ( wxCommandEvent& event ) {
    wxMessageBox ( "This is a wxWidgets Hello World example",
                   "About Hello World", wxOK | wxICON_INFORMATION );
}

void QuesterFrame::OnNewQuest ( wxCommandEvent& event ) {
    cout << "Main Executable Path: " << wxGetApp().argv[0].ToStdString() << endl;
    wxString * Worlds = Utils::GetDefaultWorldsAsList ( wxGetApp().argv[0].ToStdString() );

    NewQuestDialog *custom = new NewQuestDialog ( Worlds );
    custom->Show ( true );
}
