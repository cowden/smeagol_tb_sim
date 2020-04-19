

#include "SSEEventAction.h"

#include "G4Event.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"

#include "SSEReadOutHit.h"

SSEEventAction::SSEEventAction()
{ }

SSEEventAction::~SSEEventAction()
{ }

void SSEEventAction::BeginOfEventAction(const G4Event * event)
{ }


void SSEEventAction::EndOfEventAction(const G4Event * event)
{

  G4cout << "SSEEventAction::EndOfEventAction" << G4endl;

  // get the hits collections
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID("SSEReadOut");
  auto roHits = static_cast<SSEReadOutHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  // extract the values
  unsigned total = 0U;
  size_t nSegments = roHits->GetSize();
  for ( unsigned i =0 ; i != nSegments; i++ ) {
    total += (*roHits)[i]->GetHitCount();     
  } 

  G4cout << "SSE Counted " << total << " photons" << G4endl;

  // check for the visualization manager
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if ( pVVisManager ) {
    G4cout << "  Drawing SD hits" << G4endl;
    // update visualization
    for ( unsigned i=0; i != nSegments; i++ )
      (*roHits)[i]->Draw();
  }
  


}
