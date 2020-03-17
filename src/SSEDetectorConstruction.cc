
#include "SSEDetectorConstruction.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


SSEDetectorConstruction::SSEDetectorConstruction():
  G4VUserDetectorConstruction(),
  checkOverlaps_(true)
{ }


SSEDetectorConstruction::~SSEDetectorConstruction()
{ }

G4VPhysicalVolume* SSEDetectorConstruction::Construct()
{
  DefineMaterials();

  return DefineVolumes(); 
}



void SSEDetectorConstruction::DefineMaterials()
{

  //  Lead
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");

  // silicate
  G4Material* SiO2 = new G4Material("SiO2",2.2*g/cm3,2);
  SiO2->AddElement(nistManager->FindOrBuildElement("Si"),1);
  SiO2->AddElement(nistManager->FindOrBuildElement("O"),2);

  // lead oxide
  G4Material* PbO = new G4Material("PbO",9.53*g/cm2,2);
  PbO->AddElement(nistManager->FindOrBuildElement("Pb"),1);
  PbO->AddElement(nistManager->FindOrBuildElement("O"),1);

  //  Lead-glass
  G4double rho = 3.1*g/cm3;
  G4Material* leadGlass = new G4Material("Lead-Glass",rho,2);
  leadGlass->AddMaterial(SiO2,72*perCent);
  leadGlass->AddMaterial(PbO,28*perCent);

  // Silicon  
  nistManager->FindOrBuildMaterial("G4_Si");

  // galactic world material
  new G4Material("Galactic",1.,1.01*g/mole,CLHEP::universe_mean_density,
    kStateGas,2.73*kelvin,3.e-18*pascal);

}



G4VPhysicalVolume* SSEDetectorConstruction::DefineVolumes()
{ 

  // geometry parameters
  G4double world_width = 50*cm;
  G4double world_height = 1000*cm;

  G4double width = 50*cm;
  G4double height = 900*cm;

  G4double ro_height = 1*mm;

  // get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("Lead-Glass");
  auto readoutMaterial = G4Material::GetMaterial("G4_Si");

  // world
  auto world_shape = new G4Box("World",world_width/2,world_width/2,world_height/2);
  auto world_LV = new G4LogicalVolume(world_shape,absorberMaterial,"World");
  auto world_PV = new G4PVPlacement(0,G4ThreeVector(),world_LV,"World",0,false,0,checkOverlaps_);


  // block
  auto block_shape = new G4Box("Box",width/2,width/2,height/2);
  auto block_LV = new G4LogicalVolume(block_shape,readoutMaterial,"Box");
  auto block_PV = new G4PVPlacement(0,G4ThreeVector(),block_LV,"Box",world_LV,false,0,checkOverlaps_);



  // readout
  auto ro_shape = new G4Box("RO",width/2,width/2,ro_height/2);
  auto ro_LV = new G4LogicalVolume(ro_shape,readoutMaterial,"RO");
  auto ro_PV = new G4PVPlacement(0,G4ThreeVector(0,0,height/2+ro_height/2),ro_LV,"RO",world_LV,false,0,checkOverlaps_);


  auto boxvisatt = new G4VisAttributes(G4Color(1.,1.,1.));
  boxvisatt->SetVisibility(true);
  block_LV->SetVisAttributes(boxvisatt);

  auto rovisatt = new G4VisAttributes(G4Color(1.,0.,0.));
  rovisatt->SetVisibility(true);
  ro_LV->SetVisAttributes(rovisatt);


  return world_PV;
}

