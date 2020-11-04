#include "../public/NewQuestDialog.h"

NewQuestDialog::NewQuestDialog(wxString * Values)
    : wxDialog ( NULL, -1, "Create New Quest", wxDefaultPosition, wxSize ( 450, 450 ) ) {
    
    ComboWorldValues = Values;
    IsMain = true;
    IsFailable = false;
    IsOptional = false;
    
    wxPanel *panel = new wxPanel ( this, -1 );

    wxBoxSizer *vbox = new wxBoxSizer ( wxVERTICAL );

    wxBoxSizer *hbox1 = new wxBoxSizer ( wxHORIZONTAL );
    wxStaticText *st1 =  new wxStaticText ( panel, wxID_ANY,
                                            wxT ( "Quest Name" ) );

    hbox1->Add ( st1, 0, wxRIGHT, 8 );
    QuestNameText = new wxTextCtrl (panel, ID_QuestName);
    hbox1->Add ( QuestNameText, 1 );

    /////

    wxBoxSizer *hboxCombo = new wxBoxSizer ( wxHORIZONTAL );
    wxStaticText *stCombo =  new wxStaticText ( panel, wxID_ANY, wxT ( "Select World" ) );

    hboxCombo->Add ( stCombo, 0, wxRIGHT, 8 );
    ComboWorlds = new wxComboBox ( panel, ID_ComboWorld, wxT("DEFAULT"), wxDefaultPosition, wxSize ( 240, -1 ), 3, ComboWorldValues, wxCB_DROPDOWN |wxCB_READONLY );
    
    ComboWorlds->SetSelection(0);
    
    hboxCombo->Add ( ComboWorlds, 1 );

    vbox->Add ( hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );
    vbox->Add ( hboxCombo, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );

    wxBoxSizer *vboxList = new wxBoxSizer ( wxVERTICAL );

    wxStaticText *stParent =  new wxStaticText ( panel, wxID_ANY, wxT ( "Select Parent Quest" ) );

    vboxList->Add ( stParent, 0, wxEXPAND | wxLEFT | wxTOP, 10 );

    wxArrayString strings;
    strings.Add ( wxT ( "First string" ) );
    strings.Add ( wxT ( "Second string" ) );
    strings.Add ( wxT ( "Third string" ) );
    strings.Add ( wxT ( "Fourth string" ) );
    strings.Add ( wxT ( "Fifth string" ) );
    strings.Add ( wxT ( "Sixth string" ) );

    // Create a ListBox with Single-selection list.
    ListBoxQuest = new wxListBox ( panel, wxID_ANY, wxPoint ( 150, 100 ), wxSize ( 180, 150 ), strings, wxLB_SINGLE );

    //ListBox->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MyFrame::OnListboxRDown), NULL, this);

    vboxList->Add ( ListBoxQuest, ID_QuestList, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10 );
    
    ButtonClear = new wxButton ( panel, ID_ButtonClear, wxT ( "Clear" ) );
    
    vboxList->Add ( ButtonClear, 0, wxALIGN_RIGHT | wxRIGHT | wxTOP, 10 );
    
    vbox->Add ( vboxList, 0, wxEXPAND | wxRIGHT | wxTOP, 10 );

    wxBoxSizer *hbox2 = new wxBoxSizer ( wxHORIZONTAL );

    vbox->Add ( hbox2, 0, wxLEFT | wxTOP, 10 );

    vbox->Add ( -1, 10 );

    wxBoxSizer *hbox4 = new wxBoxSizer ( wxHORIZONTAL );
    MainRadio = new wxRadioButton ( panel, ID_Flags_Radio,
            wxT ( "Main" ) );

    MainRadio->SetValue(true);

    hbox4->Add ( MainRadio );
    SideRadio = new wxRadioButton ( panel, ID_Flags_Radio,
            wxT ( "Side" ) );

    hbox4->Add ( SideRadio, 0, wxLEFT, 10 );
    FailableCheck = new wxCheckBox ( panel, ID_Flags_Check,
                                       wxT ( "Failable" ) );

    hbox4->Add ( FailableCheck, 0, wxLEFT, 10 );

    OptionalCheck = new wxCheckBox ( panel, ID_Flags_Check,
                                       wxT ( "Optional" ) );

    hbox4->Add ( OptionalCheck, 0, wxLEFT, 10 );

    vbox->Add ( hbox4, 0, wxLEFT, 10 );

    vbox->Add ( -1, 25 );

    wxBoxSizer *hbox5 = new wxBoxSizer ( wxHORIZONTAL );
    OkButton = new wxButton ( panel, ID_OkButton, wxT ( "Create" ) );
    OkButton->Enable(false);
    hbox5->Add ( OkButton, 0 );
    vbox->Add ( hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10 );
    
    
    Bind( wxEVT_TEXT, &NewQuestDialog::OnQuestNameChange, this, ID_QuestName );
    Bind( wxEVT_COMBOBOX, &NewQuestDialog::OnQuestNameChange, this, ID_ComboWorld );
    Bind( wxEVT_BUTTON, &NewQuestDialog::OnButtonClearPressed, this, ID_ButtonClear );
    Bind( wxEVT_BUTTON, &NewQuestDialog::OnOkButtonPressed, this, ID_OkButton );
    Bind( wxEVT_RADIOBUTTON, &NewQuestDialog::OnFlagsChanged, this, ID_Flags_Radio );
    Bind( wxEVT_CHECKBOX, &NewQuestDialog::OnFlagsChanged, this, ID_Flags_Check );

    panel->SetSizer ( vbox );
    
    //Utils::GenerateCache();

    Centre();
    
    ShowModal();
    
    

    Destroy();
}


void NewQuestDialog::OnQuestNameChange(wxCommandEvent& event ) {
    if(!QuestNameText->GetValue().IsEmpty() && ComboWorlds->GetSelection() > -1) {
        OkButton->Enable(true);
    }else {
        OkButton->Enable(false);
    }
}

void NewQuestDialog::OnButtonClearPressed(wxCommandEvent& event ) {
    ListBoxQuest->SetSelection(wxNOT_FOUND);
}

void NewQuestDialog::OnOkButtonPressed(wxCommandEvent& event ) {
    std::string QuestName = QuestNameText->GetValue().ToStdString();
    std::string ComboSelectionString = ComboWorlds->GetStringSelection().ToStdString();
    uint8_t ComboIntSelection = ComboWorlds->GetSelection();
    int ParentQuest = ListBoxQuest->GetSelection();
    
    struct QuestData Data = {QuestName, 
                             ComboIntSelection, 
                             ParentQuest, 
                             IsMain, 
                             IsFailable, 
                             IsOptional};
                             
    std::tuple<bool, std::string> Result = Utils::CreateNewQuest(&Data);

    if(std::get<bool>(Result)) {
        wxMessageDialog* dial = new wxMessageDialog ( NULL,
                wxT ( "Quest Created Successfully!" ), wxT ( "Success" ), wxCENTRE | wxOK );
        dial->ShowModal();
        this->Destroy();
    }else {
        
    }
    
}

void NewQuestDialog::OnFlagsChanged(wxCommandEvent& event ) {
    MainRadio->GetValue() ? IsMain = true : IsMain = false;
    IsFailable = FailableCheck->GetValue();
    IsOptional = OptionalCheck->GetValue();
}