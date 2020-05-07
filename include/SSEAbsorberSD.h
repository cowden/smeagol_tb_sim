#ifndef SSEABOSRBER_H
#define SSEABOSRBER_Ha

#include "G4VSensitiveDetector.hh"

#include "SSEAbsorberHit.h"

#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4VPhysicalVolume;

class SSEAbsorberSD: public G4VSensitiveDetector {
public:

  /**
  * Default constructor
  */
  SSEAbsorberSD(G4String);

  /**
  * Default destructor
  */
  virtual ~SSEAbsorberSD();

  /**
  * Initialize
  */
  virtual void Initialize(G4HCofThisEvent *);

  /**
  * Process hits
  */
  virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

  /**
  * Action to take at the end of an event.
  */
  virtual void EndOfEvent(G4HCofThisEvent *);

private:

  SSEAbsorberHitsCollection * hitCollection_;

};


#endif
