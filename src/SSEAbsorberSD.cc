
#include "SSEAbsorberSD.h"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SDManager.hh"

SSEAbsorberSD::SSEAbsorberSD(G4String name):
  G4VSensitiveDetector(name)
  ,hitCollection_(NULL)
{
  collectionName.insert("SSEAbsorber");
}


SSEAbsorberSD::~SSEAbsorberSD() { }


void SSEAbsorberSD::Initialize(G4HCofThisEvent *hits)
{

  // create hits collection
  hitCollection_ = new SSEAbsorberHitsCollection(SensitiveDetectorName,collectionName[0]);

  // add this collection to hce
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hits->AddHitsCollection(hcID,hitCollection_);
 
  // create hit
  hitCollection_->insert(new SSEAbsorberHit());
}

G4bool SSEAbsorberSD::ProcessHits(G4Step * step, G4TouchableHistory *history)
{
  return true;
}


void SSEAbsorberSD::EndOfEvent(G4HCofThisEvent *hits)
{

  // print out hits
  (*hitCollection_)[0]->Print();
}
