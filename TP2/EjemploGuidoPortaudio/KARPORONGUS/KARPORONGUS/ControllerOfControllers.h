#pragma once
#include "AcousticGuitarController.h"
// Aca se incluyen todos los instrumentos
#include "Utils/Tracks.h"
#include "UserInput.h"
class ControllerOfControllers
{
public:
	ControllerOfControllers();
	~ControllerOfControllers();
	vector<SynthTrack> sytnsynthesisProject(vector<Tracks> projectTracks,UserInput userData);
	
private:
	AcousticGuitarController AGController;
	// aca agregas tus instrumentos
};

