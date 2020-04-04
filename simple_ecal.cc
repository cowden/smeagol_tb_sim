
/////////////////////////////////////////////
// C S Cowden
//
/////////////////////////////////////////////




#include "G4MTRunManager.hh"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


#include "SSEDetectorConstruction.h"
#include "SSEActionInitialization.h"

void PrintUsage() {
}


int main(int argc, char **argv) {

  // parse command line arguments
  if (argc > 7 ){
    PrintUsage();
    return 1;
  }


  G4String macro;
  G4String session;
  G4int nThreads = 4;
  for ( G4int i=1; i<argc; i=i+2 ) {
    if ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
  }

  // set up the UI and run manager
  G4UIExecutive * ui = nullptr;
  if ( !macro.size() ) {
    ui = new G4UIExecutive(argc,argv,session);
  }

  auto runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(nThreads);

  //  set mandatory initialization classes
  auto physicsList = new FTFP_BERT;
  //auto physicsList = new QBBC;
  physicsList->RegisterPhysics(new G4OpticalPhysics());
  runManager->SetUserInitialization(physicsList);

  auto detConstruction = new SSEDetectorConstruction();
  runManager->SetUserInitialization(detConstruction);

  auto actionInitialization = new SSEActionInitialization(detConstruction);
  runManager->SetUserInitialization(actionInitialization);

  // initialize visualization
  auto visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get UIManager pointer
  auto UImanager = G4UImanager::GetUIpointer();

  // process macro run session
  if ( macro.size() ) {
    // batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute scripts/init_vis.mac");
    ui->SessionStart();
  }



  // clean up 
  delete visManager;
  delete runManager;
  delete ui;

  return 0;
}
