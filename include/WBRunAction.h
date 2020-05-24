#ifndef WBRUNACTION_H
#define WBRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class WBRunAction : public G4UserRunAction {
public:
  WBRunAction();
  virtual ~WBRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

};

#endif
