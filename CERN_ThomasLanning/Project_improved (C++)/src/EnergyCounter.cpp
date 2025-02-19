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
  //I dont use these anymore but keep them so I dont have to change the header files lol
  m_totalElectronEnergy = 0.0;
  m_totalPhotonEnergy = 0.0;
  m_particle_id = 0.0;
  /////////////////////
  // this one is new!
  /////////////////////
  m_charge = 0.0;
}

// Analyse anything that hits the detector
G4bool EnergyCounter::ProcessHits( G4Step* step, G4TouchableHistory* )
{
  // Get the energy deposited by this hit
  G4double edep = step->GetTotalEnergyDeposit();
  m_totalEnergy += edep;
  G4double charge = step->GetTrack()->GetParticleDefinition()->GetPDGCharge();
  m_charge += charge; // add the charge to the total charge


  return true;
}

// At the end of an event, store the energy collected in this detector
void EnergyCounter::EndOfEvent( G4HCofThisEvent* )
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->FillNtupleDColumn( 0, m_ID+1, m_totalEnergy);
//If the box detecotr (m_ID =4), then add charge deposit
  if (m_ID == 4)
  {
    analysisManager->FillNtupleDColumn(0, 1, m_charge); //last column is charge
  }

}
