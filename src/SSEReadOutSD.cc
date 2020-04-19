

#include "SSEReadOutSD.h"

#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4SDManager.hh"


SSEReadOutSD::SSEReadOutSD(G4String name,unsigned nX, unsigned nY):
  G4VSensitiveDetector(name)
  ,nX_(nX)
  ,nY_(nY)
  ,hitCollection_(NULL)
{ 

  // calculate total segments
  nSegments_ = nX_*nY_;

  collectionName.insert("SSEReadOut");
}


SSEReadOutSD::~SSEReadOutSD() { }


void SSEReadOutSD::Initialize(G4HCofThisEvent * hits)
{ 

  // create hits collection
  hitCollection_ = new SSEReadOutHitsCollection(SensitiveDetectorName,collectionName[0]);

  // add this collection in hce
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hits->AddHitsCollection(hcID,hitCollection_);

  // Create hits
  for ( unsigned i=0; i != nSegments_; i++ ) {
    hitCollection_->insert(new SSEReadOutHit());
  }

}


G4bool SSEReadOutSD::ProcessHits(G4Step * step, G4TouchableHistory * history)
{

  if ( step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) {

    auto touchable = (step->GetPreStepPoint()->GetTouchable());

    // get the segment index
    const unsigned xind = touchable->GetReplicaNumber(0);
    const unsigned yind = touchable->GetReplicaNumber(1);
    const unsigned ind = yind*nX_+xind;

    // Add values
    (*hitCollection_)[ind]->Add(touchable); 

    // kill the track
    step->GetTrack()->SetTrackStatus(fStopAndKill);
  } 

  return true;
}

G4bool SSEReadOutSD::ProcessOpticalHits(G4Step * step, G4TouchableHistory * history)
{ 

  return true;
}

void SSEReadOutSD::EndOfEvent(G4HCofThisEvent * hits) 
{

  if ( verboseLevel > 1 ) {
    // 
 
  } 

}

