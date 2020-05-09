#pragma once
#include "AcousticGuitarController.h"
#include "ElectricGuitarController.h"
#include "BanjoController.h"
#include "DrumController.h"
#include "BellController.h"
#include "ClarinetController.h"
#include "TromboneController.h"
#include "OrganController.h"
#include "TrumpetController.h"

// Aca se incluyen todos los instrumentos
#include "../Utils/Tracks.h"
#include "../UserInput/UserInput.h"
class ControllerOfControllers
{
public:
	ControllerOfControllers();
	~ControllerOfControllers();
	vector<SynthTrack> sytnsynthesisProject(vector<Tracks> projectTracks,UserInput userData);
	vector<SynthTrack> sytnsynthesisPreview(vector<Tracks> projectTracks, UserInput userData);
	
private:
	AcousticGuitarController AGController;
	ElectricGuitarController EGController;
	BanjoController BController;
	DrumController DController;
	BellController bellController;
	ClarinetController CController;
	TromboneController TController;
	OrganController OController;
	TrumpetController TrumpController;
	// aca agregas tus instrumentos
};

