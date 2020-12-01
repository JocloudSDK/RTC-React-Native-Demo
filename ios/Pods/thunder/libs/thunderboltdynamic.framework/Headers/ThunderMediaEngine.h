#pragma once
#ifndef ThunderMediaEngine_h
#define ThunderMediaEngine_h

#if defined _WIN32 || defined __CYGWIN__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

namespace THUNDER
{

class IAudioFrameObserver
{
 public:
  enum AUDIO_FRAME_TYPE
  {
    FRAME_TYPE_PCM16 = 0, // PCM 16bit little endian
  };

  struct AudioFrame
  {
    AUDIO_FRAME_TYPE type;

    int samples; // Sample quantity of the frame
    int bytesPerSample; // Bytes per sample: PCM (16 digits) contains two types
    int channels; // Quantity of channels (crossed data for stereo); 1: single track, 2: dual track
    int samplesPerSec; // Sampling rate
    void* buffer; // data buffer

    long long renderTimeMs; // Not used momentarily
    int avsync_type; // Not used momentarily
  };

 public:
  // Callback on original audio capture data
  __attribute__((visibility("default"))) virtual bool onRecordAudioFrame(AudioFrame& audioFrame) { return true;}
  // Callback on original audio play data
  __attribute__((visibility("default"))) virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) { return true;}
  // Callback on original data decoded by remote audio users
  __attribute__((visibility("default"))) virtual bool onPlaybackAudioFrameBeforeMixing(const char* uid, AudioFrame& audioFrame) { return true;}
  // Callback on mix of capture and render data
  __attribute__((visibility("default"))) virtual bool onMixedAudioFrame(AudioFrame& audioFrame) { return true;}
};

// MediaEngine C++interface
class IMediaEngine
{
 public:
  IMediaEngine();
  virtual ~IMediaEngine();

 public:
  /*!
   @brief Register an audio frame observer
   @param [IN] observer Audio observer object
   @remark The user shall inherit the IAudioFrameObserver interface class and duplicate four methods. These methods will be used to transfer the related original audio data to the user.
   */
  __attribute__((visibility("default"))) static bool registerAudioFrameObserver(IAudioFrameObserver* observer);
};

} // namespace THUNDER

#endif /* ThunderMediaEngine_h */
