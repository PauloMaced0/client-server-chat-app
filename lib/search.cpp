#include "search.h"

searchBox::searchBox(wxWindow* parent)
    : wxSearchCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER) 
{
    this->ShowCancelButton(true);
    this->ShowSearchButton(true);
}
