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
	string finalEfect;
	double T=0;
	double D=0.9;
	double M=0;
	
};

