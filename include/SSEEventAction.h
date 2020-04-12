#ifndef SSEEVENTACTION_H
#define SSEEVENTACTION_H


#include "G4UserEventAction.hh"

#include "globals.hh"


class SSEEventAction: public G4UserEventAction {

public:

  SSEEventAction();
  ~SSEEventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

private:




};

#endif
