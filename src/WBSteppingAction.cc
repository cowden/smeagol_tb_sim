
#include "WBSteppingAction.h"

#include "CGG4Interface.h"

WBSteppingAction::WBSteppingAction(cg::CGG4Interface * cgint) 
:cg_(cgint)
{ }

WBSteppingAction::~WBSteppingAction()
{ }

void WBSteppingAction::UserSteppingAction(const G4Step * step)
{ 

  cg_->process_step(step);

}
