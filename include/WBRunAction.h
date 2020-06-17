#ifndef WBRUNACTION_H
#define WBRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>

class G4Run;

namespace cg {
  class CGG4Interface;
}

class WBRunAction : public G4UserRunAction {
public:
  WBRunAction(cg::CGG4Interface *);
  virtual ~WBRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:

  cg::CGG4Interface * cg_;
  

};

#endif
