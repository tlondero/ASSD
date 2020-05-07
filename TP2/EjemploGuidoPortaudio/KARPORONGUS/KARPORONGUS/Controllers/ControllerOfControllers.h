#pragma once
#include "AcousticGuitarController.h"
#include "ElectricGuitarController.h"
#include "BanjoController.h"
#include "DrumController.h"
// Aca se incluyen todos los instrumentos
#include "../Utils/Tracks.h"
#include "../UserInput/UserInput.h"
class ControllerOfControllers
{
public:
	ControllerOfControllers();
	~ControllerOfControllers();
	vector<SynthTrack> sytnsynthesisProject(vector<Tracks> projectTracks,UserInput userData);
	
private:
	AcousticGuitarController AGController;
	ElectricGuitarController EGController;
	BanjoController BController;
	DrumController DController;
	// aca agregas tus instrumentos
};

