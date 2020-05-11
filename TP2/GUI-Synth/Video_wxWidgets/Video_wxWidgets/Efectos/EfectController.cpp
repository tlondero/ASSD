#include "EfectController.h"

EfectController::EfectController() {

}
vector<SynthTrack> EfectController::applyEfects(vector<SynthTrack> tracketeo) {
	vector<SynthTrack> temp= tracketeo;
	for (unsigned int track = 0; track < tracketeo.size(); track++) {
		if (tracketeo[track].effect2Apply == EffList[0]) {
			for (unsigned int note = 0; note < tracketeo[track].track.size(); note++) {
				temp[track].track[note].sound=this->eco.applyEffect(tracketeo[track].track[note].sound, tracketeo[track].T, tracketeo[track].D);
			}
		}
		if (tracketeo[track].effect2Apply == EffList[1]) {
			for (unsigned int note = 0; note < tracketeo[track].track.size(); note++) {
				temp[track].track[note].sound = this->reverb.applyEffect(tracketeo[track].track[note].sound, tracketeo[track].T, tracketeo[track].M);
			}
		}
	}
	return tracketeo;
}
EfectController::~EfectController() {

}
