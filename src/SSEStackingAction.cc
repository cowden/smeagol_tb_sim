
#include "SSEStackingAction.h"

#include "G4Track.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "SSEAbsorberHit.h"


SSEStackingAction::SSEStackingAction()
:G4UserStackingAction()
{ }

SSEStackingAction::~SSEStackingAction()
{ }


G4ClassificationOfNewTrack SSEStackingAction::ClassifyNewTrack(const G4Track * track)
{

  // check if the track is in the absorber, break out if not
  auto pv = track->GetVolume();

  if ( pv) {
    const G4String & logName = pv->GetLogicalVolume()->GetName();
    if ( logName == "Box" ) {

      // get the run manager and the current event
      G4RunManager* runMan = G4RunManager::GetRunManager();
      const G4Event* event = runMan->GetCurrentEvent();
  
      G4SDManager* SDMan = G4SDManager::GetSDMpointer();
      G4int colID = SDMan->GetCollectionID("SSEAbsorber");
  
      // get the hit collection  for this event
      G4HCofThisEvent *hce = event->GetHCofThisEvent();
  
      // get the hit collection for the absorber
      auto abshit = (SSEAbsorberHitsCollection*)hce->GetHC(colID);
  
      // increment count of tracks
      (*abshit)[0]->AddTrack(track);

    }
  }

  // return everyting to the urgent stack
  return fUrgent;
}

void SSEStackingAction::NewStage()
{ }

void SSEStackingAction::PrepareNewEvent()
{ }

