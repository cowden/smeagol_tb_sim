

#include "WBEventAction.h"

#include "G4Event.hh"

#include "CGG4Interface.h"

WBEventAction::WBEventAction(cg::CGG4Interface *cgint)
:cg_(cgint)
{ }

WBEventAction::~WBEventAction()
{ }

void WBEventAction::BeginOfEventAction(const G4Event * event )
{
  cg_->start_event(); 
}

void WBEventAction::EndOfEventAction(const G4Event * event )
{ }
