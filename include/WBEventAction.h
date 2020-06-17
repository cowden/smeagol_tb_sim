#ifndef WBEVENTACTION_H
#define WBEVENTACTION_H

#include "G4UserEventAction.hh"
#include "globals.hh"


namespace cg {
  class CGG4Interface;
}

class WBEventAction: public G4UserEventAction {

public:

  WBEventAction(cg::CGG4Interface *);
  ~WBEventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:

  cg::CGG4Interface * cg_;

};

#endif
