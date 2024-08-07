#ifndef CONTACTS_H
#define CONTACTS_H

#include "wx/sizer.h"
#include "wx/window.h"
#include "wx/scrolwin.h"

class contactsStack : public wxScrolledWindow 
{
public:
    contactsStack(wxWindow* parent);

    void AddContactCard(wxBitmap profileImg, wxString name, wxDateTime lastMsgDate, wxString message);
private:
    wxBoxSizer* mainSizer;
};

#endif // !CONTACTS_H
