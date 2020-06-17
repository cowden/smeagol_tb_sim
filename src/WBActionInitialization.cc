
#include "WBActionInitialization.h"

#include "SSEPrimaryGeneratorAction.h"
#include "SSEStackingAction.h"
#include "WBSteppingAction.h"
#include "WBEventAction.h"
#include "WBRunAction.h"

#include "CGG4Interface.h"

WBActionInitialization::WBActionInitialization(WBDetectorConstruction *det)
:G4VUserActionInitialization()
,detConstruction_(det)
{ }

WBActionInitialization::~WBActionInitialization()
{ }

void WBActionInitialization::BuildForMaster() const
{ 
  cg::CGG4Interface *cgint = new cg::CGG4Interface;
  SetUserAction(new WBRunAction(cgint));
}


void WBActionInitialization::Build() const
{

  cg::CGG4Interface *cgint = new cg::CGG4Interface;
  
  SetUserAction(new SSEPrimaryGeneratorAction);
  SetUserAction(new SSEStackingAction);
  SetUserAction(new WBSteppingAction(cgint));

  SetUserAction(new WBEventAction(cgint));
  SetUserAction(new WBRunAction(cgint));
}
