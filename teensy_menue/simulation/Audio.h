#ifndef AUDIO_H
#define AUDIO_H
#include "AudioStream.h"
#include <cstdint>

class AudioInputSpiMono : public AudioStream
{
  public:
    AudioInputSpiMono() : AudioStream(1,nullptr) {}
};

class AudioOutputMQS: public AudioStream
{
  public:
    AudioOutputMQS(): AudioStream(1,nullptr) {}
};
class AudioSynthWaveformSine: public AudioStream
{
  public:
    AudioSynthWaveformSine(): AudioStream(1,nullptr) {}
    void amplitude(float ampl) {}
    void frequency(float f) {}
    void phase (float p) {}
};
class AudioEffectMultiply: public AudioStream
{
  public:
    AudioEffectMultiply(): AudioStream(1,nullptr) {}
};
class AudioMixer4: public AudioStream
{
  public:
    AudioMixer4(): AudioStream(1,nullptr) {}
    void gain(int chan, float gain) {}
};

class AudioAnalyzePeak: public AudioStream
{
 public:
    AudioAnalyzePeak() : AudioStream(1,nullptr) {}
    float read() {return 22.0;}
};
class AudioFilterBiquad: public AudioStream
{
 public:
    AudioFilterBiquad() : AudioStream(1, nullptr) {}
    void setHighpass(int n, float f, float q = 0.7) {}
    void setLowpass(int n, float f, float q) {}
    void setBandpass(int n, float f, float q) {}
};
class AudioEffectDelay: public AudioStream
{
  public:
    AudioEffectDelay() : AudioStream(1,nullptr) {}
    void delay(int b, int ms) {}
};
class AudioAnalyzeFFT1024: public AudioStream
{
  public:
    AudioAnalyzeFFT1024() : AudioStream(1,nullptr) {}
  uint16_t output[1024];
};

class AudioConnection
{
  public:
    AudioConnection(AudioStream a, int b, AudioStream c, int d) {}
    AudioConnection(AudioStream a, AudioStream c) {}
};

class AudioRecordQueue : public AudioStream
{
  public:
    AudioRecordQueue() :AudioStream(1,nullptr) {}
    void begin(){ m_available = 384000 /10 / AUDIO_BLOCK_SAMPLES; }
    int16_t* readBuffer() {return m_buf;}
    void freeBuffer() {}
    virtual size_t available() { return m_available; }
    void end() { m_available = 0;}
  private:
    int16_t m_buf[256];
    size_t m_available = 0;
};

void set_audioClock(int c0, int c1, int c2, bool x);
int AudioProcessorUsage();
int AudioMemoryUsage();
int AudioProcessorUsageMax();
void AudioMemory(int mem);
void AudioInterrupts();
void AudioNoInterrupts();
void AudioProcessorUsageMaxReset();

#endif // AUDIO_H
