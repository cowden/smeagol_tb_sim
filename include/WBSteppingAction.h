

#ifndef WBSTEPPINGACTION_H
#define WBSTEPPINGACTION_H


/////////////////////////////////////////////
// C S Cowden
/////////////////////////////////////////////

#include"G4UserSteppingAction.hh"
#include "G4OpBoundaryProcess.hh"

#include "globals.hh"

namespace cg {
  class CGG4Interface;
}

class WBSteppingAction: public G4UserSteppingAction {
public:

  WBSteppingAction(cg::CGG4Interface *);
  virtual ~WBSteppingAction();
  virtual void UserSteppingAction(const G4Step *);

private:

  cg::CGG4Interface * cg_;

};


#endif
