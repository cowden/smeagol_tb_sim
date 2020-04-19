#ifndef SSEREADOUTSD_H
#define SSEREADOUTSD_H

/////////////////////////////////////////////
// C S Cowden
/////////////////////////////////////////////

#include "G4VSensitiveDetector.hh"

#include "SSEReadOutHit.h"

#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4VPhysicalVolume;

/**
* Smeagol Simple  Ecal (SSE) sensitive detector class
* for the readout geometries
*/
class SSEReadOutSD: public G4VSensitiveDetector {
public:

  /**
  * Default Constructor
  * Pass the sensitive detector name
  * Parameters:
  *  * name
  *  * number of segments along X-axis
  *  * number of segments along Y-axis
  */
  SSEReadOutSD(G4String , unsigned, unsigned);

  /**
  * Default destructor
  */
  virtual ~SSEReadOutSD();


  /**
  * Initialize
  */
  virtual void Initialize(G4HCofThisEvent *);
  
  /**
  * Process hits - virtual function inherited from G4VSensitiveDetector
  * If we set up the pmt volumes with correct optical properties and 
  * the surface properties between them correctly, photons pass into 
  * the PMT as expected.  We don't have to implement the same solutaion
  * as in the LXe example.
  */
  virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

  /**
  * Process the optical photon hits. 
  * See the LXe example.  Since the optical photon is absorbed 
  * at the surface, we have to artificially push hits from the 
  * boundary process.  We shall watch the OpBoundary process
  * in SteppingAction.
  */ 
  virtual G4bool ProcessOpticalHits(G4Step*, G4TouchableHistory*);

  /** 
  * Action to take at the end of an event
  */
  virtual void EndOfEvent(G4HCofThisEvent *);

private:


  unsigned nX_;
  unsigned nY_;
  unsigned nSegments_;

  SSEReadOutHitsCollection * hitCollection_;

};

#endif
