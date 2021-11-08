#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#define AUDIO_BLOCK_SAMPLES  128
#define AUDIO_SAMPLE_RATE_EXACT 44100.0f
#include <stddef.h>

class AudioStream
{
  public:
    AudioStream(int a, void* b) {}
    virtual ~AudioStream();
    virtual size_t available() {return 384000 /10 /AUDIO_BLOCK_SAMPLES; }
    virtual void update();


};

#endif // AUDIOSTREAM_H
