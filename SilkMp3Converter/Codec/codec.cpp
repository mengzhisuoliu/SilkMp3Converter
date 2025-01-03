#include <stdio.h>

#include "codec.h"

using namespace std;

int Silk2Mp3(string inpath, string outpath, int sr)
{
    FILE *fSilk = fopen(inpath.c_str(), "rb");
    FILE *fMp3  = fopen(outpath.c_str(), "wb");

    if (fSilk == NULL) {
        printf("Error: could not open input file %s\n", inpath.c_str());
        exit(0);
    }

    if (fMp3 == NULL) {
        printf("Error: could not open input file %s\n", outpath.c_str());
        exit(0);
    }

    vector<uint8_t> silk, pcm, mp3;
    fseek(fSilk, 0L, SEEK_END);
    size_t sz = ftell(fSilk);
    fseek(fSilk, 0L, SEEK_SET);

    silk.resize(sz);
    fread(silk.data(), sizeof(uint8_t), sz, fSilk);

    SilkDecode(silk, pcm, sr);
    Mp3Encode(pcm, mp3, sr / 2);

    fwrite(mp3.data(), sizeof(uint8_t), mp3.size(), fMp3);

    return 0;
}

int Silk2Mp3(vector<uint8_t> &silk, vector<uint8_t> &mp3, int sr)
{
    vector<uint8_t> pcm;
    SilkDecode(silk, pcm, sr);
    Mp3Encode(pcm, mp3, sr / 2);
    return 0;
}

int Silk2Mp3(vector<uint8_t> &silk, string mp3path, int sr)
{
    vector<uint8_t> pcm;
    SilkDecode(silk, pcm, sr);
    Mp3Encode(pcm, mp3path, sr / 2);
    return 0;
}
