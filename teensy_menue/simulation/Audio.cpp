#include "Audio.h"
#include "play_fats_raw.h"

int CCM_CS1CDR;

int AudioMem;
bool AudioIrqs = true;

int AudioProcessorUsage()
{
    return 22;
}

int AudioMemoryUsage()
{
  return 224;
}

int AudioProcessorUsageMax()
{
  return 33;
}

void AudioProcessorUsageMaxReset()
{

}

void AudioMemory(int mem)
{
  AudioMem = mem;
}

void AudioInterrupts()
{
   AudioIrqs = true;
}

void AudioNoInterrupts()
{
   AudioIrqs = false;
}

void set_audioClock(int c0, int c1, int c2, bool x)
{

}
void AudioPlayFatsRaw::stop(void)
{

}
bool AudioPlayFatsRaw::play(const char*)
{
  return true;
}

void AudioPlayFatsRaw::begin()
{

}
void AudioPlayFatsRaw::update()
{

}


AudioStream::~AudioStream()
{

}

void AudioStream::update()
{

}

