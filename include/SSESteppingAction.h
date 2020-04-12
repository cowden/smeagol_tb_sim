

#ifndef SSESTEPPINGACTION_H
#define SSESTEPPINGACTION_H


/////////////////////////////////////////////
// C S Cowden
/////////////////////////////////////////////

#include"G4UserSteppingAction.hh"
#include "G4OpBoundaryProcess.hh"

#include "globals.hh"

class SSESteppingAction: public G4UserSteppingAction {
public:

  SSESteppingAction();
  virtual ~SSESteppingAction();
  virtual void UserSteppingAction(const G4Step *);

private:

};


#endif
