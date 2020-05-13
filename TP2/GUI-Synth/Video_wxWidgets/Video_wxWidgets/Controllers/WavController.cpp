#include "WavController.h"
using namespace std;
namespace little_endian_io {
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;

WavController::WavController() {

}

void WavController::compileWav(vector<SynthTrack> allTracks, double duration_, string wavName_, double volume_) {
	this->duration = duration_;
	this->wavName = wavName_;
	vector <double> wavVector = vector<double>(ceil(this->duration * SAMPLE_RATE), 0);
	this->volume = volume_;
	for (unsigned int track = 0; track < allTracks.size(); track++) {
		for (unsigned int note = 0; note < allTracks[track].track.size(); note++) {
			int T = floor(allTracks[track].track[note].t_on * SAMPLE_RATE);
			for (unsigned int i = 0; i < allTracks[track].track[note].sound.size(); i++) {
				wavVector[i + T] += allTracks[track].track[note].sound[i];
			}
		}
	}
	double max = *max_element(wavVector.begin(), wavVector.end());
	for (int i = 0; i < wavVector.size(); i++) {
		wavVector[i] = wavVector[i] / max;
	}
	LaJEEPETA.push_back(wavVector);
}

void WavController::makeWav() {
	int channels = 2;
	double seconds = (LaJEEPETA.size() - 1) * TMAX + this->duration; //this->duration;
	string name = this->wavName;
	ofstream f(name + ".wav", ios::binary);

	// Write the file headers
	f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word(f, 16, 4);  // no extension data
	write_word(f, 1, 2);  // PCM - integer samples
	write_word(f, 2, 2);  // two channels (stereo file)

	write_word(f, SAMPLE_RATE, 4); //write_word(f, 44100, 4);  // samples per second (Hz)
	write_word(f, SAMPLE_RATE * (2) * channels, 4); //write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8

	write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

	// Write the data chunk header
	size_t data_chunk_pos = f.tellp();
	f << "data----";  // (chunk size to be filled in later)

	// Write the audio samples
	double max_amplitude = volume;  // "volume"


	int N = SAMPLE_RATE * seconds;  // total number of samples
	int T = TMAX * SAMPLE_RATE;
	vector<double> antiAereo;
	
	antiAereo.resize(N);		//10 716 217		g11 477 155

	for (unsigned int n = 0; n < LaJEEPETA.size(); n++) {
		for (int k = 0; k < LaJEEPETA[n].size(); k++) { 
			antiAereo[k + n * T] += LaJEEPETA[n][k];
		}
	}

	double amplitude = 1;
	for (int i = 0; i < N; i++) {
		double value = antiAereo[i];
		write_word(f, (int)((amplitude)*value * volume), 2);
		write_word(f, (int)((amplitude)*value * volume), 2);
	}
	
	

	// (We'll need the final file size to fix the chunk sizes above)
	size_t file_length = f.tellp();

	// Fix the data chunk header to contain the data size
	f.seekp(data_chunk_pos + 4);
	write_word(f, file_length - data_chunk_pos + 8);

	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	f.seekp(0 + 4);
	write_word(f, file_length - 8, 4);

	this->LaJEEPETA.clear();
}

WavController::~WavController() {
}
