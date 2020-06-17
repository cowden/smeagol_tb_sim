
#include "WBRunAction.h"
#include "SSEAnalysis.h"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"

#include "CGG4Interface.h"


WBRunAction::WBRunAction(cg::CGG4Interface *cgint)
: G4UserRunAction()
,num_(0U)
,cg_(cgint)
{

  // create analysis manager
  auto am = G4AnalysisManager::Instance();
  G4cout << "Instantiating AnalysisManager " << am->GetType() << G4endl;

  // create directories
  am->SetVerboseLevel(1);
  am->SetNtupleMerging(true);

  // create ntuple
  am->CreateNtuple("shower","Shower Graph");
  am->CreateNtupleIColumn("tid"); 
  am->CreateNtupleIColumn("pid"); // parent track id
  am->CreateNtupleIColumn("proc");  // creating physics process
  am->CreateNtupleDColumn("e");  // energy
  am->CreateNtupleIColumn("pdgid");  // particle id
  am->CreateNtupleDColumn("x"); // x creation position
  am->CreateNtupleDColumn("y"); // y creation position
  am->CreateNtupleDColumn("z"); // z creation position
  
  am->FinishNtuple();
}




WBRunAction::~WBRunAction()
{
  delete G4AnalysisManager::Instance();
}



void WBRunAction::BeginOfRunAction(const G4Run *run)
{
  // get the analysis manager instance
  auto am = G4AnalysisManager::Instance();
  
  // open a new output file
  G4String fileName = "wb_data";
  am->OpenFile(fileName);
}



void WBRunAction::EndOfRunAction(const G4Run* run)
{
  // get a pointer to the analysis manager
  auto am = G4AnalysisManager::Instance();

  // print some summary stuff

  // save the data
  // write & close the file
  am->Write();
  am->CloseFile();

  // push to master (if this is a worker thread)
  if ( G4Threading::IsWorkerThread() ) {
    cg_->merge();
  } else {
    //print the static data
    //print_data();
  }
}



