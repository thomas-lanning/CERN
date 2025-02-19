#include "RunAction.h"

#include "g4csv.hh"

RunAction::RunAction() : G4UserRunAction()
{
  // Set number of layers
  // THIS CHANGED!
  ////////////////////////////////
  G4int const layerNumber = 3;
  ////////////////////////////////
  // Create analysis manager
  auto analysis1Manager = G4AnalysisManager::Instance();

  // Add an ntuple for energy deposits (ntuple id 0)
  analysis1Manager->CreateNtuple("Energy", "Deposited energy" );
  analysis1Manager->CreateNtupleDColumn( "Generated Energy" );
  analysis1Manager->CreateNtupleDColumn( "charge" );
  for ( unsigned int layerIndex = 1; layerIndex <= layerNumber; ++layerIndex )
  {
    std::string columnName = "ElectronLayerIndex1" + std::to_string( layerIndex );
    analysis1Manager->CreateNtupleDColumn( columnName );
  }
  analysis1Manager->CreateNtupleDColumn( "Detector2" );

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
//  auto analysis2Manager = G4AnalysisManager::Instance();

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
