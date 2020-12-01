#pragma once
/**
 @header
 @brief Relevant interface for playing audio files
 */
#import <Foundation/Foundation.h>

@class ThunderAudioFilePlayer;
/**
 @protocol
 @brief Proxy for playback events of audio files
 */
__attribute__((visibility("default"))) @protocol ThunderAudioFilePlayerDelegate <NSObject>

// 本地文件播放事件的各种状态
typedef NS_ENUM(NSInteger, ThunderAudioFilePlayerEvent)
{
  AUDIO_PLAY_EVENT_OPEN = 1, // 打开文件
  AUDIO_PLAY_EVENT_PLAY = 2, // 开始播放
  AUDIO_PLAY_EVENT_STOP = 3, // 停止播放
  AUDIO_PLAY_EVENT_PAUSE = 4, // 暂停播放
  AUDIO_PLAY_EVENT_RESUME = 5, // 恢复播放
  AUDIO_PLAY_EVENT_END = 6, // 播放完毕
  AUDIO_PLAY_EVENT_SEEK_COMPLETE = 7, // 快进播放
};
	
// 本地文件播放事件的错误码
typedef NS_ENUM(NSInteger, ThunderAudioFilePLayerErrorCode)
{
  AUDIO_PLAYER_OPEN_FILE_PATH_ERROR = -4, // 文件路径错误
  AUDIO_PLAYER_OPEN_FILE_FORMAT_NOT_SUPPORT = -3, // 文件格式不支持
  AUDIO_PLAYER_OPEN_FILE_DECODER_FAILED = -2, // 文件格式解码出错
  AUDIO_PLAYER_CREATE_FILE_DECODER_FAILED = -1, // 文件格式解析出错
  AUDIO_PLAYER_STATUS_SUCCESS = 0, // 成功
};

@optional
/**
 * deprecated("use onAudioFileStateChange: instead.")
 * @brief End of audio file playback
 */
- (void)onAudioFilePlayEnd __attribute__((deprecated("use onAudioFilePlayEnd instead.")));

/**
 * deprecated("use onAudioFileStateChange: instead.")
 * @brief End of audio file playback
 */
- (void)onAudioFilePlayEnd:(nonnull ThunderAudioFilePlayer*)player;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 * @brief Callback of playback error of audio files
 * @param [IN] errorCode = 0:  Opening file successful
               errorCode = -1: Error in parsing file format
               errorCode = -2: Error in decoding file format
               errorCode = -3: Unsupported file format 
               errorCode = -4: No file path exists
 */
- (void)onAudioFilePlayError:(nonnull ThunderAudioFilePlayer*)player errorCode:(int)errorCode;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 @brief Start playing
*/
- (void)onAudioFilePlaying:(nonnull ThunderAudioFilePlayer*)player;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 @brief Pause playing
*/
- (void)onAudioFilePause:(nonnull ThunderAudioFilePlayer*)player;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 @brief Resume playing
*/
- (void)onAudioFileResume:(nonnull ThunderAudioFilePlayer*)player;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 @brief Callback on playback being stopped by user
*/
- (void)onAudioFileStop:(nonnull ThunderAudioFilePlayer*)player;

/**
 * deprecated("use onAudioFileStateChange: instead.")
 @brief Fast forward to the specified time after completion
 @param [OUT] milliseconds Actual fast forwarding progress
 */
- (void)onAudioFileSeekComplete:(nonnull ThunderAudioFilePlayer*)player milliseconds:(int)milliseconds;


/**
 @brief 播放器状态变化通知
 @param [OUT] event 播放事件 查看 ThunderAudioFilePlayerEvent
 @param [OUT] errorCode 状态码  查看 ThunderAudioFilePLayerErrorCode
 */
- (void)onAudioFileStateChange:(nonnull ThunderAudioFilePlayer*)player event:(ThunderAudioFilePlayerEvent)event  errorCode:(ThunderAudioFilePLayerErrorCode)errorCode;

/*!
 @brief Audio playing volume
 @param [OUT] volume Playback volume
 @param [OUT] currentMs Current playback duration
 @param [OUT] totalMs Total playback duration
 */
- (void)onAudioFileVolume:(nonnull ThunderAudioFilePlayer*)player
                   volume:(uint32_t)volume
                   currentMs:(uint32_t)currentMs
                   totalMs:(uint32_t)totalMs;
@end

/**
 @brief Interface for playing audio files
 @remark One ThunderAudioFilePlayer instance should be created for each file to be played.
 */
__attribute__((visibility("default"))) @interface ThunderAudioFilePlayer : NSObject

/**
 @brief Setting callback of playback event of audio file
 @param [IN] delegate Event callback
 */
- (void)setPlayerDelegate:(nullable id<ThunderAudioFilePlayerDelegate>)delegate;

/**
 @brief Open audio files supporting mp3, aac and wav formats
 @param [IN] path File path
 */
- (void) open:(nonnull NSString*)path;

/**
 @brief Close audio file
 */
- (void) close;

/**
  @brief Start playing
 */
- (void) play;

/**
 @brief Stop playing
 */
- (void) stop;

/**
 @brief Pause playing
 */
- (void) pause;

/**
 @brief Continue to play
 */
- (void) resume;

/**
 @brief Skip to specified playing time
 @param [IN] timeMS Playing time
 */
- (void) seek:(uint32_t)timeMS;

/**
 @brief Get the total play time of file
 @return Total play time, unit: millisecond
 */
- (uint32_t) getTotalPlayTimeMS;

/**
 @brief Get current played duration
 @return Played duration (in millisecond)
 */
- (uint32_t) getCurrentPlayTimeMS;

/**
 @brief Set playing volume of current file
 @param [IN] volume Playback volume in [0-100]
 */
- (void) setPlayVolume:(uint32_t)volume;

/**
 @brief Adjust volume of music file in mixed video being played locally. Please call this method in the channel
 @param [IN] volume Playing volume in 0-100]
 @return 0: succeeded, <0: Failed
 */
- (int) setPlayerLocalVolume:(uint32_t)volume;

/**
 @brief Adjust volume of music file in mixed video being played remotely. Please call this method in the channel
 @param [IN] volume Playing volume in 0-100]
 @return 0: succeeded, <0: Failed
 */
- (int) setPlayerPublishVolume:(uint32_t)volume;

/**
 @brief Get the volume of music file played locally
 @return Succeeded call of method: return the volume value in [0-100]; <0: Method call failed
 */
- (int) getPlayerLocalVolume;

/**
 @brief Get the volume of music file played remotely
 @return Succeeded call of method: return the volume value in [0-100]; <0: Method call failed
 */
- (int) getPlayerPublishVolume;

/**
 @brief Set a tone for audio play
 @param [IN] val Tone value: -5, -4, -3, -2, -1, 0 (normal), 1, 2, 3, 4, 5
 */
- (void) setSemitone:(int)val;

/**
 @brief 设置音频播放速率
 @param [IN] val 速率值 0.5，0.75， 1.0， 1.25，1.5，1.75，2.0
 */
- (void) setTempo:(float)val;

/**
 @brief 设置音频播放方位
 @param [IN] azimuth -90~90
 */
- (void) setPosition:(int)azimuth;

/**
 @brief Set the number of loop playback
 @param [IN] cycle Positive integer: the number of loop; 0: loop canceled; -1: infinite loop
 @return 0: succeeded call of method; <0: failed call of method
*/
- (int) setLooping:(int)cycle;

/**
 @brief Select audio track
 @param [IN] trackIndex Audio track index
 @return Succeeded: 0,  failed: -1
 */
- (int) selectAudioTrack:(int)trackIndex;

/**
@brief Get the number of audio tracks
@return Return the number of audio tracks of file
*/
-(int) getAudioTrackCount;

/**
 @brief Whether to set the current playing file as live streaming accompaniment
 @param [IN] enable Enabled or disabled, disabled by default
 */
- (void) enablePublish:(BOOL)enable;

/**
 @brief Whether to enable the spectrum
 @param [IN] enable Enabled or disabled, disabled by default
 */
- (void)enableSpectrum:(BOOL)enable;

/**
 @brief Whether to enable volume callback
 @param [IN] enable Enabled or disabled,
 @param [IN] interval Callback interval
 */
- (void) enableVolumeIndication:(BOOL)enable interval:(int) interval;

/**
 @brief Whether to set the accompaniment as the standard stream for video mixing
 @param [IN] standard YES: Standard stream NO: Non-standard stream NO by default
 */
-(void)setMixStandard:(BOOL)standard;

/**
 @brief Query whether the accompaniment is the standard stream for video mixing
 @return bool, YES: Standard stream,  NO:  Non-standard stream
 */
-(BOOL)isMixStandard;

/*!
 @brief Get spectrum information in a range of [0-1]
 @param [IN] buffer Spectrum buffer
 @param [IN] len Length of spectrum buffer
 @return Return effective data length
 */
-(int) getCurrentSpectrum:(float* _Nonnull)buffer len:(int) len;

@end

