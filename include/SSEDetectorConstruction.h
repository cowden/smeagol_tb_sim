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


  G4VPhysicalVolume* absorberPV_; // the absorber physical volume
  G4VPhysicalVolume* gapPV_; // the gap physical volume

  G4bool checkOverlaps_;
};

#endif
