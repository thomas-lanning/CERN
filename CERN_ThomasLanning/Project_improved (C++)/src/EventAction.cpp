#include "EventAction.h"

#include "g4csv.hh"
#include "G4VProcess.hh"

EventAction::EventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction( const G4Event* )
{
  m_graphEdges.clear();
  m_Photon.clear();
  m_allParticles.clear();
  m_Electron.clear(); //clear all of this at the start!
}

void EventAction::EndOfEventAction( const G4Event* )
{

  // Print particle totals
  std::cout << "Total particles in the event: " << m_allParticles.size() << std::endl;
  // these are zero because I changed my values I just am afraid it might break the code if i delete it
  // and since they were doing no harm I decided to just leave them in 
  std::cout << "Photons produced : " << m_Photon.size() << std::endl;
  std::cout << "Electrons produced: " << m_Electron.size() << std::endl;

//add the row after the event
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->AddNtupleRow(0);


}

void EventAction::RecordParticleData( const G4Step* step )
{
  // Get the track that this step belongs to
  G4Track * track = step->GetTrack();

  // Get the type of particle that made this track
  std::string particle = track->GetParticleDefinition()->GetParticleName();


  // Collect all unique particle IDs
  m_allParticles.insert( track->GetTrackID() );

  // Make a graph edge connecting a new track ID to its parent
  std::pair< int, int > edge = std::make_pair( track->GetParentID(), track->GetTrackID() );
  m_graphEdges.insert( edge );
}
