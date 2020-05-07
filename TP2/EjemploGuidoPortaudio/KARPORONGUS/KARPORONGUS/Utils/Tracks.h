#pragma once
#include<string>
#include "Note.h"
#include <vector>
class Tracks
{
public:
	Tracks();
	~Tracks();
	std::string instrumentName;
	std::vector<Note> Notes;
	std::string userInstrumentChoice;
};

