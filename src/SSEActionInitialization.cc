
#include "SSEActionInitialization.h"

#include "SSEPrimaryGeneratorAction.h"
#include "SSERunAction.h"
#include "SSEEventAction.h"

SSEActionInitialization::SSEActionInitialization(SSEDetectorConstruction* det):
  G4VUserActionInitialization()
  ,detConstruction_(det)
{ }

SSEActionInitialization::~SSEActionInitialization()
{ }

void SSEActionInitialization::BuildForMaster() const
{
}

void SSEActionInitialization::Build() const
{
  SetUserAction(new SSEPrimaryGeneratorAction);
  SetUserAction(new SSERunAction);
  SetUserAction(new SSEEventAction);
}

