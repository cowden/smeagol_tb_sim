#ifndef WBDETECTORCONSTRUCTION_H
#define WBDETECTORCONSTRUCTION_H

/******************************
* C S Cowden
* Construct a big W block.
******************************/

#include "G4VUserDetectorConstruction.hh"
#include "G4MaterialPropertiesTable.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Box;

class WBDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  WBDetectorConstruction();
  virtual ~WBDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  virtual void ConstructSDandField();

private:

  G4double width_;
  G4double depth_;

  G4Box * box_;
  G4LogicalVolume * worldlv_;
  G4VPhysicalVolume * worldpv_;
  G4LogicalVolume * boxlv_;
  G4VPhysicalVolume * boxpv_;
  
};

#endif
