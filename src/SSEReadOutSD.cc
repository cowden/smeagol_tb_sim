

#include "SSEReadOutSD.h"

#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"


SSEReadOutSD::SSEReadOutSD(G4String name):
  G4VSensitiveDetector(name)
{ }


SSEReadOutSD::~SSEReadOutSD() { }


void SSEReadOutSD::InitSegments(const G4VPhysicalVolume * phys_vol, unsigned nSegments)
{

  // find the base location

  // determine step size

  // create locations

  // construct maps/extents 

}

void SSEReadOutSD::Initialize(G4HCofThisEvent * hits)
{ }


G4bool SSEReadOutSD::ProcessHits(G4Step * step, G4TouchableHistory * history)
{

  G4cout << "Processing hits from Readout" << G4endl;
  if ( step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() ) {

    G4cout << "  Optical photon hit from " << history << " " 
      << step->GetPreStepPoint()->GetTouchable() 
      << " " << step->GetPreStepPoint()->GetPhysicalVolume()<< G4endl;

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
{ }

