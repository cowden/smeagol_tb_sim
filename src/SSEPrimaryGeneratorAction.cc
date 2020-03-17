

#include "SSEPrimaryGeneratorAction.h"

#include "G4LogicalVolumeStore.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


SSEPrimaryGeneratorAction::SSEPrimaryGeneratorAction():
  G4VUserPrimaryGeneratorAction(),
  particleGun_(nullptr)
{

  G4int nParticles = 1;
  particleGun_ = new G4ParticleGun(nParticles);

  auto particleDef = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  particleGun_->SetParticleDefinition(particleDef);
  particleGun_->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun_->SetParticleEnergy(50.*MeV);  

}


SSEPrimaryGeneratorAction::~SSEPrimaryGeneratorAction()
{
  delete particleGun_;
}

void SSEPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

  G4double whl = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  whl = dynamic_cast<G4Box*>(worldLV->GetSolid())->GetZHalfLength();

  //
  particleGun_->SetParticlePosition(G4ThreeVector(0.,0.,-whl));
  particleGun_->GeneratePrimaryVertex(event);

}

void SSEPrimaryGeneratorAction::SetRandomFlag(G4bool value)
{
}
