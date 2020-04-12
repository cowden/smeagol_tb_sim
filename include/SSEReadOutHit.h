#ifndef SSEREDOUTHIT_H
#define SSEREDOUTHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"

class G4VTouchable;

class SSEReadOutHit : public G4VHit {
public:
  /**
  * Default constructor
  */
  SSEReadOutHit();

  /**
  * Copy constructor
  */
  SSEReadOutHit(const SSEReadOutHit &);

  /**
  * basic default constructor
  */
  virtual ~SSEReadOutHit();

  /**
  * equality comparison operator
  */ 
  G4bool operator==(const SSEReadOutHit &) const;

  /**
  * defining the new operator.  This is required.
  */
  inline void *operator new(size_t);
  inline void operator delete(void *);

  /**
  * assignment operator
  */
  const SSEReadOutHit & operator=(const SSEReadOutHit &);

  /**
  * Update the visualization based on the hit.
  */
  virtual void Draw();

  /**
  * Print some information to the log
  */
  virtual void Print();

private:

  G4int nPhotons_;

};

typedef G4THitsCollection<SSEReadOutHit> SSEReadOutHitsCollection;

extern G4ThreadLocal G4Allocator<SSEReadOutHit>* SSEReadOutHitAllocator;

inline void* SSEReadOutHit::operator new(size_t) {
  if ( !SSEReadOutHitAllocator )
    SSEReadOutHitAllocator = new G4Allocator<SSEReadOutHit>;
  return (void *) SSEReadOutHitAllocator->MallocSingle();
}

inline void SSEReadOutHit::operator delete(void *aHit) {
  SSEReadOutHitAllocator->FreeSingle((SSEReadOutHit*)aHit);
}

#endif
