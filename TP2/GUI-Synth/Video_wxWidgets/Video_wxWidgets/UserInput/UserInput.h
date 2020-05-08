#pragma once
#include <string>
#include <vector>
#include "UserChoice.h"
using namespace std;
class UserInput
{
public:
	UserInput();
	~UserInput();
	string wavName;
	vector<UserChoice> pairTrackInst;
	
	
};

