#include "text_display.h"
#include "wx/sizer.h"

textDisplay::textDisplay(wxWindow* parent)
    : wxRichTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(370, 200), wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE) 
{
    this->SetBackgroundColour(wxColor(38, 38, 40));

    wxBoxSizer* message_box_sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(message_box_sizer);

    // Example
    wxString msg = "Hello, how are you? qwldkqklw jqwjk jklqwjklw jklqw lwq kljqw jklwq kljqw jlk qw\n";
    this->AddMessage(msg, false);

    msg = "I'm good, thanks! How about you ewfewkfwekj kjwe jkewjkkjew jkewj ew jkjkefwjkef wjk ewjke wjk?\n";
    this->AddMessage(msg, true);
    // !Example
}

void textDisplay::AddMessage(wxString message, bool isSender)
{
    wxRichTextAttr txt;

    if (isSender) {
        txt.SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
        txt.SetLeftIndent(600);
        this->BeginStyle(txt);
        this->WriteText(message);
        this->EndStyle();
    } else {
        txt.SetRightIndent(600);
        txt.SetAlignment(wxTEXT_ALIGNMENT_LEFT);
        this->BeginStyle(txt);
        this->WriteText(message);
        this->EndStyle();

        this->BeginStyle(wxRichTextAttr()); // Use default style for the empty line
        this->WriteText("\n"); // Insert an empty line
        this->EndStyle();
    }
}
