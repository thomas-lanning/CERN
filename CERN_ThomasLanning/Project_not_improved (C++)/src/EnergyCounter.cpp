#include "EnergyCounter.h"

#include "g4csv.hh"

EnergyCounter::EnergyCounter( const G4String& name, const G4int id )
  : G4VSensitiveDetector( name ) // Run the constructor of the parent class
{
  // Set which ntuple column to use (0th column true energy, first column will be particle id)
  m_ID = id ;
}

EnergyCounter::~EnergyCounter()
{
}

// At the start of the event, zero the energy counter
void EnergyCounter::Initialize( G4HCofThisEvent* )
{
  m_totalEnergy = 0.0;
  //I defined this varibale because I need to record the elctron energy
  m_totalElectronEnergy = 0.0;
  m_totalPhotonEnergy = 0.0;
  m_particle_id = 0.0;
}

// Analyse anything that hits the detector
G4bool EnergyCounter::ProcessHits( G4Step* step, G4TouchableHistory* )
{
  // Get the energy deposited by this hit
  G4double edep = step->GetTotalEnergyDeposit();
  m_totalEnergy += edep;

  G4Track * track = step->GetTrack();
  std::string particle = track->GetParticleDefinition()->GetParticleName();
  G4ThreeVector momentum = track->GetMomentum();
  // Get the analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

///////////////////
// Below is the code I use in the first bit of the jupyter notebook to measure what happens in a single
// event. I commented it all out so you can still see what is supposed to happen:
// simply umcomment and rerun it to get this bit
/////////////////// 

/*
//if its a electron add that energy to the list
  if (particle == "e-")
  {
    m_totalElectronEnergy += edep;
    m_particle_id = 1; //if electron return 1
    analysisManager->FillNtupleDColumn( 0, m_ID+4, edep);
    analysisManager->FillNtupleDColumn( 0, 3, momentum.mag());
    analysisManager->FillNtupleDColumn( 0, 2, m_ID); //return the id number in 2nd column
    analysisManager->FillNtupleDColumn( 0, 1, m_particle_id);
    analysisManager->AddNtupleRow(0);
  }
  if (particle == "gamma")
  {
     m_totalPhotonEnergy += edep;
     m_particle_id = 0;
     analysisManager->FillNtupleDColumn( 0, m_ID+4, edep);
     analysisManager->FillNtupleDColumn( 0, 3, momentum.mag());
     analysisManager->FillNtupleDColumn( 0, 2, m_ID); //return the id number in 2nd column
     analysisManager->FillNtupleDColumn( 0, 1, m_particle_id);
     analysisManager->AddNtupleRow(0);
  }

*/

  return true;
}

// At the end of an event, store the energy collected in this detector
void EnergyCounter::EndOfEvent( G4HCofThisEvent* )
{
  auto analysisManager = G4AnalysisManager::Instance();

//get the right columns! we ignore the first few since those were meant for the above commented out example
  analysisManager->FillNtupleDColumn( 0, m_ID+4, m_totalEnergy);
// add the final data to the ntuple
  analysisManager->AddNtupleRow(0);

}
