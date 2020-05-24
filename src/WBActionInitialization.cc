
#include "WBActionInitialization.h"

#include "SSEPrimaryGeneratorAction.h"
#include "SSEStackingAction.h"

WBActionInitialization::WBActionInitialization(WBDetectorConstruction *det)
:G4VUserActionInitialization()
,detConstruction_(det)
{ }

WBActionInitialization::~WBActionInitialization()
{ }

void WBActionInitialization::BuildForMaster() const
{ }


void WBActionInitialization::Build() const
{
  SetUserAction(new SSEPrimaryGeneratorAction);
  SetUserAction(new SSEStackingAction);
}
