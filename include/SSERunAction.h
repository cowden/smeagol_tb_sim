#ifndef SSERUNACTION_H
#define SSERUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;


class SSERunAction : public G4UserRunAction {
public:
  SSERunAction();
  virtual ~SSERunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
};


#endif
