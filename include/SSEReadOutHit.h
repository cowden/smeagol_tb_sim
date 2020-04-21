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


  /**
  * Add data to the hit
  * pass a pointer to a touchable that corresponds to the readout segment.
  */
  virtual void Add(const G4VTouchable *);

  /**
  * Set the x index (column) of the segment
  */
  inline virtual void SetColumn(unsigned col) { col_ = col; }

  /**
  * Return the column index of the segment
  */
  inline virtual unsigned GetColumn() const { return col_; }

  /**
  * Set the y index (row) of the segment.
  */
  inline virtual void SetRow(unsigned row) { row_ = row; }

  /**
  * Return the row index of the segment.
  */
  inline virtual unsigned GetRow() const { return row_; }

  /**
  * Set the physical volume for this hit.
  */
  virtual void SetPhysVol(G4VPhysicalVolume * vol) { physVol_ = vol; }


  /**
  * Get the number of photons incident in the SD.
  */
  G4int GetHitCount() const { return nPhotons_; }


  /**
  * Set the position of the segment.
  */
  inline virtual void SetPosition(G4ThreeVector p) { pos_ = p; }
  
  /**
  * Get the position of segment
  */
  inline virtual G4ThreeVector GetPosition() const { return pos_; }

  /**
  * Set the rotation of the segment.
  */
  inline virtual void SetRotation(G4RotationMatrix r) { rot_ = r; }

  /**
  * Get the rotation of the segment.
  */
  inline virtual G4RotationMatrix GetRotation() const { return rot_; }

  /**
  * Set the logical volume.
  */
  inline virtual void SetLogicalVolume(G4LogicalVolume * log ) { logVol_ = log; }

  /**
  * Get the logical volume.
  */
  inline virtual G4LogicalVolume * GetLogicalVolume() const { return logVol_; }


  /**
  * Set segment dimensions
  */
  inline virtual void SetDimensions(G4double x, G4double y, G4double z) {
    wx_ = x;
    wy_ = y;
    wz_ = z;
  }


  /**
  * Get segment dimensions
  */



private:

  G4int nPhotons_;

  unsigned col_;
  unsigned row_;

  const G4VTouchable * touchable_;
  G4VPhysicalVolume * physVol_;
  G4LogicalVolume * logVol_;

  G4double wx_;
  G4double wy_;
  G4double wz_;

  G4ThreeVector pos_;
  G4RotationMatrix rot_;
  

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
