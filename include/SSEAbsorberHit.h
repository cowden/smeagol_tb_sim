#ifndef SSEABSORBERHIT_H
#define SSEABSORBERHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"

class G4VTouchable;
class G4Track;

class SSEAbsorberHit : public G4VHit {
public:
  
  /**
  * Default constructor
  */
  SSEAbsorberHit();

  /**
  * Copy constructor
  */
  SSEAbsorberHit(const SSEAbsorberHit &);

  /**
  * basic default destructor
  */
  virtual ~SSEAbsorberHit();


  /**
  * equality comparison operator
  */
  G4bool operator==(const SSEAbsorberHit &) const;

  /**
  * defining the new operator.  This is required.
  */
  inline void *operator new(size_t);
  inline void operator delete(void *);

  /**
  * assignment operator
  */
  const SSEAbsorberHit & operator=(const SSEAbsorberHit &);

  /**
  * Update the visualization based on the hit
  */
  virtual void Draw();

  /**
  * Print some information to the lag
  */
  virtual void Print();

  /**
  * Add data to the hit
  */
  virtual void AddTrack(const G4Track *);

private:

  G4double e_threshold_;

  G4int nTracks_;
  G4int nCharged_;

};

typedef G4THitsCollection<SSEAbsorberHit> SSEAbsorberHitsCollection;

extern G4ThreadLocal G4Allocator<SSEAbsorberHit>* SSEAbsorberHitAllocator;

inline void* SSEAbsorberHit::operator new(size_t) {

  if ( !SSEAbsorberHitAllocator )
    SSEAbsorberHitAllocator = new G4Allocator<SSEAbsorberHit>;

  return (void *) SSEAbsorberHitAllocator->MallocSingle();
}

inline void SSEAbsorberHit::operator delete(void *aHit) { 
  SSEAbsorberHitAllocator->FreeSingle((SSEAbsorberHit*)aHit);
}

#endif
