///-----------------------------------------------------------------
///
/// @file      SearchIssueDialog.cpp
/// @author    coderuth
/// Created:   5/13/2018 9:26:36 AM
/// @section   DESCRIPTION
///            SearchIssueDialog class implementation
///
///------------------------------------------------------------------

#include "SearchIssueDialog.h"
#include "Book.h"
#include <sstream>

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// SearchIssueDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(SearchIssueDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(SearchIssueDialog::OnClose)
	EVT_BUTTON(ID_DELETEBUTTON,SearchIssueDialog::okButtonClick)
	EVT_BUTTON(ID_WXBUTTON1,SearchIssueDialog::cancelButtonClick)
	EVT_BUTTON(ID_SEARCHBUTTON,SearchIssueDialog::searchButtonClick)
END_EVENT_TABLE()
////Event Table End

SearchIssueDialog::SearchIssueDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

SearchIssueDialog::~SearchIssueDialog()
{
} 

void SearchIssueDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxArrayString arrayStringFor_typeRadio;
	arrayStringFor_typeRadio.Add(_("ID"));
	arrayStringFor_typeRadio.Add(_("Name"));
	typeRadio = new wxRadioBox(this, ID_TYPERADIO, _("Search By"), wxPoint(16, 57), wxSize(275, 44), arrayStringFor_typeRadio, 1, wxRA_SPECIFY_ROWS, wxDefaultValidator, _("typeRadio"));
	typeRadio->SetSelection(0);

	deleteButton = new wxButton(this, ID_DELETEBUTTON, _("OK"), wxPoint(216, 330), wxSize(75, 25), 0, wxDefaultValidator, _("deleteButton"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Cancel"), wxPoint(138, 330), wxSize(75, 25), 0, wxDefaultValidator, _("WxButton1"));

	WxGrid1 = new wxGrid(this, ID_WXGRID1, wxPoint(16, 139), wxSize(275, 176));
	WxGrid1->SetDefaultColSize(175);
	WxGrid1->SetDefaultRowSize(25);
	WxGrid1->SetRowLabelSize(100);
	WxGrid1->SetColLabelSize(25);
	WxGrid1->CreateGrid(6,1,wxGrid::wxGridSelectCells);
	
	WxGrid1->SetRowLabelValue(0, _("Issue ID"));
    WxGrid1->SetRowLabelValue(1, _("Book Taken By")); //from wxSmith 
    WxGrid1->SetRowLabelValue(2, _("Book ID"));
    WxGrid1->SetRowLabelValue(3, _("Book Name"));
    WxGrid1->SetRowLabelValue(4, _("Issued Date")); //from wxSmith 
    WxGrid1->SetRowLabelValue(5, _("Due Date"));

    WxGrid1->SetColLabelValue(0, _("Result"));

	idLabel = new wxStaticText(this, ID_IDLABEL, _("Enter Issue ID"), wxPoint(16, 35), wxDefaultSize, 0, _("idLabel"));

	idField = new wxTextCtrl(this, ID_IDFIELD, _(""), wxPoint(106, 30), wxSize(184, 25), 0, wxDefaultValidator, _("idField"));

	searchButton = new wxButton(this, ID_SEARCHBUTTON, _("Search"), wxPoint(16, 107), wxSize(276, 25), 0, wxDefaultValidator, _("searchButton"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("Search Issue by ID"), wxPoint(5, 6), wxSize(296, 361));

	SetTitle(_("SearchIssueDialog"));
	SetIcon(wxNullIcon);
	SetSize(8,8,317,406);
	Center();
	
	////GUI Items Creation End
}

void SearchIssueDialog::OnClose(wxCloseEvent& /*event*/) {
	Destroy();
}

/*
 * searchButtonClick
 */
void SearchIssueDialog::searchButtonClick(wxCommandEvent& event) {
    FILE *fs;
    Book a, temp;
    int num, pos = 0;
    bool found = false;
    
    std::stringstream ss;
    wxString str = idField->GetValue();
    
    //fs = fopen("Issue.dat", "rb");
//    while (fread(&a, sizeof(a), 1, fs) == 1) {
//        if (a.issueID == wxAtoi(str)) {
//            found = true;
//            temp = a;
//        }
//    }

    fs = fopen("IndexIssue.dat", "rb+"); //open file for reading propose
	while ((num = getw(fs)) != EOF) {
        if (num == wxAtoi(str)) {
            found = true;
            break;
        }
        pos++;
    }
    if (found) {
        
        fs = fopen("Issue.dat", "rb+"); //open file for reading propose
        
        fseek(fs, pos * sizeof(temp), SEEK_SET);
        fread(&temp, sizeof(temp), 1, fs);
        
        ss << temp.issueID;
        WxGrid1->SetCellValue(0, 0, _(ss.str()));
        ss.str(std::string());
        
        WxGrid1->SetCellValue(1, 0, _(temp.stname));
        
        ss << temp.id;
        WxGrid1->SetCellValue(2, 0, _(ss.str()));
        ss.str(std::string());
        
        WxGrid1->SetCellValue(3, 0, _(temp.name));
        
        ss << temp.issued.dd << "-" << temp.issued.mm << "-" << temp.issued.yy;
        WxGrid1->SetCellValue(4, 0, _(ss.str()));
        ss.str(std::string());
        
        ss << temp.duedate.dd << "-" << temp.duedate.mm << "-" << temp.duedate.yy;
        WxGrid1->SetCellValue(5, 0, _(ss.str()));
        ss.str(std::string());

    } else {
        wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Issue found, Try Again?"), wxT("Info"), wxOK | wxICON_EXCLAMATION);
        dial->ShowModal();
    }
    fclose(fs);  
}


/*
 * cancelButtonClick
 */
void SearchIssueDialog::cancelButtonClick(wxCommandEvent& event) {
	EndModal(true);
}

/*
 * okButtonClick
 */
void SearchIssueDialog::okButtonClick(wxCommandEvent& event) {
    EndModal(true);
	// insert your code here
}

/*
 * WxRadioButton1Click
 */
void SearchIssueDialog::WxRadioButton1Click(wxCommandEvent& event)
{
	// insert your code here
}
