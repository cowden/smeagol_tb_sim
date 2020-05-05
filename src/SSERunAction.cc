

#include "SSERunAction.h"
#include "SSEAnalysis.h"

#include "G4Run.hh"
#include "G4RunManager.hh"

SSERunAction::SSERunAction()
  :  G4UserRunAction()
{

  // create analysis manager 
  auto analysis_ = G4AnalysisManager::Instance();
  G4cout << "Instantiating AnalysisManager " << analysis_->GetType() << G4endl;

  // create directories
  analysis_->SetVerboseLevel(1);
  analysis_->SetNtupleMerging(true);

  // create ntuple
  analysis_->CreateNtuple("shower","Shower Graph");
  analysis_->CreateNtupleIColumn("tid"); // track id
  analysis_->CreateNtupleIColumn("pid"); // parent track id
  analysis_->CreateNtupleIColumn("proc");  // creating physics process
  analysis_->CreateNtupleDColumn("e");  // energy
  analysis_->CreateNtupleIColumn("pdgid");  // particle id
  analysis_->CreateNtupleDColumn("x"); // x creation position
  analysis_->CreateNtupleDColumn("y"); // y creation position
  analysis_->CreateNtupleDColumn("z"); // z creation position
  
  analysis_->FinishNtuple();

  analysis_->CreateNtuple("ro","ReadOut Segments");
  analysis_->CreateNtupleIColumn("id"); // the id of the readout segment
  analysis_->CreateNtupleDColumn("e"); // the total energy in the cell
  
  analysis_->FinishNtuple();

}

SSERunAction::~SSERunAction()
{
  delete G4AnalysisManager::Instance();
}


void SSERunAction::BeginOfRunAction(const G4Run *run)
{

  // get the AnalysisManager instance
  auto am_ = G4AnalysisManager::Instance();

  // open a new output file
  G4String fileName = "sse_data";
  am_->OpenFile(fileName); 

}

void SSERunAction::EndOfRunAction(const G4Run* run)
{

  // get a pointer to the analysis manager
  auto am_ = G4AnalysisManager::Instance();

  // print some summary stuff 

  // save the data
  // write & close the file.
  am_->Write();
  am_->CloseFile();
 

}
