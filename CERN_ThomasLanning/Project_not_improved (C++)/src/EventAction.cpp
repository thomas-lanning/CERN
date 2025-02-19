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
  // Print particle totals to see that my simulation is working in the terminal screen
  std::cout << "Total particles in the event: " << m_allParticles.size() << std::endl;
  std::cout << "Photons produced : " << m_Photon.size() << std::endl;
  std::cout << "Electrons produced: " << m_Electron.size() << std::endl;

}

void EventAction::RecordParticleData( const G4Step* step )
{
  // Get the track that this step belongs to
  G4Track * track = step->GetTrack();

  // Get the type of particle that made this track
  std::string particle = track->GetParticleDefinition()->GetParticleName();

  // Find out how the track was created
  // have to check if the pointer is valid: it doesn't exist for intermediate steps
  if ( track->GetCreatorProcess() )
  {
    std::string creator = track->GetCreatorProcess()->GetProcessName();

    //do the same but for electrons
    if (particle == "e-")
    {
      m_Electron.insert( track->GetTrackID());
    }
    //if ( creator == "conv" && particle == "e+" )
    if (particle == "gamma")
    {
      // Use a set so that track IDs are only stored once
      m_Photon.insert( track->GetTrackID() );
    }
  }

  // Collect all unique particle IDs
  m_allParticles.insert( track->GetTrackID() );

  // Make a graph edge connecting a new track ID to its parent
  std::pair< int, int > edge = std::make_pair( track->GetParentID(), track->GetTrackID() );
  m_graphEdges.insert( edge );
}
