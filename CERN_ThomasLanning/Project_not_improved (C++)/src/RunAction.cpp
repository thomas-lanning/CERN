#include "RunAction.h"

#include "g4csv.hh"

RunAction::RunAction() : G4UserRunAction()
{
  // Set number of layers
  //using 5 here because it was easy during troubleshooting times
  // I delete these columns in the notebook because theyre empty...
  G4int const layerNumber = 5;

  // Create analysis manager
  auto analysis1Manager = G4AnalysisManager::Instance();

  // Add an ntuple for all my variables (ntuple id 0)
  analysis1Manager->CreateNtuple("Energy", "Deposited energy" );
  analysis1Manager->CreateNtupleDColumn( "Generated Energy" );
  analysis1Manager->CreateNtupleDColumn( "Photon/Elextron" );
  analysis1Manager->CreateNtupleDColumn( "detector ID" );
  analysis1Manager->CreateNtupleDColumn( "particleMomentum" );
  for ( unsigned int layerIndex = 1; layerIndex <= layerNumber; ++layerIndex )
  {
    std::string columnName = "ElectronLayerIndex1" + std::to_string( layerIndex );
    analysis1Manager->CreateNtupleDColumn( columnName );
  }
  analysis1Manager->FinishNtuple();
}

RunAction::~RunAction()
{
  // Delete analysis manager
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction( const G4Run* )
{
  // Get analysis manager
  auto analysis1Manager = G4AnalysisManager::Instance();

  // Open an output file
  analysis1Manager->OpenFile( "output.csv" );
}

void RunAction::EndOfRunAction( const G4Run* )
{
  // Get analysis manager
  auto analysis1Manager = G4AnalysisManager::Instance();

  // Save output data
  analysis1Manager->Write();
  analysis1Manager->CloseFile();

}
