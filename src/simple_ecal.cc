
/////////////////////////////////////////////
// C S Cowden
//
/////////////////////////////////////////////




#include "G4MTRunManager.hh"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


#include "SSEDetectorConstruction.h"
#include "SSEActionInitialization.h"


int main(int argc, char **argv) {

  // parse command line arguments


  // set up the UI and run manager
  G4UIExecutive * ui = nullptr;
  if ( !macro.size() ) {
    ui = new G4UIExecutive(argc,argv,session);
  }

  auto runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(nThreads);

  //  set mandatory initialization classes

  // initialize visualization

  // Get UIManager pointer

  // process macro run session

  return 0;
}
