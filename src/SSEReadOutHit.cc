
#include "SSEReadOutHit.h"

#include "G4VTouchable.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4Box.hh"

#include "G4SystemOfUnits.hh"


G4ThreadLocal G4Allocator<SSEReadOutHit>* SSEReadOutHitAllocator=0;

SSEReadOutHit::SSEReadOutHit()
  :nPhotons_(0U)
  ,touchable_(NULL)
  ,physVol_(NULL)
  ,wx_(1.5*cm)
  ,wy_(1.5*cm)
  ,wz_(1.5*cm)
  ,col_(UINT_MAX)
  ,row_(UINT_MAX)
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
  nPhotons_ = right.nPhotons_; 

  touchable_ = right.touchable_;
  physVol_ = right.physVol_;
  logVol_ = right.logVol_;

  wx_ = right.wx_;
  wy_ = right.wy_;
  wz_ = right.wz_;

  pos_ = right.pos_;
  rot_ = right.rot_;

  col_ = right.col_;
  row_ = right.row_;

  return *this; 
}

G4bool SSEReadOutHit::operator==(const SSEReadOutHit &right) const 
{
  return (col_ == right.col_ && row_ == right.row_);
}

void SSEReadOutHit::Draw()
{ 

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if ( pVVisManager ) {

    G4double intensity = (G4double)nPhotons_/5.;
    if ( intensity > 1. )
      intensity = 1.;

    G4Transform3D trans(rot_.inverse(),pos_);
    G4VisAttributes attribs;
    G4Color color(intensity,0.,0.);
    attribs.SetColour(color);
    attribs.SetForceSolid(true);

    //G4cout << "  " << row_ << " " << col_ << " " << nPhotons_ << " " << intensity << G4endl;

    G4Box box("dummy",wx_,wy_,wz_);
    pVVisManager->Draw(box,attribs,trans);

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
