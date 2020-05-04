#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "WavGen.h"
#define SAMPLE_RATE     44100
#define MAX_AMP         32760
#define TWO_PI          6.283185307179586476925286766559

using namespace std;

namespace little_endian_io
{
    template <typename Word>
    std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
    {
        for (; size; --size, value >>= 8)
            outs.put(static_cast <char> (value & 0xFF));
        return outs;
    }
}
using namespace little_endian_io;

int makeWav(int channels, double seconds, string name,vector<double> data,double volume)        //frequency in Hz
{
    ofstream f(name + ".wav", ios::binary);
    int sample_rate = SAMPLE_RATE;
    
    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word(f, 16, 4);  // no extension data
    write_word(f, 1, 2);  // PCM - integer samples
    write_word(f, 2, 2);  // two channels (stereo file)
   
    write_word(f, sample_rate, 4); //write_word(f, 44100, 4);  // samples per second (Hz)
    write_word(f, sample_rate * (2) * channels, 4); //write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
    
    write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)

    // Write the audio samples
    // (We'll generate a single C4 note with a sine wave, fading from left to right)
    constexpr double two_pi = TWO_PI;
     double max_amplitude = volume;  // "volume"

    int N = sample_rate * seconds;  // total number of samples
    for (int n = 0; n < N; n++)
    {
		if (n >= data.size())data.push_back(0);
		double amplitude =  1;// (double)n / N * max_amplitude;
		double value = data[n];
        write_word(f, (int)((max_amplitude - amplitude) * value), 2);
        write_word(f, (int)((max_amplitude - amplitude) * value), 2);
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp(data_chunk_pos + 4);
    write_word(f, file_length - data_chunk_pos + 8);

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp(0 + 4);
    write_word(f, file_length - 8, 4);

    return 0;

}

//int main(void)
//{
//    int a = makeSin(200, 2, 1, "mamee");
//	return 0;
//}