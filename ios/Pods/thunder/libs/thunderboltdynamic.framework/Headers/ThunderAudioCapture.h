#pragma once
#import <Foundation/Foundation.h>
#import <CoreMedia/CMSampleBuffer.h>
/**
 @protocol
 @brief Interface for pushing video data
 @remark
 The [ThunderVideoCaptureProtocol startCapture] interface provides a ThunderVideoPublisherProtocol object to the external, and the object calls the pushing interface to push external video data.
 */
__attribute__((visibility("default"))) @protocol ThunderAudioPublisherProtocol <NSObject>

@required
/**
 @brief Interface for pushing original audio data
 @param [IN] samples Original audio data
 @param [IN] cts Audio capture time (in millisecond)
 */
- (void)pushCaptureData:(nonnull NSData*)samples cts:(uint32_t)cts;

/**
 @brief External stream publishing audio
 @param [IN] pcmId Type
 @param [IN] pcmData Audio data
 */
- (void)pushExtAudioData:(uint32_t)pcmId pcmData:(nullable CMSampleBufferRef)pcmData;

@end

/**
 @protocol
 Interface for implementing video capture
 */
__attribute__((visibility("default"))) @protocol ThunderAudioCaptureProtocol <NSObject>

@required

/**
 @brief Start capture
 @param [IN] protocol Interface for pushing data @see ThunderVideoPublisherProtocol
 */
- (void)startCapture:(nullable id<ThunderAudioPublisherProtocol>)protocol;

/**
 @brief End capturing
 */
- (void)stopCapture;

@optional
/**
 @brief Get the sampling rate of audios
 @return Sampling rate
 */
- (uint32_t)getSampleRate;

/**
 @brief Get the number of used channels
 @return Number of channels
 */
- (uint32_t)getChannels;

/**
 @brief Get the bit depth of used data
 @return Sampling bit depth
 */
- (uint32_t)getBitDepth;

@end

/**
 @protocol
 @brief Callback delegate on audio data
 */
__attribute__((visibility("default"))) @protocol ThunderDefaultMicDataDelegate <NSObject>

@required

/**
 @brief Callback interface for audio data
 @param [IN] data Original audio data
 @param [IN] bActiveAudio Whether audio data transmitted currently contains active data (that is, someone is speaking)
 */
- (void)onAudioDataCallback:(nonnull NSData*)data bActiveAudio:(bool)bActiveAudio;

@end

/**
 @class
 @brief Microphone capture object in SDK by default
 */
__attribute__((visibility("default"))) @interface ThunderDefaultMic : NSObject <ThunderAudioCaptureProtocol>
/**
 @brief Setting callback of microphone captured data
 @param [IN] sampleRate Sampling rate of audio data
 @param [IN] channels Number of sampling channels for audio data
 @param [IN] delegate Callback of audio data
 @remark Not supporting setting the sampling bit depth of audio data, and providing the internal fixed value of 16 bit
 */
- (void)setMicDataDelegate:(uint32_t)sampleRate
                  channels:(uint32_t)channels
                  delegate:(nullable id<ThunderDefaultMicDataDelegate>)delegate;

/**
 @brief Obtain externally configured callbacks on camera capture data
 @return Externally configured data callbacks
 */
- (nullable id<ThunderDefaultMicDataDelegate>)getMicDataDelegate;
@end


/**
 @brief External stream publishing on audio
 */
__attribute__((visibility("default"))) @interface ThunderExtAudio : NSObject <ThunderAudioCaptureProtocol>

@property NSUInteger sampleRate;
@property NSUInteger channelsPerFrame;
@property uint32_t pcmId;

- (BOOL)pushPcmData:(uint32_t)pcmId pcmData:(nullable CMSampleBufferRef)pcmData;

- (void)pushCaptureData:(nonnull NSData*)samples cts:(uint32_t)cts;

@end
