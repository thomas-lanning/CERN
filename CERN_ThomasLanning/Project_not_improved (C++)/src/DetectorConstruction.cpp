#include "DetectorConstruction.h"
#include "EnergyCounter.h"
#include "G4Sphere.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4SubtractionSolid.hh" //for box detector
#include "G4RotationMatrix.hh" //to rotate my sphere
#include "G4VisAttributes.hh" //for color

////////////////////////////////
// If you look at the jupyter notebook, you can see pictures of what
// the final build looks like, this might help since its a pretty
// long file of code otherwise.
// to summarize, theres 4 building and a shield detector and a 
// box detector.
// The buildings are lead because they are supposed to be skyscrapers...
////////////////////////////////


// Set number of detector layers
// I copied this code from a checkpoint example: i keep it here for my 
// Later improved version I will add more layers
G4int const nLayers = 1;

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::m_magneticFieldMessenger = 0;

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

// Here we define the actual experiment that we want to perform
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Materials
  // http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
  G4NistManager* nistManager = G4NistManager::Instance();
  G4Material* vacuum = nistManager->FindOrBuildMaterial( "G4_Galactic" );
  G4Material* lead = nistManager->FindOrBuildMaterial( "G4_Pb" );
  G4Material* liquidArgon = nistManager->FindOrBuildMaterial( "G4_lAr" );

  // Sizes of the principal geometrical components (solids)
  // I am making a few buildings
  G4double buildingThickness = 50*cm;
  G4double worldLength = 500.0*cm;

  // Definitions of Solids, Logical Volumes, Physical Volumes

  // WORLD: Solid (cube)
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent( worldLength );
  G4Box* worldS = new G4Box(
                 "World",         // its name
                 worldLength,
                 worldLength,
                 worldLength );   // its size (in half-lengths)

  // WORLD: Logical volume (how to treat it)
  G4LogicalVolume* worldLV = new G4LogicalVolume(
                 worldS,          // its solid
                 vacuum,          // its material
                 "World" );       // its name

  // WORLD: Physical volume (where is it)
  // Must place the World Physical volume unrotated at (0,0,0).
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, 0.0, 0.0), // in the centre
                 worldLV,         // its logical volume
                 "World",         // its name
                 0,               // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps


  // NOW I will define a bunch of buildings as a kind of city which gets bombarded by the sun/particle gun
  // Building:  properties
  std::string building1Name = "Building1";
  G4double building1Height = 80*cm;
  G4ThreeVector building1Position( -70*cm, -70*cm, 450 *cm -building1Height/2);
  // ABSORBER: Solid (tube)
  G4Box* building1S = new G4Box(
                  building1Name,      // its name
                  buildingThickness,   // same aa before with the world,
                  buildingThickness,   // define the x,y,z'a
                  building1Height);

  // ABSORBER: Logical volume (how to treat it)
  G4LogicalVolume* building1LV = new G4LogicalVolume(
                  building1S,         // its solid
                  lead,              // its material DO WOOD!
                  building1Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use apparently

  // ABSORBER: Physical volume (where is it)
  G4VPhysicalVolume* building1PV = new G4PVPlacement(
                  0,                 // no rotation
                  building1Position,  // where is it
                  building1LV,        // its logical volume
                  building1Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps


  // Building2:  properties
  std::string building2Name = "Building2";
  G4double building2Height = 95*cm;
  G4ThreeVector building2Position( 70*cm, 70*cm, 450 *cm-building2Height/2);

  // 
  G4Box* building2S = new G4Box(
                  building2Name,      // its name
                  buildingThickness,   // same as before,
                  buildingThickness,   // define the x,y,z'a
                  building2Height);

  // ABSORBER: Logical volume (how to treat it)
  G4LogicalVolume* building2LV = new G4LogicalVolume(
                  building2S,         // its solid
                  lead,              // its material
                  building2Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use apparently

  // ABSORBER: Physical volume (where is it)
  G4VPhysicalVolume* building2PV = new G4PVPlacement(
                  0,                 // no rotation
                  building2Position,  // where is it
                  building2LV,        // its logical volume
                  building2Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps

  // Building3:  properties
  std::string building3Name = "Building3";
  G4double building3Height = 125*cm;
  G4ThreeVector building3Position( -70*cm, 70*cm, 450 *cm-building3Height/2);

  //
  G4Box* building3S = new G4Box(
                  building3Name,      // its name
                  buildingThickness,   // same aa before with the world,
                  buildingThickness,   // define the x,y,z'a
                  building3Height);

  // ABSORBER: Logical volume (how to treat it)
  G4LogicalVolume* building3LV = new G4LogicalVolume(
                  building3S,         // its solid
                  lead,              // its material DO WOOD!
                  building3Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use apparently

  // ABSORBER: Physical volume (where is it)
  G4VPhysicalVolume* building3PV = new G4PVPlacement(
                  0,                 // no rotation
                  building3Position,  // where is it
                  building3LV,        // its logical volume
                  building3Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps
  // Building4:  properties
  std::string building4Name = "Building4";
  G4double building4Height = 150*cm;
  G4ThreeVector building4Position( 70*cm, -70*cm, 450*cm -building4Height/2);

  // 
  G4Box* building4S = new G4Box(
                  building4Name,      // its name
                  buildingThickness,   // same aa before with the world,
                  buildingThickness,   // define the x,y,z'a
                  building4Height);

  // ABSORBER: Logical volume (how to treat it)
  G4LogicalVolume* building4LV = new G4LogicalVolume(
                  building4S,         // its solid
                  lead,              // its material DO WOOD!
                  building4Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use apparently

  // ABSORBER: Physical volume (where is it)
  G4VPhysicalVolume* building4PV = new G4PVPlacement(
                  0,                 // no rotation
                  building4Position,  // where is it
                  building4LV,        // its logical volume
                  building4Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps



  // ABSORBER: Quit if there's an overlap
  if ( building1PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;
  if ( building2PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;
  if ( building3PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;
  if ( building4PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;

//start making my detectors
  std::string detector1Name = "Detector1";
  G4ThreeVector detector1Position( 0, 0, 400*cm );
  G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
  rotationMatrix->rotateX(90.*deg);
  // DETECTOR: Solid (semi-sphere)
  G4Sphere* detector1S = new G4Sphere(
                  detector1Name,      // its name
                  480.0*cm, //Rmin
                  500.0*cm,  //Rmax
                  0*deg, //SPhi
                  180*deg, //DPhi
                  0*deg, //STheta
                  360*deg);       //DTheta

  // DETECTOR: Logical volume (how to treat it)
  G4LogicalVolume* detector1LV = new G4LogicalVolume(
                  detector1S,         // its solid
                  liquidArgon,       // its material
                  detector1Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use

  // DETECTOR: Physical volume (where is it)
  G4VPhysicalVolume* detector1PV = new G4PVPlacement(
                  rotationMatrix,                 // 90degree x-rotation
                  detector1Position,  // where is it
                  detector1LV,        // its logical volume
                  detector1Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps
  //Now lets change the color to green and alpha to 0.15 so we can look through it
  G4VisAttributes greenVis;
  greenVis.SetColor(0.0, 1.0, 0.0, 0.15);
  detector1LV->SetVisAttributes(greenVis);


  // DETECTOR: Warn if there's an overlap
  if ( detector1PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;


///ANOTHER DETECTOR. I want this one a box around the buildings, to measure the radition on them
  std::string detector2Name = "Detector2";
  G4ThreeVector detector2Position( 0, 0, 450*cm-100*cm );

  // first we define an exterior
  G4Box* detector2Exterior = new G4Box(
                  "detector2Exterior",      // its name
                  150*cm, 150*cm, 200*cm);       //x,y,z dimensions
// and an interior
  G4Box* detector2Interior = new G4Box(
    "detector2interior",
    149*cm, 149*cm, 199*cm);
  //create the shell call it detector 2 by subtracting the two above solids
  G4SubtractionSolid* detector2S = new G4SubtractionSolid(detector2Name,detector2Exterior,detector2Interior);
// credit to Surajsinghdeos from this post https://geant4-forum.web.cern.ch/t/how-to-create-a-hollow-box/4690/4
  
  // DETECTOR: Logical volume (how to treat it)
  G4LogicalVolume* detector2LV = new G4LogicalVolume(
                  detector2S,         // its solid
                  lead,       // its material
                  detector2Name,      // its name
                  0, 0, 0 );         // Modifiers we don't use

  // DETECTOR: Physical volume (where is it)
  G4VPhysicalVolume* detector2PV = new G4PVPlacement(
                  rotationMatrix,                 // 90degree x-rotation
                  detector2Position,  // where is it
                  detector2LV,        // its logical volume
                  detector2Name,      // its name
                  worldLV,           // its mother volume
                  false,             // no boolean operations
                  0,                 // copy number
                  true );            // checking overlaps

  // Create a G4VisAttributes object with a blue color and 15% opacity
  G4VisAttributes blueVis;
  blueVis.SetColor(0.0, 0.0, 1.0, 0.15);

  // Set the visualization attributes for a different particle
  detector2LV->SetVisAttributes(blueVis);

   // DETECTOR: Warn if there's an overlap
  if ( detector2PV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;


  // Always return the physical world
  return worldPV;
}

// 
void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  // I set the field in run.mac: its just zero: beamopia doesn't have a 
  // magentic field on its version of "earth"
  G4ThreeVector fieldValue = G4ThreeVector();
  m_magneticFieldMessenger = new G4GlobalMagFieldMessenger( fieldValue );

  // Register the field messenger for deleting
  G4AutoDelete::Register( m_magneticFieldMessenger );

  // Make "sensitive detector 1" for the liquid argon
  std::string detector1Name = "Detector1";

  auto argon1Detector = new EnergyCounter(detector1Name, 0 );
  G4SDManager::GetSDMpointer()->AddNewDetector( argon1Detector );
  this->SetSensitiveDetector( detector1Name, argon1Detector );

// Make "sensitive detector 2" for the liquid argon
  std::string detector2Name = "Detector2";

  auto argon2Detector = new EnergyCounter(detector2Name, 1 );
  G4SDManager::GetSDMpointer()->AddNewDetector( argon2Detector );
  this->SetSensitiveDetector( detector2Name, argon2Detector );

}
