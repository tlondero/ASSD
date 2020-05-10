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
	this->wavVector = vector<double>(ceil(this->duration * SAMPLE_RATE), 0);
	this->volume = volume_;
	for (unsigned int track = 0; track < allTracks.size(); track++) {
		for (unsigned int note = 0; note < allTracks[track].track.size(); note++) {
			int T = floor(allTracks[track].track[note].t_on * SAMPLE_RATE);
			for (unsigned int i = 0; i < allTracks[track].track[note].sound.size(); i++) {
				this->wavVector[i + T] += allTracks[track].track[note].sound[i];
			}
		}
	}

	//reverb
	//T = 3tn/(-log|gn|) para comb paralelo
	/*
	std::vector<double> M_parallel = { 4799, 4999, 5399, 5801 , 6013};
	std::vector<double> g_parallel = { -0.742, -0.733, -0.715, -0.697 , -0.656};
	std::vector<double> M_series = { 1051, 337 };
	std::vector<double> g_series = { -0.7, -0.7 };
	std::vector<double> wavVector2(this->wavVector.size(), 0);
	std::vector<double> temp(this->wavVector.size(), 0);
	double mix_ratio = 1;


	for (int j = 0; j < M_parallel.size(); j++) {
		for (int i = 0; i < this->wavVector.size(); i++) {
			if (i - M_parallel[j] > 0) {
				temp[i] = this->wavVector[i] + g_parallel[j] * this->wavVector[i - M_parallel[j]];
			}
			else {
				temp[i] = this->wavVector[i];
			}
			wavVector2[i] += temp[i];
		}
	}

	for (int j = 0; j < M_series.size(); j++) {
		for (int i = 0; i < this->wavVector.size(); i++) {
			if (i - M_series[j] > 0) {
				temp[i] = -1 * g_series[j] * wavVector2[i] + wavVector2[i - M_series[j]] + g_series[j] * temp[i - M_series[j]];
			}
			else {
				temp[i] = wavVector2[i];
			}
		}
		wavVector2 = temp;
	}

	for (int i = 0; i < this->wavVector.size(); i++) {
		this->wavVector[i] += mix_ratio * wavVector2[i];
	}
	*/

	//Eco simple
	/*	double M = 10000;
	double g = -0.7;

	for (int i = 0; i < this->wavVector.size(); i++) {
		if(i - M > 0)
			this->wavVector[i] = this->wavVector[i] + g * this->wavVector[i - M];
	} 
	*/

	double max = *max_element(wavVector.begin(), wavVector.end());
	for (int i = 0; i < wavVector.size(); i++) {
		wavVector[i] = wavVector[i] / max;
	}
}

void WavController::makeWav() {
	int channels = 2;
	double seconds = this->duration;
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
	for (unsigned int n = 0; n < N; n++)
	{
		if (n >= this->wavVector.size())this->wavVector.push_back(0);
		double amplitude = 1;
		double value = this->wavVector[n];
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

}
WavController::~WavController() {
}
