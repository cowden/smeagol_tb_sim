#ifndef SSEDetectorConstruction_h
#define SSEDetectorConstruction_h

/////////////////////////////////////////
// C S Cowden
// Simple Smeagol Experimental Detector Design
/////////////////////////////////////////

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class SSEDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  SSEDetectorConstruction();
  virtual ~SSEDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  G4VPhysicalVolume* absorberPV_; // the absorber physical volume
  G4VPhysicalVolume* gapPV_; // the gap physical volume

  G4bool checkOverlaps_;
};

#endif
