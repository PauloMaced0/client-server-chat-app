#ifndef CONTACTS_H
#define CONTACTS_H

#include "wx/richtext/richtextctrl.h"
#include "wx/string.h"

class textDisplay : public wxRichTextCtrl 
{
public:
    textDisplay(wxWindow* parent);

private:
    void AddMessage(wxString message, bool isSender);
};

#endif // !CONTACTS_H
