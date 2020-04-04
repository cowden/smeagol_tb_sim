
#include "SSEDetectorConstruction.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

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

  // set optical properties
  // load the file 
  H5::H5File prop_file("prop_table.h5",H5F_ACC_RDONLY); // define name in macro

  // load the properties table for air
  G4MaterialPropertiesTable * lead_glass_properties = LoadMaterialPropertiesTable(prop_file,"/lead-glass/props");
  G4cout << "Lead-Glass Material Properties Table" << G4endl;
  lead_glass_properties->DumpTable();
  leadGlass->SetMaterialPropertiesTable(lead_glass_properties);  

  // load the properties table for silicon

  // close the file
  prop_file.close();
}



G4VPhysicalVolume* SSEDetectorConstruction::DefineVolumes()
{ 

  // geometry parameters
  G4double world_width = 50*cm;
  G4double world_height = 50*cm;

  G4double width = 50*cm;
  G4double height = 30*cm;

  G4double ro_height = 1*mm;

  // get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("Lead-Glass");
  auto readoutMaterial = G4Material::GetMaterial("G4_Si");

  // world
  auto world_shape = new G4Box("World",world_width/2,world_width/2,world_height/2);
  auto world_LV = new G4LogicalVolume(world_shape,defaultMaterial,"World");
  auto world_PV = new G4PVPlacement(0,G4ThreeVector(),world_LV,"World",0,false,0,checkOverlaps_);


  // block
  auto block_shape = new G4Box("Box",width/2,width/2,height/2);
  auto block_LV = new G4LogicalVolume(block_shape,absorberMaterial,"Box");
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

