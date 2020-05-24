#ifndef SSEDetectorConstruction_h
#define SSEDetectorConstruction_h

/////////////////////////////////////////
// C S Cowden
// Simple Smeagol Experimental Detector Design
/////////////////////////////////////////

#include <string>
#include "H5Cpp.h"

#include "G4VUserDetectorConstruction.hh"
#include "G4MaterialPropertiesTable.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4PVReplica;

class SSEDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  SSEDetectorConstruction();
  virtual ~SSEDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  virtual void ConstructSDandField();

private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  /**
  * Load the material property table stored in the hdf5 file whose handle is `file`.
  * Get the properties table in array/dataset indicated by the string table.
  * Thie function returns the G4MaterialPropertiesTable needed to support optical
  * photons.
  * It defines the following properties (in order of array columsns after energy):
  *  * RINDEX
  *  * ABSLENGTH
  * Energy is assumed in units of eV and absorption length in units of m.
  */
  G4MaterialPropertiesTable * LoadMaterialPropertiesTable(H5::H5File & , const char *);

  /**
  * Dump material properties by detector elements to the log file.
  */
  void DumpDetectorMaterialProperties();



  // ------------------------------------------
  // member data

  G4double world_width_;
  G4double world_height_;
  G4double width_;
  G4double height_;
  G4double ro_height_;

  unsigned nXSegments_;
  unsigned nYSegments_; 

  G4LogicalVolume* absorberLog_;
  G4LogicalVolume* readoutLog_;
  G4VPhysicalVolume* absorberPV_; // the absorber physical volume
  G4VPhysicalVolume* readoutPV_; // the gap physical volume

  G4LogicalVolume* roSegmentLog_;
  G4PVReplica* roSegments_;

  G4bool checkOverlaps_;
};

#endif
