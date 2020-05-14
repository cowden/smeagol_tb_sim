
#include "SSEActionInitialization.h"

#include "SSEPrimaryGeneratorAction.h"
#include "SSERunAction.h"
#include "SSEEventAction.h"
#include "SSEStackingAction.h"
#include "SSESteppingAction.h"

SSEActionInitialization::SSEActionInitialization(SSEDetectorConstruction* det):
  G4VUserActionInitialization()
  ,detConstruction_(det)
{ }

SSEActionInitialization::~SSEActionInitialization()
{ }

void SSEActionInitialization::BuildForMaster() const
{
  SetUserAction(new SSERunAction);
}

void SSEActionInitialization::Build() const
{
  SetUserAction(new SSEPrimaryGeneratorAction);
  SetUserAction(new SSERunAction);
  SetUserAction(new SSEEventAction);
  SetUserAction(new SSEStackingAction);
  SetUserAction(new SSESteppingAction);
}

