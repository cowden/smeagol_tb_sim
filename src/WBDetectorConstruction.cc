
#include "WBDetectorConstruction.h"

#include "G4Box.hh"
#include"G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "SSEAbsorberSD.h"
#include "G4SDManager.hh"


WBDetectorConstruction::WBDetectorConstruction()
:G4VUserDetectorConstruction()
,width_(150*cm)
,depth_(150*cm)
{ }

WBDetectorConstruction::~WBDetectorConstruction()
{ }

G4VPhysicalVolume* WBDetectorConstruction::Construct()
{

  // get the material
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_W");
  auto W = G4Material::GetMaterial("G4_W");

  // create a giant box
  box_ = new G4Box("Box",width_/2.,width_/2.,depth_/2.);
  worldlv_ = new G4LogicalVolume(box_,W,"World");
  worldpv_ = new G4PVPlacement(0,G4ThreeVector(),worldlv_,"World",0,false,0,false);

  boxlv_ = new G4LogicalVolume(box_,W,"Box");
  boxpv_ = new G4PVPlacement(0,G4ThreeVector(),boxlv_,"Box",worldlv_,false,0,false);

  // return the volume 
  return boxpv_;

}

void WBDetectorConstruction::ConstructSDandField()
{

  if ( !boxlv_ ) return;

  // absorber SD
  G4cout << "Constructing SSEAbosrberSD" << G4endl;
  SSEAbsorberSD* absSD = new SSEAbsorberSD("SSEAbosrberSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(absSD);

  SetSensitiveDetector(boxlv_,absSD); 

}
