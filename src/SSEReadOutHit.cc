
#include "SSEReadOutHit.h"

#include "G4VTouchable.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

G4ThreadLocal G4Allocator<SSEReadOutHit>* SSEReadOutHitAllocator=0;

SSEReadOutHit::SSEReadOutHit()
  :nPhotons_(0U)
  ,touchable_(NULL)
  ,physVol_(NULL)
{ }

SSEReadOutHit::SSEReadOutHit(const SSEReadOutHit &right): G4VHit()
  ,nPhotons_(right.nPhotons_)
  ,touchable_(right.touchable_)
  ,physVol_(right.physVol_)
{ }

SSEReadOutHit::~SSEReadOutHit()
{ }


const SSEReadOutHit& SSEReadOutHit::operator=(const SSEReadOutHit & right) 
{
  return *this; 
}

G4bool SSEReadOutHit::operator==(const SSEReadOutHit &right) const 
{ 
  return 1;
}

void SSEReadOutHit::Draw()
{ 

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if ( pVVisManager && physVol_ ) {
    
    //unsigned i = touchable_->GetReplicaNumber(0);
    //unsigned j = touchable_->GetReplicaNumber(1);

    //G4cout << "Drawing hit " << i << " " << j << nPhotons_ << G4endl;

    //G4VisAttributes attribs(G4Color(i/10.,j/10.,0.));
    G4VisAttributes attribs (G4Color(0.5,0.5,1.));

    //G4LogicalVolume * logVol = touchable_->GetVolume()->GetLogicalVolume();
    pVVisManager->Draw(*physVol_,attribs);
  }

}


void SSEReadOutHit::Print()
{ }

void SSEReadOutHit::Add(const G4VTouchable * touchable)
{

  // check if touchable is null or already has it set
  if ( !touchable_ && (touchable != touchable_) ) {
    touchable_ = touchable;
    physVol_ = touchable_->GetVolume();
  }

  // add to the count of photons
  nPhotons_++;

}
