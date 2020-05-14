
#include "SSEAbsorberHit.h"

#include "G4VTouchable.hh"
#include "G4Track.hh"

#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<SSEAbsorberHit> * SSEAbsorberHitAllocator=0;

SSEAbsorberHit::SSEAbsorberHit()
 :G4VHit()
 ,e_threshold_(25*MeV)
 ,nTracks_(0U)
 ,nCharged_(0U)
{ }



SSEAbsorberHit::~SSEAbsorberHit()
{ }


SSEAbsorberHit::SSEAbsorberHit(const SSEAbsorberHit &right)
{
  e_threshold_ = right.e_threshold_;

  nTracks_ = right.nTracks_;
  nCharged_ = right.nCharged_;
}

G4bool SSEAbsorberHit::operator==(const SSEAbsorberHit &right) const
{
  return (e_threshold_ == right.e_threshold_) && (nTracks_ == right.nTracks_) && (nCharged_ == right.nCharged_);
}

void SSEAbsorberHit::Draw()
{ }

void SSEAbsorberHit::Print()
{ 

  G4cout << "######################################" << G4endl;
  G4cout << "SSEAbsorberHit" << G4endl;
  G4cout << "nTracks " << nTracks_ << G4endl;
  G4cout << "nCharged " << nCharged_ << G4endl;
  G4cout << "-------------------------------------" << G4endl;

}

void SSEAbsorberHit::AddTrack(const G4Track *aTrack)
{


  auto pdg = aTrack->GetParticleDefinition()->GetPDGEncoding();

  // get the energy
  if ( aTrack->GetTotalEnergy() >= e_threshold_ ) {
    nTracks_++;
    
    if ( aTrack->GetDynamicParticle()->GetCharge() )
      nCharged_++;
  }
   
}
