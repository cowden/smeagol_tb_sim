
#include "SSEDetectorConstruction.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4PVReplica.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "SSEReadOutSD.h"
#include "SSEAbsorberSD.h"


SSEDetectorConstruction::SSEDetectorConstruction():
  G4VUserDetectorConstruction(),
  checkOverlaps_(true),
  world_width_(150*cm),
  world_height_(150*cm),
  width_( 150*cm),
  height_(30*cm),
  ro_height_(1*mm),
  nXSegments_(75U),
  nYSegments_(75U)
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

  // set optical properties
  // load the file 
  H5::H5File prop_file("prop_table.h5",H5F_ACC_RDONLY); // define name in macro

  // load the properties table for air
  G4MaterialPropertiesTable * lead_glass_properties = LoadMaterialPropertiesTable(prop_file,"/lead-glass/props");
  G4cout << "Lead-Glass Material Properties Table" << G4endl;
  lead_glass_properties->DumpTable();
  leadGlass->SetMaterialPropertiesTable(lead_glass_properties);  

  // load the properties table for silicon
  G4Material* si = G4Material::GetMaterial("G4_Si");
  si->SetMaterialPropertiesTable(lead_glass_properties); 


  // close the file
  prop_file.close();
}



G4VPhysicalVolume* SSEDetectorConstruction::DefineVolumes()
{ 


  // get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("Lead-Glass");
  auto readoutMaterial = G4Material::GetMaterial("G4_Si");

  // world
  auto world_shape = new G4Box("World",world_width_/2.,world_width_/2.,world_height_/2.);
  auto world_LV = new G4LogicalVolume(world_shape,defaultMaterial,"World");
  auto world_PV = new G4PVPlacement(0,G4ThreeVector(),world_LV,"World",0,false,0,checkOverlaps_);


  // block
  auto block_shape = new G4Box("Box",width_/2.,width_/2.,height_/2.);
  absorberLog_ = new G4LogicalVolume(block_shape,absorberMaterial,"Box");
  absorberPV_ = new G4PVPlacement(0,G4ThreeVector(),absorberLog_,"Box",world_LV,false,0,checkOverlaps_);

  // readout
  auto ro_shape = new G4Box("ROUnit",width_/2.,width_/2.,ro_height_/2.);
  readoutLog_ = new G4LogicalVolume(ro_shape,readoutMaterial,"RO");
  readoutPV_ = new G4PVPlacement(0,G4ThreeVector(0,0,height_/2.+ro_height_/2.),readoutLog_,"RO",world_LV,false,0,checkOverlaps_);

  auto rep_shape = new G4Box("ROStrip",width_/2.,width_/2./nYSegments_,ro_height_/2.);
  auto rep_log = new G4LogicalVolume(rep_shape,readoutMaterial,"rep");
  auto temp = new G4PVReplica("array",rep_log,readoutLog_,kYAxis,nYSegments_,width_/nYSegments_);

  auto ro_segment_shape = new G4Box("ROSeg",width_/2./nXSegments_,width_/2./nYSegments_,ro_height_/2.);
  roSegmentLog_ = new G4LogicalVolume(ro_segment_shape,readoutMaterial,"ROSeg");
  roSegments_ = new G4PVReplica("ROSeg",roSegmentLog_,rep_log,kXAxis,nXSegments_,width_/nYSegments_);


  auto boxvisatt = new G4VisAttributes(G4Color(1.,1.,1.));
  boxvisatt->SetVisibility(true);
  absorberLog_->SetVisAttributes(boxvisatt);

  auto rovisatt = new G4VisAttributes(G4Color(0.,0.,0.));
  rovisatt->SetVisibility(true);
  roSegmentLog_->SetVisAttributes(rovisatt);


  //
  // load the optical surface properties
  // temporarily put in some manual values
  G4OpticalSurface* absWrap = new G4OpticalSurface("AbsorberWrapper");

  new G4LogicalBorderSurface("AbsorberWrap", absorberPV_, readoutPV_, absWrap);

  absWrap->SetType(dielectric_dielectric);
  absWrap->SetFinish(polished);
  absWrap->SetModel(glisur);

  G4double pp[] = {2.0*eV, 3.5*eV};
  const G4int num = sizeof(pp)/sizeof(G4double);
  G4double reflectivity[] = {1.,1.};
  G4double efficiency[] = {1., 1.};
  
  G4MaterialPropertiesTable* absWrapProps = new G4MaterialPropertiesTable();
  absWrapProps->AddProperty("REFLECTIVITY",pp,reflectivity,num);
  absWrapProps->AddProperty("EFFICIENCY",pp,efficiency,num);
  absWrap->SetMaterialPropertiesTable(absWrapProps);

  // Print the Materials
  DumpDetectorMaterialProperties(); 

  return world_PV;
}

G4MaterialPropertiesTable * SSEDetectorConstruction::LoadMaterialPropertiesTable(H5::H5File & file,const char * name)
{

  H5::DataSet dataset = file.openDataSet(name);

  // extract the data
  const unsigned ndims = dataset.getSpace().getSimpleExtentNdims(); 
  std::vector<hsize_t> dims(ndims);
  dataset.getSpace().getSimpleExtentDims(&dims[0],NULL);
  H5::DataSpace memspace(2,&dims[0]); 
  std::vector<float> raw_props(dataset.getSpace().getSelectNpoints());
  dataset.read(&raw_props[0], H5::PredType::NATIVE_FLOAT, memspace, dataset.getSpace());

  // make copies of copies of the columns and convert the units
  const unsigned n = dims[0];
  const unsigned w = dims[1];
  std::vector<G4double> energy(n);
  std::vector<G4double> rindex(n);
  std::vector<G4double> abslength(n);

  for ( unsigned i=0; i != n; i++ ){
    energy[i] = raw_props[i*w]*eV;
    rindex[i] = raw_props[i*w+1];
    abslength[i] = raw_props[i*w+2]*m;
  }

  // create the material properties
  G4MaterialPropertiesTable * prop_table = new G4MaterialPropertiesTable();
  prop_table->AddProperty("RINDEX", energy.data(), rindex.data(), n);
  prop_table->AddProperty("ABSLENGTH", energy.data(), abslength.data(), n);
 

  return prop_table;
}

void SSEDetectorConstruction::DumpDetectorMaterialProperties()
{

  // 
  // print material properties
  
  G4cout << G4Material::GetMaterial("Galactic") << G4endl;
  G4cout << G4Material::GetMaterial("Lead-Glass") << G4endl;
  G4cout << G4Material::GetMaterial("G4_Si") << G4endl;

}

void SSEDetectorConstruction::ConstructSDandField() 
{

  if ( !absorberPV_ ) return;

  // readout SD
  G4cout << "Constructing SSEReadOutSD" << G4endl;
  SSEReadOutSD* readoutSD = new SSEReadOutSD("SSEReadOutSD",nXSegments_,nYSegments_);
  G4SDManager::GetSDMpointer()->AddNewDetector(readoutSD);

  SetSensitiveDetector(roSegmentLog_,readoutSD);

  // absorber SD
  G4cout << "Constructing SSEAbsorberSD" << G4endl;
  SSEAbsorberSD* absSD = new SSEAbsorberSD("SSEABsorberSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(absSD);

  SetSensitiveDetector(absorberLog_,absSD);
  

}

