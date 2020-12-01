#pragma once
#import <Foundation/Foundation.h>
#import "ThunderAPIDefine.h"
#import "ThunderAudioFilePlayer.h"
#import "ThunderObjects.h"
#import "ThunderVideoCapture.h"
/************************************************************************/
/* Description of Terms: 
1. Initialization: Indicates that the initialize function is called and Succeeded is returned.
2. Joining room: Indicates that the joinRoom function is called and Succeeded is returned.
3. Joining room successfully: Indicates that the onJoinRoomSuccess callback notification is returned.
*/
/************************************************************************/

#pragma mark enumDefine
// Set the SDK running mode; Note: Different modes are not interoperable. Only call it before the joinRoom is called!
typedef NS_ENUM(NSInteger, ThunderRtcConfig)
{
  THUNDER_CONFIG_DEFAULT = 0, // Default mode. =1
  THUNDER_CONFIG_NORMAL = 1, // Audio/video mode
  THUNDER_CONFIG_ONLY_AUDIO = 2, // Pure voice mode; optimize for pure audio
};

// Set room profile
typedef NS_ENUM(NSInteger, ThunderRtcRoomConfig)
{
  THUNDER_ROOM_CONFIG_LIVE = 0, // Live streaming (high quality, without interaction mode) (shifted to medium quality and strong interaction mode when connecting microphones)
  THUNDER_ROOM_CONFIG_COMMUNICATION = 1, // Communication (medium quality and strong interaction mode)
  THUNDER_ROOM_CONFIG_GAME = 3, // Game (low quality and strong interaction mode)
  THUNDER_ROOM_CONFIG_MULTIAUDIOROOM = 4, // Multi-person voice room (medium quality, economic traffic and strong interaction mode)
  THUNDER_ROOM_CONFIG_CONFERENCE = 5, // Conference (medium quality, strong interaction mode, applicable to frequent enabling/disabling of microphones, with smooth sound in enabling/disabling microphones)
};

typedef NS_ENUM(NSInteger, ThunderRtcRemotePlayType)
{
  THUNDER_REMOTE_PLAY_NORMAL = 0, // common audience view
  THUNDER_REMOTE_PLAY_MULTI = 1, // Multiple interaction view
};

typedef NS_ENUM(NSInteger, ThunderRtcAudioConfig)
{
  THUNDER_AUDIO_CONFIG_DEFAULT = 0, // Default settings. which is 1 in communication mode, and 2 in live mode.
  THUNDER_AUDIO_CONFIG_SPEECH_STANDARD = 1, // Specify the sampling rate of 16 KHz, audio encoding, single track, and encoding rate of around 18 kbps
  THUNDER_AUDIO_CONFIG_MUSIC_STANDARD_STEREO = 2, // Specify the sampling rate of 44.1 KHz,
                                                  // Voice encoding, dual track, encoding rate of around 24 kbps, and high delay in encoding
  THUNDER_AUDIO_CONFIG_MUSIC_STANDARD = 3, // Specify the sampling rate of 44.1 KHz, music encoding, dual track, encoding rate of around 40 kbps, and low delay in encoding
  THUNDER_AUDIO_CONFIG_MUSIC_HIGH_QUALITY_STEREO = 4, // Specify the sampling rate of 44.1KHz, music encoding, dual track, and encoding rate of around 128kbps
  THUNDER_AUDIO_CONFIG_MUSIC_HIGH_QUALITY_STEREO_192 = 5, // Specify the sampling rate of 44.1KHz, music encoding, dual track, and encoding rate of around 192kbps
};

typedef NS_ENUM(NSInteger, ThunderRtcCommutMode)
{
  THUNDER_COMMUT_MODE_DEFAULT = 0, // =1 by default
  THUNDER_COMMUT_MODE_HIGH = 1, // High interactive mode
  THUNDER_COMMUT_MODE_LOW = 2, // Low interactive mode
};

typedef NS_ENUM(NSInteger, ThunderRtcScenarioMode)
{
  THUNDER_SCENARIO_MODE_DEFAULT = 0, // =1 by default
  THUNDER_SCENARIO_MODE_STABLE_FIRST = 1, // Fluent priority: applicable for stable education
  THUNDER_SCENARIO_MODE_QUALITY_FIRST = 2, // Tone quality priority: applicable for show field with a few or without interaction
};

// Set log level
typedef NS_ENUM(NSInteger, ThunderRtcLogLevel)
{
  THUNDER_LOG_LEVEL_TRACE = 0,
  THUNDER_LOG_LEVEL_DEBUG = 1,
  THUNDER_LOG_LEVEL_INFO = 2,
  THUNDER_LOG_LEVEL_WARN = 3,
  THUNDER_LOG_LEVEL_ERROR = 4,
};

// Sound effect mode
typedef NS_ENUM(NSInteger, ThunderRtcSoundEffectMode)
{
  THUNDER_SOUND_EFFECT_MODE_NONE = 0, // Disable mode
  THUNDER_SOUND_EFFECT_MODE_VALLEY = 1, // VALLEY mode
  THUNDER_SOUND_EFFECT_MODE_RANDB = 2, // R&B mode
  THUNDER_SOUND_EFFECT_MODE_KTV = 3, // KTV mode
  THUNDER_SOUND_EFFECT_MODE_CHARMING = 4, // CHARMING mode
  THUNDER_SOUND_EFFECT_MODE_POP = 5, // Pop mode
  THUNDER_SOUND_EFFECT_MODE_HIPHOP = 6, // Hip-hop mode
  THUNDER_SOUND_EFFECT_MODE_ROCK = 7, // Rock mode
  THUNDER_SOUND_EFFECT_MODE_CONCERT = 8, // Concert mode
  THUNDER_SOUND_EFFECT_MODE_STUDIO = 9, // Studio mode
};
// Voice changing mode
typedef NS_ENUM(NSInteger, ThunderRtcVoiceChangerMode)
{
  THUNDER_VOICE_CHANGER_NONE = 0, // Disable mode
  THUNDER_VOICE_CHANGER_ETHEREAL = 1, // Ethereal
  THUNDER_VOICE_CHANGER_THRILLER = 2, // Thriller
  THUNDER_VOICE_CHANGER_LUBAN = 3, // Luban
  THUNDER_VOICE_CHANGER_LORIE = 4, // Lorie
  THUNDER_VOICE_CHANGER_UNCLE = 5, // Uncle
  THUNDER_VOICE_CHANGER_DIEFAT = 6, // Die-fat
  THUNDER_VOICE_CHANGER_BADBOY = 7, // Bad boy
  THUNDER_VOICE_CHANGER_WRACRAFT = 8, // Wracraft
  THUNDER_VOICE_CHANGER_HEAVYMETAL = 9, // Heavy metal
  THUNDER_VOICE_CHANGER_COLD = 10, // Cold
  THUNDER_VOICE_CHANGER_HEAVYMECHINERY = 11, // Heavy machinery
  THUNDER_VOICE_CHANGER_TRAPPEDBEAST = 12, // Trapped breast
  THUNDER_VOICE_CHANGER_POWERCURRENT = 13, // Power current
};

// Authentication results
typedef NS_ENUM(NSInteger, ThunderRtcSdkAuthResult)
{
  THUNDER_SDK_AUTHRES_SUCCUSS = 0, // Authentication succeeded
  THUNDER_SDK_AUTHRES_ERR_SERVER_INTERNAL = 10000, // Internal server error, try again
  THUNDER_SDK_AUTHRES_ERR_NO_TOKEN = 10001, // Without token, [ThunderAPI updateToken:] needs calling
  THUNDER_SDK_AUTHRES_ERR_TOKEN_ERR = 10002, // Token authentication failed (incorrect digital signature), which may be caused by incorrect appSecret
  THUNDER_SDK_AUTHRES_ERR_APPID = 10003, // appid in token is inconsistent with appid when authentication is executed
  THUNDER_SDK_AUTHRES_ERR_UID = 10004, // uid in token is inconsistent with uid when authentication is executed
  THUNDER_SDK_AUTHRES_ERR_TOKEN_EXPIRE = 10005, // token has expired
  THUNDER_SDK_AUTHRES_ERR_NO_APP = 10006, // App does not exist, which is not registered in the management background
  THUNDER_SDK_AUTHRES_ERR_TOKEN_WILL_EXPIRE = 10007, // token is about to expire
  THUNDER_SDK_AUTHRES_ERR_BAND = 10008, // The user is baned
};

// Offline reason
typedef NS_ENUM(NSUInteger, ThunderLiveRtcUserOfflineReason)
{
  THUNDER_SDK_USER_OFF_LINE_REASON_QUIT = 1, // The user is offline actively
  THUNDER_SDK_USER_OFF_LINE_REASON_DROPPED = 2, // Go offline for timeout, because no data received from the other side for a long time
  THUNDER_SDK_USER_OFF_LINE_REASON_BECOME_AUDIENCE = 3, // User status is switched from anchor to audience (live mode)
};

// Network quality
typedef NS_ENUM(NSUInteger, ThunderLiveRtcNetworkQuality)
{
  THUNDER_SDK_NETWORK_QUALITY_UNKNOWN = 0, // Unknown quality
  THUNDER_SDK_NETWORK_QUALITY_EXCELLENT = 1, // Excellent network quality
  THUNDER_SDK_NETWORK_QUALITY_GOOD = 2, // Good network quality
  THUNDER_SDK_NETWORK_QUALITY_POOR = 3, // The network quality is poor, but the communication is not affected even the user can feel its defects.
  THUNDER_SDK_NETWORK_QUALITY_BAD = 4, // The network quality is bad, and the communication can be barely made but is not smooth
  THUNDER_SDK_NETWORK_QUALITY_VBAD = 5, // The network quality is very bad, the communication cannot be made basically
  THUNDER_SDK_NETWORK_QUALITY_DOWN = 6, // The network has been disconnected, and the communication cannot be made at all
};

// Status of failure in sending secondary media information
typedef NS_ENUM(NSUInteger, ThunderSendMediaExtraInfoFailedStatus)
{
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_DATA_EMPTY = 1, // Extra information is null
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_DATA_TOO_LARGE = 2, // Excessively large size of senting data each time,
                                                           // It shall not exceed 200Byte each time when only audio is published, or 2048Byte each time when video is published
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_FREQUENCY_TOO_HIGHT = 3, // The sending frequency is too high, which cannot exceeds 100ms each time
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_NOT_IN_ANCHOR_SYSTEM = 4, // Not an anchor system
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_NO_JOIN_MEDIA = 5, // Channel not to be joined
  THUNDER_SEND_MEDIA_EXTRA_INFO_FAILED_NO_PUBLISH_SUCCESS = 6, // Publishing failed
};

// Geographic area
typedef NS_ENUM(NSInteger, ThunderRtcAreaType)
{
  THUNDER_AREA_DEFAULT = 0, // Default (domestic)
  THUNDER_AREA_FOREIGN = 1, // Overseas
  THUNDER_AREA_RESERVED = 2, // thunder-reserved
  THUNDER_AREA_PRIVATE = 10, // thunder-yylive
};

typedef NS_ENUM(NSInteger, ThunderSourceType)
{
  THUNDER_AUDIO_MIC = 0, // Only microphone
  THUNDER_AUDIO_FILE = 1, // Only file
  THUNDER_AUDIO_MIX = 2, // Microphone and file
  THUNDER_SOURCE_TYPE_NONE = 10, // Stop all uplink audio data
};

typedef NS_ENUM(NSInteger, ThunderSaverMode)
{
  THUNDER_AUDIO_SAVER_ONLY_CAPTURE = 0, // Only save all uplink audio data in the room.
                                        // Uplink audio data: Audio data of the anchor and accompany that have been set as uplink can be saved
  THUNDER_AUDIO_SAVER_ONLY_RENDER = 1, // Save audio data beyond the anchor in the room, e.g. audio/video data of the accompany and audience
  THUNDER_AUDIO_SAVER_BOTH = 2, // Save all audio data in the room
};

typedef NS_ENUM(NSInteger, ThunderFileMode)
{
  THUNDER_AUDIO_SAVER_FILE_APPEND = 0, // Open a text file, and the data written will override the file
  THUNDER_AUDIO_SAVER_FILE_OVERRIDE = 1, // Open another text file and write data at end of the file
};

typedef NS_ENUM(NSInteger, ThunderVideoRenderMode)
{
  THUNDER_RENDER_MODE_FILL = 0,
  THUNDER_RENDER_MODE_ASPECT_FIT = 1,
  THUNDER_RENDER_MODE_CLIP_TO_BOUNDS = 2,
  THUNDER_RENDER_MODE_ORIGINAL = 3,
};

// Use mode of original audio/video data
typedef NS_ENUM(NSInteger, ThunderAudioRawFrameOperationMode ) {
  THUNDER_AUDIO_RAW_FRAME_OPERATION_MODE_READ_ONLY = 1, // Read only mode. The user only acquires original data from AudioFrame
  THUNDER_AUDIO_RAW_FRAME_OPERATION_MODE_WRITE_ONLY = 2, // Write only mode. The user replaces data in AudioFrame for encoding transmission of SDK
  THUNDER_AUDIO_RAW_FRAME_OPERATION_MODE_READ_WRITE = 3, // Read-write mode
                                                         // The user obtains data from AudioFrame and modifies data. Then the data is returned to SDK for encoding and transmission.
};

// Connection status between SDK and server
typedef NS_ENUM(NSInteger, ThunderConnectionStatus)
{
  THUNDER_CONNECTION_STATUS_CONNECTING = 0, // Connecting
  THUNDER_CONNECTION_STATUS_CONNECTED = 1, // Connected
  THUNDER_CONNECTION_STATUS_DISCONNECTED = 2, // Disconnected
};

// Portrait and landscape orientation
typedef NS_ENUM(NSInteger, ThunderVideoCaptureOrientation)
{
  THUNDER_VIDEO_CAPTURE_ORIENTATION_PORTRAIT = 0, // Portrait
  THUNDER_VIDEO_CAPTURE_ORIENTATION_LANDSCAPE = 1, // Landscape
};

// Mirroring
typedef NS_ENUM(NSInteger, ThunderVideoMirrorMode)
{
  THUNDER_VIDEO_MIRROR_MODE_PREVIEW_MIRROR_PUBLISH_NO_MIRROR = 0, // The preview other than stream publishing is mirrored
  THUNDER_VIDEO_MIRROR_MODE_PREVIEW_PUBLISH_BOTH_MIRROR = 1, // Both preview and stream publishing are not mirrored
  THUNDER_VIDEO_MIRROR_MODE_PREVIEW_PUBLISH_BOTH_NO_MIRROR = 2, // Neither preview and stream publishing is not mirrored
  THUNDER_VIDEO_MIRROR_MODE_PREVIEW_NO_MIRROR_PUBLISH_MIRROR = 3, // Preview is not mirrored, but publish is mirrored
};

// Callback of video capture status
typedef NS_ENUM(NSInteger, ThunderVideoCaptureStatus)
{
  THUNDER_VIDEO_CAPTURE_STATUS_SUCEESS = 0, // Open successfully. Fail to detect ios currently. Add this value to unify with Android
  THUNDER_VIDEO_CAPTURE_STATUS_AUTHORIZED = 1, // User authorization
  THUNDER_VIDEO_CAPTURE_STATUS_NOT_DETERMINED = 2, // Users don’t give authority
  THUNDER_VIDEO_CAPTURE_STATUS_RESTRICTED = 3, // Occupied
  THUNDER_VIDEO_CAPTURE_STATUS_DENIED = 4, // Users refuse to give authority
  THUNDER_VIDEO_CAPTURE_STATUS_CLOSE = 5, // Camera closed
};

/**
 @brief Type of video capture data called back
 - THUNDER_Preprocess_DataType_PixelBuffer: SDK will return the camera data of pixelbuffer
 - THUNDER_Preprocess_DataType_Texture: SDK will return the data of texture ID
 */
typedef NS_ENUM(NSInteger, ThunderVideoCaptureFrameDataType)
{
  THUNDER_VIDEO_CAPTURE_DATATYPE_PIXELBUFFER = 0,
  THUNDER_VIDEO_CAPTURE_DATATYPE_TEXTURE = 1,
};

//Quality adaptability of local videos since last statistics (based on target frame rate and target bit rate)
typedef NS_ENUM(NSInteger, ThunderVideoQualityAdaptIndication)
{
    ThunderVideoQualityAdaptNone = 0,          //The quality of local video is constant
    ThunderVideoQualityAdaptUpBandwidth = 1,   //The quality of local video has been improved because of higher network bandwidth
    ThunderVideoQualityAdaptDownBandwidth = 2, //The quality of local video becomes worse because of lower network bandwidth
};

//编码形式
typedef NS_ENUM(NSInteger, ThunderVideoEncodedType)
{
  THUNDER_VIDEO_ENCODED_TYPE_UNKNOWN = 0, // 未知类型
  THUNDER_VIDEO_ENCODED_TYPE_HARD = 1, // 硬编码
  THUNDER_VIDEO_ENCODED_TYPE_SOFT = 2, // 软编码
};

typedef NS_ENUM(NSInteger, ThunderVideoDecodedType)
{
  THUNDER_VIDEO_DECODED_TYPE_UNKNOWN = 0, // Unknown decode type
  THUNDER_VIDEO_DECODED_TYPE_HARD = 1, // Hard decode
  THUNDER_VIDEO_DECODED_TYPE_SOFT = 2, // Soft decode
};

// ThunderRemoteAudioState定义
typedef NS_ENUM(NSInteger, ThunderRemoteAudioState)
{
  THUNDER_REMOTE_AUDIO_STATE_STOPPED = 0, // 远端音频流默认初始状态。 在 THUNDER_REMOTE_AUDIO_REASON_LOCAL_STOPPED(4) 或 THUNDER_REMOTE_AUDIO_REASON_REMOTE_STOPPED(6)  的情况下，会报告该状态
  THUNDER_REMOTE_AUDIO_STATE_STARTING = 1, // 本地用户已接收远端音频首包
  THUNDER_REMOTE_AUDIO_STATE_DECODING = 2, // 远端音频流正在解码，正常播放
  THUNDER_REMOTE_AUDIO_STATE_FROZEN = 3, // 远端音频流卡顿。在 THUNDER_REMOTE_AUDIO_REASON_NETWORK_CONGESTION(2) 的情况下，会报告该状态
  THUNDER_REMOTE_AUDIO_STATE_FAILED = 4, // 远端音频流播放失败。在THUNDER_REMOTE_AUDIO_REASON_INTERNAL(1)，THUNDER_REMOTE_AUDIO_REASON_PLAY_DEVICE_START_FAILED(8)，
                                         // THUNDER_REMOTE_AUDIO_REASON_FORMAT_NOT_SUPPORT(9)的情况下，会报告该状态
};
 
// ThunderRemoteAudioReason定义
typedef NS_ENUM(NSInteger, ThunderRemoteAudioReason)
{
  THUNDER_REMOTE_AUDIO_REASON_OK = 0, // 状态正常
  THUNDER_REMOTE_AUDIO_REASON_INTERNAL = 1, // 内部原因
  THUNDER_REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 2, // 网络阻塞
  THUNDER_REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 3, // 网络恢复正常
  THUNDER_REMOTE_AUDIO_REASON_LOCAL_STOPPED = 4, // 本地用户停止接收远端音频流或本地用户禁用音频模块
  THUNDER_REMOTE_AUDIO_REASON_LOCAL_STARTED = 5, // 本地用户恢复接收远端音频流或本地用户启用音频模块
  THUNDER_REMOTE_AUDIO_REASON_REMOTE_STOPPED = 6, // 远端用户停止发送音频流或远端用户禁用音频模块
  THUNDER_REMOTE_AUDIO_REASON_REMOTE_STARTED = 7, // 远端用户恢复发送音频流或远端用户启用音频模块
  THUNDER_REMOTE_AUDIO_REASON_PLAY_DEVICE_START_FAILED = 8, // 音频播放设备启动失败
  THUNDER_REMOTE_AUDIO_REASON_FORMAT_NOT_SUPPORT = 9, // 音频编码标准不支持导致解码失败
};

// 远端视频流状态
typedef NS_ENUM(NSInteger, ThunderRemoteVideoState)
{
  THUNDER_REMOTE_VIDEO_STATE_STOPPED = 0, // 远端视频默认初始状态。在 THUNDER_REMOTE_VIDEO_REASON_LOCAL_STOPPED(4) 或 THUNDER_REMOTE_VIDEO_REASON_REMOTE_STOPPED(6) 的情况下，会报告该状态
  THUNDER_REMOTE_VIDEO_STATE_STARTING = 1, // 本地用户已接收远端视频首包
  THUNDER_REMOTE_VIDEO_STATE_DECODING = 2, // 远端视频流正在解码
  THUNDER_REMOTE_VIDEO_STATE_RENDERING = 3, // 远端视频流正在渲染
  THUNDER_REMOTE_VIDEO_STATE_FROZEN = 4, // 远端视频流卡顿。在 THUNDER_REMOTE_VIDEO_REASON_NETWORK_CONGESTION(2) 的情况下，会报告该状态
  THUNDER_REMOTE_VIDEO_STATE_FAILED = 5, // Failed to play remote video. In the case of THUNDER_REMOTE_VIDEO_REASON_CODEC_UNKNOWN(8), the status will be reported
};

// 远端视频流状态改变原因
typedef NS_ENUM(NSInteger, ThunderRemoteVideoReason)
{
  THUNDER_REMOTE_VIDEO_REASON_OK = 0, // 状态正常
  THUNDER_REMOTE_VIDEO_REASON_INTERNAL = 1, // 内部原因
  THUNDER_REMOTE_VIDEO_REASON_NETWORK_CONGESTION = 2, // 网络阻塞
  THUNDER_REMOTE_VIDEO_REASON_NETWORK_RECOVERY = 3, // 网络恢复正常
  THUNDER_REMOTE_VIDEO_REASON_LOCAL_STOPPED = 4, // 本地用户停止接收远端视频流或本地用户禁用视频模块
  THUNDER_REMOTE_VIDEO_REASON_LOCAL_STARTED = 5, // 本地用户恢复接收远端视频流或本地用户启动视频模块
  THUNDER_REMOTE_VIDEO_REASON_REMOTE_STOPPED = 6, // 远端用户停止发送视频流或远端用户禁用视频模块
  THUNDER_REMOTE_VIDEO_REASON_REMOTE_STARTED = 7, // 远端用户恢复发送视频流或远端用户启用视频模块
  THUNDER_REMOTE_VIDEO_REASON_CODEC_UNKNOWN = 8, // Unknown video codec
};


// 本地视频流状态定义
typedef NS_ENUM(NSInteger, ThunderLocalVideoStreamStatus)
{
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_STOPPED = 0, // 本地视频默认初始状态
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_CAPTURING = 1, // 本地视频采集设备启动成功
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_PREVIEWING = 2, // 本地视频预览成功
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_ENCODING = 3, // 本地视频首帧编码成功
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_SENDING = 4, // 本地视频首帧发送成功
  THUNDER_LOCAL_VIDEO_STREAM_STATUS_FAILED = 5, // 本地视频启动失败
};

// 本地视频流状态状态发生变化原因
typedef NS_ENUM(NSInteger, ThunderLocalVideoStreamErrorReason)
{
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_OK = 0, // 本地视频状态正常
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1, // 出错原因不明确
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_DEVICE_DENIED = 2, // 没有权限启动本地视频采集设备
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_DEVICE_RESTRICTED = 3, // 本地视频采集设备正在使用中
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4, // 本地视频采集失败，建议检查采集设备是否正常工作
  THUNDER_LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5, // 本地视频编码失败
};

// 本地音频状态回调
typedef NS_ENUM(NSInteger, ThunderLocalAudioStreamStatus)
{
  THUNDER_LOCAL_AUDIO_STREAM_STATUS_STOPPED = 0, // 本地音频默认初始状态
  THUNDER_LOCAL_AUDIO_STREAM_STATUS_CAPTURING = 1, // 本地音频录制设备启动成功
  THUNDER_LOCAL_AUDIO_STREAM_STATUS_ENCODING = 2, // 本地音频首帧编码成功
  THUNDER_LOCAL_AUDIO_STREAM_STATUS_SENDING = 3, // 本地音频首帧发送成功
  THUNDER_LOCAL_AUDIO_STREAM_STATUS_FAILED = 4, // 本地音频启动失败
};

// 本地音频错误原因
typedef NS_ENUM(NSInteger, ThunderLocalAudioStreamErrorReason)
{
  THUNDER_LOCAL_AUDIO_STREAM_ERROR_OK = 0, // 状态正常
  THUNDER_LOCAL_AUDIO_STREAM_ERROR_UNKNOWN = 1, // 本地音频错误原因未知
  THUNDER_LOCAL_AUDIO_STREAM_ERROR_CAPTURE_FAILURE = 2, // 本地音频采集失败
  THUNDER_LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 3, // 本地音频编码失败
};

/**
 * @brief 当前语音路由的设备
 */
typedef NS_ENUM(NSInteger, ThunderAudioOutputRouting)
{
    THUNDER_AUDIO_OUTPUT_ROUTING_DEFAULT = -1, // 使用默认的语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_HEADSET = 0, // 使用耳机为语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_EARPIECE = 1, // 使用听筒为语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_HEADSETNOMIC = 2, // 使用不带麦的耳机为语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_SPEAKERPHONE = 3, // 使用手机的扬声器为语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_LOUDSPEAKER = 4, // 使用外接的扬声器为语音路由
    THUNDER_AUDIO_OUTPUT_ROUTING_HEADSETBLUETOOTH = 5, // 使用蓝牙耳机为语音路由
};

/**
 * @brief 视频流类型
 */
typedef NS_ENUM(NSInteger, ThunderVideoStreamType)
{
  THUNDER_VIDEO_STREAM_TYPE_HIGH = 0, // 高码率、高分辨率视频，即大流
  THUNDER_VIDEO_STREAM_TYPE_LOW = 1, // 低码率、低分辨率视频，即小流
};

/**
 * @brief 图片水印缩放类型
 */
typedef NS_ENUM(NSInteger, TranscodingImageScaleType)
{
  TRANSCODING_IMAGESCALE_RATIO_TYPE = 0, // 等比例缩放裁剪
  TRANSCODING_IMAGESCALE_STRETCH_TYPE = 1, // 拉伸铺满整块画布
};

/**
 * @brief 水印个数限制
 */
typedef NS_ENUM(NSInteger, TranscodingWatermarkCountType)
{
  TRANSCODING_WATERMARK_TEXT_MAX = 3, // Number of text watermark
  TRANSCODING_WATERMARK_IMAGE_MAX = 4, // Number of image watermark
};

/**
 * @brief Authentication media stream type
 */
typedef NS_ENUM(NSInteger, LiveBizAuthStreamType)
{
  LIVE_BIZ_AUTH_STREAM_VIDEO = 1, // Video stream
  LIVE_BIZ_AUTH_STREAM_AUDIO = 2, // Audio stream
};

#pragma mark struct define
struct ThunderReverbExParamOc
{
  double mRoomSize; // 0~100
  double mPreDelay; // 0~200
  double mReverberance; // 0~100
  double mHfDamping; // 0~100
  double mToneLow; // 0~100
  double mToneHigh; // 0~100
  double mWetGain; // -20~10
  double mDryGain; // -20~10
  double mStereoWidth; // 0~100
};
typedef struct CG_BOXABLE ThunderReverbExParamOc ThunderReverbExParamOc;

struct ThunderCprParamOc
{
  int threshold;
  int makeupGain;
  int ratio;
  int knee;
  int releaseTime;
  int attackTime;
};
typedef struct CG_BOXABLE ThunderCprParamOc ThunderCprParamOc;

struct ThunderLimiterParamOc
{
  float fCeiling;          // (-30 ~ 0)
  float fThreshold;        // (-10 ~ 0)
  float fPreGain;             // (0~30)
  float fRelease;             // (0~1000)
  float fAttack;             // (0~1000)
  float fLookahead;         // (0~8)
  float fLookaheadRatio;     // (0.5~2)
  float fRMS;                 // (0~100)
  float fStLink;             // (0~1)
};
typedef struct CG_BOXABLE ThunderLimiterParamOc ThunderLimiterParamOc;

typedef float ThunderEqGainsOc[11];

__attribute__((visibility("default"))) @interface ThunderVideoEncodeParam : NSObject
@property(assign, nonatomic) NSUInteger width;
@property(assign, nonatomic) NSUInteger height;
@property(assign, nonatomic) NSUInteger frameRate;
@property(assign, nonatomic) NSUInteger codeRate;
@property (assign, nonatomic) ThunderVideoEncodedType encodedType; // hardware or software encoding
@property (assign, nonatomic) ThunderVideoCodecType codecType; // H264 or H265
@end

__attribute__((visibility("default"))) @interface ThunderRtcAudioVolumeInfo : NSObject
@property(copy, nonatomic) NSString* _Nonnull uid;
@property(assign, nonatomic) NSUInteger volume;
@property(assign, nonatomic) NSUInteger pts;
@end

__attribute__((visibility("default"))) @interface ThunderRtcRoomStats : NSObject
@end

__attribute__((visibility("default"))) @interface ThunderRtcRemoteVideoStats : NSObject
@property (assign, nonatomic) NSUInteger delay; // Delay from publishing remote video stream to playback
@property (assign, nonatomic) NSUInteger width; // Width of remote video stream
@property (assign, nonatomic) NSUInteger height; // Height of remote video stream
@property (assign, nonatomic) NSUInteger receivedBitrate; // Receiving bit rate (unit: Kbps)
@property (assign, nonatomic) NSUInteger decoderOutputFrameRate; // Output frame rate of remote video decoder (unit: fps)
@property (assign, nonatomic) NSUInteger rendererOutputFrameRate; // Output frame rate of remote video renderer (unit: fps)
@property (assign, nonatomic) NSUInteger packetLossRate; // Packet loss rate (%) of remote video after network confrontation
@property (assign, nonatomic) NSUInteger rxStreamType; // Types of video stream, including large stream and small stream
@property (assign, nonatomic) NSUInteger totalFrozenTime; // The accumulated time (ms) from the time when a remote user begins to punish to the time of video freezing
@property (assign, nonatomic) NSUInteger frozenRate; // The percentage (%) of the accumulated time (from the time when a remote user begins to publish to the time of video freezing) accounting for total effective time of videos
@property (assign, nonatomic) ThunderVideoCodecType codecType; // Codec type, H264/H265/VP8
@property (assign, nonatomic) ThunderVideoDecodedType decodedType; // Decoding type, hardware or software decoding
@end

__attribute__((visibility("default"))) @interface ThunderRtcRemoteAudioStats : NSObject
@property (assign, nonatomic) NSUInteger quality; // Quality of audio streams sent by remote users. 0: Unknown; 1: Excellent; 2: Good; 3: Poor, flawed but does not affect communication; 4: Bad, communication can be made but not smoothly; 5: Very Bad, communication can barely be made; 6: Disconnected, communication can not be made at all
@property (assign, nonatomic) NSUInteger networkTransportDelay; // Network delay from an audio sending end to an audio receiving end
@property (assign, nonatomic) NSUInteger jitterBufferDelay; // Delay from a receiving end to network jitter buffer
@property (assign, nonatomic) NSUInteger totalDelay; // 从主播采集音频到观众播放的总延迟
@property (assign, nonatomic) NSUInteger frameLossRate; // Frame loss rate (%) of remote audio streams
@property (assign, nonatomic) NSUInteger numChannels; // Quantity of tracks
@property (assign, nonatomic) NSUInteger receivedSampleRate; // Sampling rate (Hz) of remote audios
@property (assign, nonatomic) NSUInteger receivedBitrate; // Average bit rate of remote audios within a statistical period
@property (assign, nonatomic) NSUInteger totalFrozenTime; // The accumulated time (ms) from the time when a remote user joins a channel to the time of audio freezing
@property (assign, nonatomic) NSUInteger frozenRate; // The percentage (%) of the accumulated time (from the time when a remote user joins a channel to the time of audio freezing) accounting for total effective time of audios
@end

__attribute__((visibility("default"))) @interface ThunderVideoCanvas : NSObject
@property(strong, nonatomic) UIView* _Nullable view;
@property(assign, nonatomic) ThunderVideoRenderMode renderMode;
@property(copy, nonatomic) NSString* _Nullable uid;
// Set user’s display position during multi-person microphone connection
@property(assign, nonatomic)int seatIndex;
@end

/* 多人连麦设置布局
* 如下，ThunderMultiVideoViewCoordinate示意，外框是整体视频布局， Video是单个视频布局区域
*
* |---------------------------------------------|
* | (0,0)                                       |
* |                                             |
* |                             (x,y)         |
* |                               |---width---| |
* |                               |           | |
* |                        height |           | |
* |                               | Video     | |
* |                               |           | |
* |                               |-----------| |
* |---------------------------------------------|
*/
__attribute__((visibility("default"))) @interface ThunderMultiVideoViewCoordinate: NSObject
// Multi-person microphone connection setting layout
@property(assign, nonatomic)int x; // X coordinate at upper left corner of the single video/view layout
@property(assign, nonatomic)int y; // Y coordinate at upper left corner of the single video/view layout
@property(assign, nonatomic)int width; // Width of the single video/view layout
@property(assign, nonatomic)int height; // Height of the single video/view layout
@property(assign, nonatomic)int index; // Seat No. of the single video/view layout, starting from 0
@end

/*
*
* 多个多人view示意图
*
* |---------------------------------|
* |           viewId : 0            |
* |                                 |
* |            view : A             |
* |                                 |
* |---------------------------------|
* |---------------------------------|
* |           viewId : 1            |
* |                                 |
* |            view : B             |
* |                                 |
* |---------------------------------|
 说明：
 多人个多人view布局示意图；有如下业务场景用法举例说明：
 如果更新A的内部布局参数，需要赋值viewId：0 和 view:A，然后赋值其他布局参数即可；
 如果更换B的布局对象为C，需要赋值viewId：1 和 view：C，然后赋值其他布局参数，并重新设置视频视图座位；
 如果新增多人view D，需要赋值viewId：2 （依次） 和 view:D，然后赋值其他布局参数即可,并设置视频视图座位；
 如果销毁A以及对应布局，需要赋值viewId：0 和 view：nil；
 note：不允许出现多个viewId对应同一个view的情况
*/

__attribute__((visibility("default"))) @interface ThunderMultiVideoViewParam: NSObject
@property (assign, nonatomic) int viewId; // view的索引,从0开始（新增）
@property (strong, nonatomic) UIView* _Nullable view; // viewId对应的view（新增）
@property(strong, nonatomic)NSArray<ThunderMultiVideoViewCoordinate*>* _Nonnull videoPositions; // Video/view layout parameters
@property(strong, nonatomic)ThunderMultiVideoViewCoordinate* _Nullable bgCoordinate; // Video/view background layout parameters
@property(copy, nonatomic)NSString* _Nullable bgImageName; // Video/view background picture
@end


__attribute__((visibility("default"))) @interface ThunderVideoEncoderConfiguration : NSObject
// Publishing profile of videos is added here
// References: resolution, frame rate, minimum frame rate, bit rate, minimum bit rate, direction mode of video coding, and video coding degradation preference in the case of limited bandwidth
@property(assign, nonatomic) ThunderPublishPlayType playType;
@property(assign, nonatomic) int publishMode;
@end

__attribute__((visibility("default"))) @interface ThunderRtcLocalVideoStats : NSObject
@property (assign, nonatomic) NSUInteger sendBitrate;  // Actual sending bit rate (Kbps)
@property (assign, nonatomic) NSUInteger sendFrameRate; // Actual sending frame rate (unit: fps)
@property (assign, nonatomic) NSUInteger encoderOutputFrameRate;// Output frame rate of local coder (unit: fps)
@property (assign, nonatomic) NSUInteger renderOutputFrameRate;// Output frame rate of local renderer (unit: fps)
@property (assign, nonatomic) NSUInteger targetBitrate;// Target encoding bit rate of current encoder (unit: Kbps)
@property (assign, nonatomic) NSUInteger targetFrameRate;// Target encoding frame rate of current coder (unit: fps)
// Quality adaptability of local videos since last statistics (based on target frame rate and target bit rate)
@property (assign, nonatomic) ThunderVideoQualityAdaptIndication qualityAdaptIndication;
@property (assign, nonatomic) NSUInteger encodedBitrate;// Bit rate of video encoding (Kbps)
@property (assign, nonatomic) NSUInteger encodedFrameWidth;// Width of video encoding (px)
@property (assign, nonatomic) NSUInteger encodedFrameHeight;// Height of video encoding (px)
@property (assign, nonatomic) NSUInteger encodedFrameCount;// Number of frames sent by video, an accumulated value
@property (assign, nonatomic) ThunderVideoEncodedType encodedType;// 编码形式
@property (assign, nonatomic) ThunderVideoCodecType codecType;// Encoding type of videos
@property (assign, nonatomic) NSUInteger configBitRate;  //Configured bit rate (kbps)
@property (assign, nonatomic) NSUInteger configFrameRate;// Configured frame rate
@property (assign, nonatomic) NSUInteger configWidth;// Video height configured
@property (assign, nonatomic) NSUInteger configHeight;// Video width configured
@end

/**
@brief 通话中本地设备发送音频流的统计信息
*/
__attribute__((visibility("default"))) @interface ThunderRtcLocalAudioStats : NSObject
@property (assign, nonatomic) NSUInteger encodedBitrate; // 编码码率 kbps
@property (assign, nonatomic) NSUInteger numChannels;// Number of channels
@property (assign, nonatomic) NSUInteger sendSampleRate;// Sampling rate HZ
@property (assign, nonatomic) NSUInteger sendBitrate;// Sending bit rate (kbps)
@property (assign, nonatomic) NSUInteger enableVad;// 发送的音频流采用的VAD，0：不开启；1：开启
@end

/**
@brief CPU/内存使用情况
*/
__attribute__((visibility("default"))) @interface ThunderRtcLocalDeviceStats : NSObject
@property (assign, nonatomic) CGFloat cpuTotalUsage; // 当前系统的 CPU 使用率(%)
@property (assign, nonatomic) CGFloat cpuAppUsage; // 当前 App 的 CPU 使用率 (%)
@property (assign, nonatomic) CGFloat memoryAppUsage; // 当前 App 的内存占比 (%)
@property (assign, nonatomic) CGFloat memoryTotalUsage; // 当前系统的内存占比 (%)
@end

/**
 @brief is used to set profiles of watermarks and background images for live videos.
 */
__attribute__((visibility("default"))) @interface ThunderImage : NSObject

/**
 @brief URL of the image on the live video
 @remark
 URLs are defined differently in local live streaming and bypass stream publishing. In local live streaming, the URL refers to the local absolute path of the watermark image on the local live video; in bypass stream publishing, the URL refers to the address of the watermark image on the video of bypass stream publishing; the source file format of the watermark image must be PNG.
 */
@property(strong, nonatomic) NSURL* _Nullable url;

/**
 @brief The location and size of picutures in video frame, and the type is CGRect
 @remark
If the size of picture in PNG format is inconsistent with settings in this method, SDK will make it coincident by clipping
 */
@property(assign, nonatomic) CGRect rect;

@end

/**
 @brief Traffic notification attribute
 */
__attribute__((visibility("default"))) @interface RoomStats : NSObject
@property(nonatomic, assign) uint32_t totalDuration; // 加入频道后累计通话时长,单位为秒
@property(nonatomic, assign) uint32_t txBitrate; // Chain sending bit rate (unit: bps)
@property(nonatomic, assign) uint32_t rxBitrate; // Chain receiving bit rate (unit: bps)
@property(nonatomic, assign) uint32_t txBytes; // 加入频道后累计发送字节数
@property(nonatomic, assign) uint32_t rxBytes; // 加入频道后累计接收字节数
@property(nonatomic, assign) uint32_t txAudioBytes; // 加入频道后累计发送音频字节数
@property(nonatomic, assign) uint32_t rxAudioBytes; // 加入频道后累计接收音频字节数
@property(nonatomic, assign) uint32_t txVideoBytes; // 加入频道后累计发送视频字节数
@property(nonatomic, assign) uint32_t rxVideoBytes; // 加入频道后累计接收视频字节数
@property(nonatomic, assign) uint32_t txAudioBitrate; // Audio packet sending bit rate (unit: bps)
@property(nonatomic, assign) uint32_t rxAudioBitrate; // Audio packet receiving bit rate (unit: bps)
@property(nonatomic, assign) uint32_t txVideoBitrate; // Video packet sending bit rate (unit: bps)
@property(nonatomic, assign) uint32_t rxVideoBitrate; // Video packet receiving bit rate (unit: bps)
@property(nonatomic, assign) uint32_t lastmileDelay; // 本地客户端到边缘服务器的延迟（毫秒)，音频和视频延时中的较大值
@property(nonatomic, assign) uint32_t txPacketLossRate; // 抗丢包技术前，本地客户端到边缘服务器的上行丢包率，单位为 %
@property(nonatomic, assign) uint32_t rxPacketLossRate; // 抗丢包技术前，本地客户端到边缘服务器的下行丢包率，单位为 %
@end

__attribute__((visibility("default"))) @interface ThunderMixVideoInfo : NSObject
@property(copy, nonatomic) NSString* _Nonnull uid; // User ID
@property(assign, nonatomic) CGSize size; // Original width and height of this user's video
@property(assign, nonatomic) CGRect crop; // The region used to crop the original video in video mixing
@property(assign, nonatomic) CGRect layout; // Location of this user's video in video mixing canvas
@property(assign, nonatomic) int zOrder; // Layer number of this user's video frame in video mixing. The value range is the integer in [0, 100],
                                         // and the minimum value is 0, indicating that the image in this region is at the lowest level
@property(assign, nonatomic) float alpha; // Transparency of this user's video frame in video mixing. The value range is [0.0, 1.0].
                                          // 0.0 indicates that the image in this region is completely transparent, while 1.0 indicates completely opaque.
@end

__attribute__((visibility("default")))@interface ThunderMixAudioInfo : NSObject
@property(copy, nonatomic) NSString* _Nonnull uid;
@property(assign, nonatomic) int volume; // [0,100]
@end



#pragma mark protocol
@class ThunderEngine;

/**
 @protocol
 @brief Log agent
 */
__attribute__((visibility("default"))) @protocol ThunderRtcLogDelegate <NSObject>

@required
/**
 @brief Callback of processing log
 @param [OUT] level Level @see ThunderLogLevel
 @param [OUT] msg Log
 */
- (void)onThunderRtcLogWithLevel:(ThunderRtcLogLevel)level message:(nonnull NSString*)msg;

@end

__attribute__((visibility("default"))) @protocol ThunderEventDelegate <NSObject>

/**
 @brief Callback on joining room
 @param [OUT] room Room name
 @param [OUT] uid User ID
 @param [OUT] elapsed Indicates the time spent on joining room, that is, time elapsed (in millisecond) from calling joinRoom to event occurrence.
 @remark After joinRoom is called, receiving such a notification indicates that connection with the server is normal, and the interface that can only be called for "joining room successfully" may be called.
 */
- (void)thunderEngine:(ThunderEngine* _Nonnull)engine
    onJoinRoomSuccess:(nonnull NSString*)room
              withUid:(nonnull NSString*)uid
              elapsed:(NSInteger)elapsed;

/**
  @brief Notification of leaving room
  @remark When leaveRoom is called, this notification will be received upon normal leaving of the room.
*/
- (void)thunderEngine: (ThunderEngine* _Nonnull)engine onLeaveRoomWithStats:(ThunderRtcRoomStats* _Nonnull)stats;

/**
 @brief SDK Authentication result notification; For details about authentication, see "User Authentication Instructions" on the official website.
 @param [OUT] sdkAuthResult For authentication results, see ThunderRtcSdkAuthResult.
 @remark After joinRoom is called, if the uplink and downlink media data is available, the authentication notification for the user will be received.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine sdkAuthResult:(ThunderRtcSdkAuthResult)sdkAuthResult;

/**
 @brief Notification on service authentication results
 @param [OUT] bPublish Publishing (speaking as an anchor) or not
 @param [OUT] bizAuthResult Authentication result; 0 indicates pass; other values indicate fail (defined by the developer; SDK is only for pass-through)
 @remark The notification is received if service authentication is mandatory for services and there is media stream in the uplink.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine bPublish:(BOOL)bPublish bizAuthResult:(NSInteger)bizAuthResult;

/**
 @brief Notification on service authentication results
 @param [OUT] bPublish Publishing (speaking as an anchor) or not
 @param [OUT] bizAuthStreamType type Type of the authenticated stream, refer to LiveBizAuthStreamType
 @param [OUT] bizAuthResult Authentication result; 0 indicates pass; other values indicate fail (defined by the developer; SDK is only for pass-through)
 @remark The notification is received if service authentication is mandatory for services and there is media stream in the uplink.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine bPublish:(BOOL)bPublish bizAuthStreamType:(LiveBizAuthStreamType)bizAuthStreamType bizAuthResult:(NSInteger)bizAuthResult;

#pragma mark play
/**
 @brief Callback on voice volume prompt
 @param [OUT] speakers User ID-user volume (not implemented; Volume = totalVolume)
 @param [OUT] totalVolume (after audio mixing) total volume [0-100]
 @remark After setAudioVolumeIndication is set, the notification will be received once anyone speaks in the room.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
onPlayVolumeIndication:(NSArray<ThunderRtcAudioVolumeInfo *> * _Nonnull)speakers
          totalVolume:(NSInteger)totalVolume;

/**
 @brief Callback on capture volume prompt
 @param [OUT] totalVolume Total volume of capture (including microphone capture and file playback) 
 @param [OUT] cpt Capture timestamp
 @param [OUT] micVolume Capture volume of microphone
 @
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
onCaptureVolumeIndication:(NSInteger)totalVolume
                  cpt:(NSUInteger)cpt
            micVolume:(NSInteger)micVolume;

/**
 @brief Callback on audio playback data
 @param [OUT] uid User ID
 @param [OUT] duration Duration
 @param [OUT] cpt Capture timestamp
 @param [OUT] pts Play timestamp
 @param [OUT] data Data before decoding
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
      onAudioPlayData:(nonnull NSString*)uid
             duration:(NSUInteger)duration
                  cpt:(NSUInteger)cpt
                  pts:(NSUInteger)pts
                 data:(nullable NSData*)data;

/**
 @brief Callback on audio play spectrum data
 @param [OUT] data Spectrum data; type: UInt8; value range [0-100]
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onAudioPlaySpectrumData:(nullable NSData*)data;

/**
 @brief Callback on audio capture data
 @param [OUT] data Acquire PCM data
 @param [OUT] sampleRate Data sampling rate
 @param [OUT] channel Number of data channels
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
onAudioCapturePcmData:(nullable NSData*)data
           sampleRate:(NSUInteger)sampleRate
              channel:(NSUInteger)channel __attribute__((deprecated("[该接口已废弃]使用IAudioFrameObserver")));

/**
 @brief Callback on rendered audio data
 @param [OUT] data Render PCM data
 @param [OUT] sampleRate Data sampling rate
 @param [OUT] channel Number of data channels
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
  onAudioRenderPcmData:(nullable NSData*)data
              duration:(NSUInteger)duration
            sampleRate:(NSUInteger)sampleRate
               channel:(NSUInteger)channel __attribute__((deprecated("[该接口已废弃]使用IAudioFrameObserver")));

/**
 @brief Callback on service-customized broadcast messages
 @param [OUT] msgData Pass-through message
 @param [OUT] uid ID of the user who sends the message
 @remark If the anchor sends data through sendUserAppMsgData, the callback is received by audiences who enter the channel.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
  onRecvUserAppMsgData:(nonnull NSData*)msgData
                   uid:(nonnull NSString*)uid;

/**
 @brief Callback on failure in sending service-customized broadcast messages
 @param [OUT] status Failure status (1-Frequency is too high 2-Data sent is too large 3-Publishing is not started successfully)
 @remark If the anchor sends data through sendUserAppMsgData, the notification is received by audiences who enter the channel. As stipulated currently, the pass-through frequency is 2 times/s and the size of data sent is not greater than 200 Bytes.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onSendAppMsgDataFailedStatus:(NSUInteger) status;

/**
 @brief Callback on stopping/starting remote user's audio stream
 @param [OUT] stopped Stop/start; YES = Stop NO = Start
 @param [OUT] uid ID of the remote user
 @remark After joinRoom is called, the callback will be received when statuses of existing and subsequent audio streams in the room change.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onRemoteAudioStopped:(BOOL)stopped byUid:(nonnull NSString*)uid;

/**
 @brief Callback on starting/stopping remote user's video stream
 @param [OUT] stopped Whether the stream has been disconnected (YES: Disconnected; NO: Connected)
 @param [OUT] uid ID of the corresponding user
 @remark After joinRoom is called, the callback will be received when statuses of existing and subsequent video streams in the room change.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onRemoteVideoStopped:(BOOL)stopped byUid:(nonnull NSString*)uid;

/**
 @brief Callback on displayed first remote video frame
 @param [OUT] uid ID of the corresponding user
 @param [OUT] size Video size (width and height)
 @param [OUT] elapsed Time elapsed (in millisecond) from calling joinRoom to event occurrence.
 @remark After setRemoteVideoCanvas is called, the callback will be received when video streams are received and displayed in the window.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine
    onRemoteVideoPlay:(nonnull NSString *)uid
                 size:(CGSize)size
              elapsed:(NSInteger)elapsed;

/**
 @brief Callback on changes in local or remote video size and rotation information
 @param [OUT] uid ID of the corresponding user
 @param [OUT] size Video size (width and height)
 @param [OUT] rotation Rotation information (0–360)
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine
onVideoSizeChangedOfUid:(nonnull NSString*)uid
                 size:(CGSize)size
                 rotation:(NSInteger)rotation;

/**
 @brief Callback on camera capture status
 @param [OUT] status Camera capture status
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onVideoCaptureStatus:(ThunderVideoCaptureStatus)status;

/**
 @brief Callback on network connection status between the SDK and the server
 @param [OUT] status For connection status, see ThunderConnectionStatus.
 @remark After joinRoom is called, the callback will be received when the network connection status between the SDK and the server changes.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onConnectionStatus:(ThunderConnectionStatus)status;

/**
 @brief Notification of upstream/downstream traffic (periodic notification sent once every 2 seconds)
 @param [OUT] stats Statistics of upstream/downstream traffic
 @remark This callback is received when the user enters a channel.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onRoomStats:(nonnull RoomStats*)stats;

/**
 @brief Callback on the first frame of sent local audio
 @param [OUT] elapsed Time elapsed (in milliseconds) from calling joinRoom by a local user to triggering the callback
 @remark The callback is received when there is uplink audio stream for the user.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onFirstLocalAudioFrameSent:(NSInteger)elapsed;

/**
 @brief Callback on the first frame of sent local video
 @param [OUT] elapsed Time elapsed (in milliseconds) from calling joinRoom by a local user to triggering the callback
 @remark The callback is received when there is uplink video stream for the user.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onFirstLocalVideoFrameSent:(NSInteger)elapsed;

/**
 @brief This callback will be triggered when calling addPublishOriginStreamUrl to set publishing source stream to CDN or when calling addPublishTranscodingStreamUrl to set publishing mixed video stream to CDN, after publishing or setting up transcoding task. 
 To notify whether CDN stream publishing succeeds. If it fails, errorCode will indicate the specific reason. 
 @param [OUT] url  Target URL of stream publishing
 @param [OUT] errorCode  Error code of stream publishing
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine
  onPublishStreamToCDNStatusWithUrl:(NSString *_Nonnull)url
  errorCode:(ThunderPublishCDNErrorCode)errorCode;

/**
 @brief Callback on network type change
 @param [OUT] type Current network status
 @remark After initialization, the callback will be received when the network type changes.
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onNetworkTypeChanged:(NSInteger)type;

/*!
@brief Report local video statistics
@param stats For local video statistics, see ThunderRtcLocalVideoStats.
@remark 如果你此前调用 enableLocalDualStreamMode 方法开启双流模式，则本回调描述本地设备发送的视频大流的统计信息
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onLocalVideoStats:(ThunderRtcLocalVideoStats * _Nonnull)stats;

/*!
@brief Report local audio statistics
@param stats For local audio statistics, see ThunderRtcLocalAudioStats
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onLocalAudioStats:(ThunderRtcLocalAudioStats * _Nonnull)stats;

/*!
@brief 远端音频流状态信息回调
@param uid 远端用户 uid
@param state 远端用户音频流状态，参见ThunderRemoteAudioState
@param reason 远端用户处于当前状态原因，参见ThunderRemoteAudioReason
 @param elapsed 从加入频道到发生该状态耗时
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onRemoteAudioStateChangedOfUid:(nonnull NSString*)uid
                state:(ThunderRemoteAudioState)state
               reason:(ThunderRemoteAudioReason)reason elapsed:(NSInteger)elapsed;

/*!
@brief 已播放远端音频首帧回调
@param uid 远端用户 uid
 @param elapsed 从加入频道到发生该状态耗时
*/
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onRemoteAudioPlay:(nonnull NSString *)uid elapsed:(NSInteger)elapsed;

/*!
@brief 本地音频流状态信息
@param status 本地音频流状态，参见ThunderLocalAudioStreamStatus
@param errorReason 错误码，当音频状态为THUNDER_LOCAL_AUDIO_STREAM_STATUS_FAILED时，通过errorReason错误码检索具体原因
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onLocalAudioStatusChanged:(ThunderLocalAudioStreamStatus)status
                                                                     errorReason:(ThunderLocalAudioStreamErrorReason)errorReason;

/*!
@brief CPU/内存/GPU使用信息
@param stats CPU/内存/GPU使用信息，参见ThunderRtcLocalDeviceStats
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onDeviceStats:(ThunderRtcLocalDeviceStats * _Nonnull)stats;

/**
 @brief Callback on capture status of audio device
 @param [OUT] status Capture status
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onAudioCaptureStatus:(NSInteger)status;

/**
 * @brief 语音路由已变更回调
 * @param [OUT] routing 当前语音路由的设备
 * @remark 该回调通知是在语音路由发生切换时才会回调，非实时回调
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onAudioRouteChanged:(ThunderAudioOutputRouting)routing;

/**
 * @brief 啸叫检测结果通知回调
 * @param [OUT] bHowling true:检测到啸叫；false:没有检测到啸叫
 * @remark (1) enableHowlingDetector(true)并且在打开麦克风的状态下才会收到该回调
 *         (2) 回调不是周期的，只有状态变化时，才会收到该回调
 *         (3) enableHowlingDetector(true)的状态下，关闭麦克风再打开麦克风会收到一次该回调
 *         (4) 麦克风打开的状态状态下，从enableHowlingDetector(false)到enableHowlingDetector(true)会收到一次该回调
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onHowlingDetectResult:(BOOL)bHowling;

/**
 * @brief 漏回声检测结果通知回调
 * @param [OUT] bEcho true:检测到漏回声；false:没有检测到漏回声
 * @remark (1) enableEchoDetector(true)并且在打开麦克风的状态下才会收到该回调
 *         (2) 回调不是周期的，只有状态变化时，才会收到该回调
 *         (3) enableEchoDetector(true)的状态下，关闭麦克风再打开麦克风会收到一次该回调
 *         (4) 麦克风打开的状态状态下，从enableEchoDetector(false)到enableEchoDetector(true)会收到一次该回调
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onEchoDetectResult:(BOOL)bEcho;

/**
 * @brief 设备检测采集音量通知回调
 * @param volume 音量值： 【0~100】
 * @remark (1) startInputDeviceTest()才会收到该回调
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onAudioInputDeviceTestVolume:(int)volume;

/**
 * @brief 设备检测播放音量通知回调
 * @param volume 音量值： 【0~100】
 * @remark (1) startOutputDeviceTest:(NSString* _Nullable)filePath才会收到该回调
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onAudioOutputDeviceTestVolume:(int)volume;

/**
 * @brief 摄像头对焦区域已改变回调
 * @param [OUT] focusArea 返回对焦的区域，值的范围为0到1之间
 * @remark 调用setCameraFocusPosition改变对焦位置后触发
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onCameraFocusAreaChanged:(CGRect)focusArea;

/**
 * @brief 摄像头曝光区域已改变回调
 * @param [OUT] exposureArea 返回曝光的区域，值的范围为0到1之间
 * @remark 调用setCameraExposurePosition改变曝光位置后触发
 */
- (void)thunderEngine:(ThunderEngine *_Nonnull)engine onCameraExposureAreaChanged:(CGRect)exposureArea;

/**
 @brief Notification of server network interruption. After calling joinRoom, regardless of whether joining is successful or not, SDK will trigger this callback as long as server cannot be connected in 10 seconds
 */
- (void)thunderEngineConnectionLost:(ThunderEngine *_Nonnull)engine;

/**
 @brief Callback on near expiration of authentication service
 @param [OUT] token Token for near expiration of service
 @remark  The callback is received if the user's token is close to expiration.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onTokenWillExpire:(nonnull NSString*)token;

/**
 @brief Callback on expired authentication
 */
- (void)thunderEngineTokenRequest:(ThunderEngine * _Nonnull)engine;

/**
 @brief Callback on user banned
 @param [OUT] status Banning status (YES-Ban; NO-Unban)
 @remark The callback is received if the user banning status changes.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onUserBanned:(BOOL)status;

/**
 @brief Callback on remote user joining room
 @param [OUT] uid ID of the remote user
 @param [OUT] elapsed Time consumed for joining room
 @remark The callback is valid only in audio-only mode and is returned when other users enter the room where the local user has entered.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine onUserJoined:(nonnull NSString*)uid elapsed:(NSInteger)elapsed;

/**
 @brief Callback on remote user leaving current room
 @param [OUT] uid ID of the offline user
 @param [OUT] reason Reason for going offline
 @remark The callback is valid only in audio-only mode and is returned when other users leave the room where the local user has entered.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
        onUserOffline:(nonnull NSString*)uid
        reason:(ThunderLiveRtcUserOfflineReason)reason;

/*!
 @brief Callback on network uplink/downlink quality report
 @param [OUT] uid The callback reports the network quality of the user with the ID. If uid is 0, the network quality of the local user is returned.
 @param [OUT] txQuality For the uplink network quality of the user, see ThunderLiveRtcNetworkQuality.
 @param [OUT] rxQuality For the downlink network quality of the user, see ThunderLiveRtcNetworkQuality.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
     onNetworkQuality:(nonnull NSString*)uid
     txQuality:(ThunderLiveRtcNetworkQuality)txQuality
     rxQuality:(ThunderLiveRtcNetworkQuality)rxQuality;

/*!
 @brief Callback on remote video stream information during the call
 @param [OUT] uid ID of the remote user/anchor
 @param [OUT] stats For stream information, see ThunderRtcRemoteVideoStats.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
        onRemoteVideoStatsOfUid:(nonnull NSString*)uid
        stats:(ThunderRtcRemoteVideoStats* _Nonnull)stats;

/*!
 @brief 远端视频流状态变化回调，本地用户订阅的每一路远端用户视频状态发生改变时，SDK 会触发回调向你报告远端音频流当前状态和状态改变的原因
 @param [OUT] uid 远端用户/主播id
 @param [OUT] state 视频流状态，参见ThunderRemoteVideoState
 @param [OUT] reason 流状态改变的原因，参见ThunderRemoteVideoReason
 @param [OUT] elapsed 从用户joinRoom到收到此通知的时间间隔
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
        onRemoteVideoStateChangedOfUid:(nonnull NSString*)uid
        state:(ThunderRemoteVideoState)state
        reason:(ThunderRemoteVideoReason)reason
        elapsed:(NSInteger)elapsed;

/*!
@brief 本地视频流状态发生变化回调
@param [OUT] status 本地视频流状态，参见ThunderLocalVideoStreamStatus
@param [OUT] error 本地视频流状态发生变化的原因，参见ThunderLocalVideoStreamErrorReason
*/
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
        onLocalVideoStatusChanged:(ThunderLocalVideoStreamStatus)status
        error:(ThunderLocalVideoStreamErrorReason)error;

/*!
 @brief Callback on remote audio stream information during the call
 @param [OUT] uid ID of the remote user/anchor
 @param [OUT] stats For stream information, see ThunderRtcRemoteAudioStats.
 */
- (void)thunderEngine:(ThunderEngine * _Nonnull)engine
        onRemoteAudioStatsOfUid:(nonnull NSString*)uid
        stats:(ThunderRtcRemoteAudioStats* _Nonnull)stats;
@end

__attribute__((visibility("default"))) @interface ThunderEngineConfig : NSObject
@property(assign, nonatomic) NSString* _Nullable appId;
@property(assign, nonatomic) NSInteger sceneId;
@property(assign, nonatomic) NSInteger areaType;
@property(assign, nonatomic) NSInteger serverDomain;
@property(assign, nonatomic) id<ThunderEventDelegate> _Nullable delegate;
@end

/**
 @protocol
 @brief Interface for callback on audio capture data
 */
__attribute__((visibility("default"))) @protocol ThunderExternalAudioProcessorDelegate <NSObject>

@required
/**
 @brief Audio capture starts
 */
- (void)audioCaptureStart;

/**
 @brief Callback on audio capture data
 */
- (void)audioCaptureData:(void*_Nonnull)data
                     len:(uint32_t)len
              sampleRate:(uint32_t)sampleRate
            channelCount:(uint32_t)channelCount
            bitPerSample:(uint32_t)bitPerSample;

/**
 @brief Audio capture stops
 */
- (void)audioCaptureStop;

/**
 @brief Audio rendering starts
 */
- (void)audioRenderStart;

/**
 @brief Callback on audio rendering data
 */
-(void)audioRenderData:(void*_Nonnull)data
                   len:(uint32_t)len
            sampleRate:(uint32_t)sampleRate
          channelCount:(uint32_t)channelCount
          bitPerSample:(uint32_t)bitPerSample;

/**
 @brief Audio rendering stops
 */
- (void)audioRenderStop;

@end

/**
 @protocol
 @brief Interface for pushing video data
 @remark
 The [ThunderCustomVideoSourceProtocol shouldInitialize] interface provides a ThunderVideoFrameConsumer object to the external;
 The object calls the pushing interface to push external video data.
 */
__attribute__((visibility("default"))) @protocol ThunderVideoFrameConsumer <NSObject>

@required

/**
 @brief Interface for pushing raw video data
 @param [IN] pixelBuffer Raw video data (one frame)
 @param [IN] timestamp System time when the current frame is displayed; unit: ms; the developer must set a timestamp for each video frame.
 @param [IN] rotation Clockwise rotation angle for video
 */
- (void)consumePixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
             withTimestamp:(CMTime)timestamp
                  rotation:(ThunderVideoRotation)rotation;

/**
 @brief Interface for pushing raw video data
 @param [IN] rawData Raw video data (one frame)
 @param [IN] timestamp System time when the current frame is displayed; unit: ms; the developer must set a timestamp for each video frame.
 @param [IN] format Image format
 @param [IN] size Size of video naked data
 @param [IN] rotation Clockwise rotation angle for video
 */
- (void)consumeRawData:(void *_Nonnull)rawData
         withTimestamp:(CMTime)timestamp
                format:(ThunderVideoPixelFormat)format
                  size:(CGSize)size
              rotation:(ThunderVideoRotation)rotation;

/**
@brief Interface for pushing original video data
@param [IN] sampleBuffer Original video data (one frame)
*/
- (void)consumeCMSampleBuffer:(CMSampleBufferRef _Nonnull)sampleBuffer;

@end

/**
 @protocol
 @brief The developer implements the interface to create a custom video source. If the interface is not configured, the built-in camera is enabled for video stream publishing inside the SDK. 
 Users may change and control the default video input device by calling the setVideoSource interface.
 */
__attribute__((visibility("default"))) @protocol ThunderCustomVideoSourceProtocol <NSObject>

@required
/**
 @brief Initialize video source
 @return YES: Initializing customized video source completed;
NO: Customized video source device is not ready or fails in initialization. Engine will stop and report the error. 
 @remark
 When initializing video source, Engine will call this method. The developer can make some preparations in this method, e.g. opening the camera, initializing the video source, and telling Engine via return value whether the customized video source is ready. 
 In initializing the video source, the developer shall specify a Buffer type in bufferType, and use only the method corresponding to it in customized video source to transmit the video frame data. 
 In initializing the video source, Engine will transmit a ThunderVideoFrameConsumer object to the developer. The developer shall save this object, and input the video frame to Engine via this object after the video source is enabled.
 */
- (BOOL)onInitialize:(nullable id<ThunderVideoFrameConsumer>)protocol;

/**
 @brief Obtain Buffer type
 @remark
 In initialization, Engine will call this method to consult the Buffer type used by this video source. The developer must and can only specify one Buffer type and tell Media Engine via return value.
 */
- (ThunderVideoBufferType)bufferType;

/**
 @brief Enable video source
 YES: The custom video source is enabled successfully. Then, ThunderVideoFrameConsumer is enabled to receive video frames from the developer.
 NO: The custom video source device fails to be enabled. The Engine stops and reports an error. 
 @remark
 Engine The Engine calls back the method when enabling the video source. The developer may enable video frame capture in the method. The developer uses the returned value to notify the Media Engine whether the custom video source is enabled successfully.
 */
- (void)onStart;

/**
 @brief Stop video source
 @remark
This method will be called when the video source is stopped. The developer can stop collecting videos in this method. Media Engine notifies the developer via this callback that the frame input switch of ThunderVideoFrameConsumer is about to close and video frame input afterwards will be discarded.
 */
- (void)onStop;

/**
 @brief Release video source
 @remark
 Engine notifies the developer that the video source is about to be invalidated and he can shut down the video source device in this method. Engine will destroy the ThunderVideoFrameConsumer object and the developer shall ensure it will no longer be used after this callback.
 */
- (void)onDispose;

@end

/**
 @protocol
 @brief Proxy interface for decoded frame data
 */
__attribute__((visibility("default"))) @protocol ThunderVideoDecodeFrameObserver <NSObject>

@required
/**
 @brief Receive decoded frame data from decoder
 @param [OUT] pixelBuf buf pointer of current frame
 @param [OUT] pts Time shown in current frame
 @param [OUT] uid View the other's uid
*/
- (void)onVideoDecodeFrame:(CVPixelBufferRef _Nonnull) pixelBuf pts:(uint64_t)pts uid:(NSString* _Nonnull)uid;

@end

/**
 @protocol
 @brief Proxy interface for video frame preprocessing
 */
__attribute__((visibility("default"))) @protocol ThunderVideoCaptureFrameObserver <NSObject>

@required
/**
 @brief Declaration is made to SDK on which format of data will be used. The following two methods will be called in accordance with the format set.
 @return Use which format to callback
 */
- (ThunderVideoCaptureFrameDataType)needThunderVideoCaptureFrameDataType;

/**
 @brief Receive a frame of data from capture for processing and return processed data
 @param [OUT] pixelBuf  buf pointer of current frame
 @return Return the processed pixelbuff. If the data is not processed, return pixelbuffer in the parameter directly.
 */
- (CVPixelBufferRef _Nullable)onVideoCaptureFrame:(EAGLContext *_Nonnull)glContext
                                      PixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuf;

/**
 @brief Return src texture and dst texture
 @param [OUT] context EAGLContext
 @param [OUT] pixelBuffer Original image pixelBuffer
 @param [OUT] srcTextureID ID of source texture
 @param [OUT] dstTextureID ID of destination texture
 @param [OUT] textureFormat Texture format
 @param [OUT] textureTarget texture target
 @param [OUT] width Texture width
 @param [OUT] height Texture height
 @return bool
 */
- (BOOL)onVideoCaptureFrame:(EAGLContext *_Nonnull)context
                PixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
            SourceTextureID:(unsigned int)srcTextureID
       DestinationTextureID:(unsigned int)dstTextureID
              TextureFormat:(int)textureFormat
              TextureTarget:(int)textureTarget
               TextureWidth:(int)width
              TextureHeight:(int)height;

@end

/**
 @protocol
 @brief Proxy of media extra information
 */
__attribute__((visibility("default"))) @protocol ThunderMediaExtraInfoDelegate <NSObject>

@required
/**
 @brief Callback on failure in sending media extra information
 @param [OUT] status For failure status, see ThunderSendMediaExtraInfoFailedStatus.
 */
- (void)onSendMediaExtraInfoFailedStatus:(NSUInteger) status;

/**
 @brief Receive media extra information
 @param [OUT] uid ID of the user
 @param [OUT] data Media extra information
 */
- (void)onRecvMediaExtraInfo:(nonnull NSData*)data ofUid:(nonnull NSString*)uid;

@optional
/**
 @brief Extra information of mixed audio stream received
 @param [OUT] uid ID of mixed audio stream user
 @param [OUT] infos Original stream information about mixed audio stream, identifying which streams contribute to this mixed audio stream
 */
- (void)onRecvMixAudioInfo:(nonnull NSArray<ThunderMixAudioInfo*>*) infos ofUid:(nonnull NSString*)uid;

/**
 @brief Extra information of mixed video stream received
 @param [OUT] uid ID of mixed video stream user
 @param [OUT] infos Original stream information about mixed video stream, identifying which streams contribute to this mixed video stream and the stream layout information.
 */
- (void)onRecvMixVideoInfo:(nonnull NSArray<ThunderMixVideoInfo*>*) infos ofUid:(nonnull NSString*)uid;

@end

#pragma mark Video common
__attribute__((visibility("default"))) @protocol IThunderRtcVideoEngineKit <NSObject>

@required
/**
 @brief After enabling WebSDK compatibility, the encoding B-frames is prohibited internally, because it cannot be encoded normally by WebSDK. 
  The interface must be called before publishing and is irrelevant with entry into or exit from the room. 
 @param [IN] enabled  Whether compatibility is enabled. Disabled by default 
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 */
- (int)enableWebSdkCompatibility:(BOOL)enabled;

/**
 @brief Enable video module
 Video is enabled by default when a user enters a room; in audio-only mode, users may call this interface to switch to video.
 */
- (int)enableVideoEngine __attribute__((deprecated("this method has been deprecated")));

/**
 @brief Disable video module
 If the interface is called before entry into a room, the media mode is audio/video when a user enters a room; if the interface is called after entry into a room, the media mode switches to audio-only.
 */
- (int)disableVideoEngine __attribute__((deprecated("this method has been deprecated")));

/**
 @brief Set video encoding configuration
 @param [IN] config Specific encoding configuration
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)setVideoEncoderConfig:(ThunderVideoEncoderConfiguration* _Nonnull)config;

/**
 @brief Set rendering view of local video
 @param [IN] local  Specific rendering settings
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark (1)The interface shall be called after initialization.
         (2)The SDK will render the anchor's video to the view when startVideoPreview.
         (3)If the user destroys the view, you need to call this API again to set "view" to "null" to unbind SDK and view.
         Otherwise, when startVideoPreview is called again, it will access the wild pointer of the view and cause a crash.
 */
- (int)setLocalVideoCanvas:(ThunderVideoCanvas *_Nullable)local;

/**
 @brief Set display mode of remote view
 @param [IN] remotePlayType View display mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)setRemotePlayType:(ThunderRtcRemotePlayType)remotePlayType;

/**
 @brief Set multi-person microphone connection layout
 @param [IN] params Specific microphone connection layout
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)setMultiVideoViewLayout:(ThunderMultiVideoViewParam* _Nonnull)params;

/**
 @brief Set rendering view of remote video
 @param [IN] remote Specific view settings
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark (1)The interface shall be called after initialization.
         (2)The SDK automatically subscribes to the audio and video streams in the channel. After setting the remote anchor
         uid and view, the SDK will save the binding relationship between uid and view and render the video to the view.
         (3)If the user destroys the view, you need to call this API to set "view" to "null" to unbind SDK and view.
         Otherwise, if the remote host re-publishs, the SDK will access the wild pointer of the view and cause a crash. 
         when it subscribes automatically.
*/
- (int)setRemoteVideoCanvas:(ThunderVideoCanvas *_Nonnull)remote;

/**
 @brief Set display mode of local view
 @param [IN] mode Rendering display mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)setLocalCanvasScaleMode:(ThunderVideoRenderMode)mode;

/**
 @brief Set display mode of remote view
 @param [IN] mode Rendering display mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)setRemoteCanvasScaleMode:(NSString* _Nonnull)uid mode:(ThunderVideoRenderMode)mode;

/**
 @brief Enable video preview of local camera
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)startVideoPreview;

/**
 @brief Disable video preview of local camera
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)stopVideoPreview;

/**
 @brief Enable/disable local video capture
 @param [IN] enabled true: Enable local capture; false: Disable local capture
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)enableLocalVideoCapture:(BOOL)enabled;

/**
 @brief Enable/disable local video sending
 @param [IN] stopped true: Enable local video sending; false: Disable local video sending
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface cannot be called until after joining room successfully.
 */
- (int)stopLocalVideoStream:(BOOL)stopped;

/**
 @brief Stop/receive all remote videos
 @param [IN] stopped true: Stop all remote video streams; false: Receive all remote video streams; default value: false
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 To determine whether to receive or stop remote videos, view the value of stopRemoteVideoStream first; if stopRemoteVideoStream is not set, view the value of this function.
 */
- (int)stopAllRemoteVideoStreams:(BOOL)stopped;

/**
 @brief Stop/receive designated remote videos
 @param [IN] uid User ID
 @param [IN] stopped true: Stop remote videos of a designated user; false: Receive remote videos of a designated user
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 To determine whether to receive or stop remote videos, view the value of this function first; if this function is not set, view the value of stopAllRemoteVideoStreams.
 */
- (int)stopRemoteVideoStream:(NSString* _Nonnull)uid stopped:(BOOL)stopped;

/**
 * @brief 开/关视频双流模式
 * @param [IN] enabled 指定双流或者单流模式 YES:双流模式 NO:单流模式(默认)
 * @return 0:成功,其它错误参见enum ThunderRet
 * @remark (1)  在"初始化"后,且视频开播前调用,仅在destoryEngine重置
 *        (2)  使用该方法设置单流（默认）或者双流模式。发送端开启双流模式后，接收端可以选择接收大流还是小流。
 *           其中，大流指高分辨率、高码率的视频流，小流指低分辨率、低码率的视频流。
 */
- (int)enableLocalDualStreamMode:(BOOL)enabled;

/**
 * @brief 设置默认订阅的视频流类型
 * @param [IN] type 设置默认接收的视频流类型 参见ThunderVideoStreamType
 * @return 0:成功,其它错误参见enum ThunderRet
 * @remark (1)  在"初始化"后，且进房间前调用，在destroyEngine会重置
 *        (2)  接收远端视频流的类型优先判断changeRemoteVideoStreamType设置的值，没有的话再使用该函数设置的值，
 *           如果这两个接口都没调用，默认订阅远端视频流都是大流
 */
- (int)setDefaultRemoteVideoStreamType:(ThunderVideoStreamType)type;

/**
 * @brief 设置订阅的视频流类型
 * @param [IN] uid 用户 UID
 * @param [IN] type 视频流类型 参见ThunderVideoStreamType
 * @return 0:成功,其它错误参见enum ThunderRet
 * @remark (1)  在"初始化"后调用，在destroyEngine和leaveRoom时会重置
 *        (2)  发送端如果调用 enableLocalDualStreamMode(true)开启双流模式，接收端可选择接收大流还是小流，
 *           如果发送端不开启双流模式，接收端默认接收大流
 *        (3)  接收远端视频流的类型优先判断该接口设置的值，没有的话再使用setDefaultRemoteVideoStreamType设置的值,
 *           如果这两个接口都没调用，默认订阅远端视频流都是大流
 */

- (int)changeRemoteVideoStreamType:(NSString* _Nonnull)uid type:(ThunderVideoStreamType)type;

/**
 @brief Set external video capture source
 @param [IN] videoSource External video capture source protocol class
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setCustomVideoSource:(id<ThunderCustomVideoSourceProtocol> _Nullable)videoSource;

/**
 @brief Add local video watermark
 @param [IN] watermark Watermark name
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark
 In this method, a PNG image (the format must be PNG) is added to local live video streams as a watermark; audiences in the same live streaming room, audiences of bypass stream publishing and even the recording equipment can capture the watermark image. Only one watermark can be added into the live video, and the watermark added later will replace the last one.
 */
- (int)setVideoWatermark:(ThunderImage *_Nonnull)watermark;

 
/**
* @brief 设置本地固定的推流画面,只支持摄像头采集场景，外部推流场景不支持(IOS录屏为外部推流场景)
* @param image 固定推流画面image，
                1. 传入参数为nil的时候恢复为替换前的采集源（摄像头）
                2. 已设置固定推流画面，传入新的image,使用新的固定推流画面替换已设置的推流画面
                3. 当传入的图片的宽高比与设置的编码宽高比不一致时，SDK负责裁剪图片与编码宽高比一致
* @return 0:成功, 其它错误参见enum ThunderRet
* @remark 1. 设置该接口后，image会替换采集源的图像，作为固定采集输入源
          2. 该接口在"SDK初始化"后调用，可在开采集或者开编码后任意时刻设置
          3. 该设置直到卸载SDK后才重置，要恢复原来的采集源，必须传入nil参数来重置
          4. SDK内部不负责image的内存释放，业务层设置固定推流画面后负责image的回收
          5. 在设置固定推流画面后，业务层回收image，行为未定义，业务层必须保证image的有效性
*/
 
 
- (int)setCaptureReplaceImage:(UIImage *_Nullable)image;

 /**
 @brief  capture remote screenshot image
 @param [IN] uid  is id of  audiences
 @return  the object of  CVPixelBufferRef  for  success; nil For other errors,
 @remark
 In this method, image is captured with uid after render ; Only one image can be captured  at a time  .
 */
- (_Nullable CVPixelBufferRef)captureRemoteScreenShot:(nonnull NSString*)uid;
/**
@brief  capture Local screenshot image
@return  the object of  _UIImage referrence  for  success; nil For other errors,
@remark
In this method, image is captured  with local camrea ; Only one image can be captured  at a time  .
*/
-(UIImage *_Nullable) captureLocalScreenshot;
/**
 @brief Set decoding data callback for video stream of a certain UID
 @param [IN] delegate Decoding callback implemented
 @param [IN] uid ID of the video stream user
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization,it is reset when leaveRoom is called.
 */
-(int)registerVideoDecodeFrameObserver:(nullable id<ThunderVideoDecodeFrameObserver>)delegate
                                   uid:(nonnull NSString*)uid;

/**
 @brief Set the interface for callback on local video preprocessing
 @param [IN] delegate Interface for preprocessing of local video frames, which can be used for custom processing such as beauty
 */

-(int)registerVideoCaptureFrameObserver:(nullable id<ThunderVideoCaptureFrameObserver>)delegate;

/**
 @brief Switch to front/rear camera
 @param [IN] bFront true: front camera , false: rear camera 
 @return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)switchFrontCamera:(BOOL)bFront;

/**
 @brief Set portrait/landscape; default: portrait; available for publishing before preview
 @param [IN] orientation See ThunderVideoCaptureOrientation.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setVideoCaptureOrientation:(ThunderVideoCaptureOrientation)orientation;

/**
 @brief Set camera mirroring; available for publishing before preview; valid for front camera only
 @param [IN] mode For the mirroring mode, see ThunderVideoMirrorMode.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setLocalVideoMirrorMode:(ThunderVideoMirrorMode)mode;

@end

#pragma mark Audio common
__attribute__((visibility("default"))) @protocol IThunderRtcAudioEngineKit <NSObject>

@required
/**
 @brief Audio publishing
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface cannot be called until after joining room successfully.
 */
- (int)enableAudioEngine __attribute__((deprecated("this interface has been deprecated, stopLocalAudioStream(NO) is recommended")));

/**
 @brief Audio stopped
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface cannot be called until after joining room successfully.
 */
- (int)disableAudioEngine __attribute__((deprecated("this interface has been deprecated, stopLocalAudioStream(YES) is recommended")));

/**
 @brief Set whether to enable the speaker
 @param [IN] enableSpeaker YES = Enable the speaker; NO = Disable the speaker
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)enableLoudspeaker:(BOOL)enableSpeaker;

/**
 @brief Loudspeaker status or not
 @return YES: Loudspeaker; NO: Receiver
 */
- (BOOL)isLoudspeakerEnabled;

/**
 @brief Set audio profile
 @param [IN] config Set sampling rate, bit rate, encoding mode and number of channels
 @param [IN] commutMode Set interaction mode
 @param [IN] scenarioMode Set scenario mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called before audio capture and publishing.
 */
- (int)setAudioConfig:(ThunderRtcAudioConfig)config
            commutMode:(ThunderRtcCommutMode)commutMode
          scenarioMode:(ThunderRtcScenarioMode)scenarioMode;

/**
 @brief Callback on turning on user volume
 @param [IN] interval Callback interval ≤ 0; The volume prompt is disabled, >0: Callback interval (unit: millisecond); default value: 0; the interval of more than 200 milliseconds is recommended.
 @param [IN] moreThanThd From <moreThanThd to >=moreThanThd, immediately call back once ≤ 0: Invalid; default value = 0
 @param [IN] lessThanThd From >=lessThanThd to <lessThanThd, immediately call back once ≤ 0: Invalid; default value = 0
 @param [IN] smooth Not implemented
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called. After the callback is enabled, onPlayVolumeIndication notification will be received once anyone speaks in the room.
 */
- (int)setAudioVolumeIndication:(NSInteger)interval
                       moreThanThd:(NSInteger)moreThanThd
                       lessThanThd:(NSInteger)lessThanThd
                            smooth:(NSInteger)smooth;

/**
 @brief Callback on turning on microphone volume
 @param interval Callback interval ≤ 0; The volume prompt is disabled, >0: Callback interval (unit: millisecond); default value: 0
 @param moreThanThd From <moreThanThd tp >=moreThanThd, immediately call back once ≤ 0:  Invalid; default value = 0
 @param lessThanThd From >=lessThanThd to <lessThanThd, immediately call back once ≤ 0: Invalid; default value = 0
 @param smooth Not implemented
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called. After the callback is enabled, onCaptureVolumeIndication notification will be received once anyone speaks in the room.
 */
- (int)enableCaptureVolumeIndication:(NSInteger)interval
                         moreThanThd:(NSInteger)moreThanThd
                         lessThanThd:(NSInteger)lessThanThd
                              smooth:(NSInteger)smooth;

/**
 @brief Disable/Enable local audio (including audio capture, encoding and upload)
 @param [IN] stopped true: Disable local audio; false: Enable local audio
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface cannot be called until after joining room successfully.
 */
- (int)stopLocalAudioStream:(BOOL)stopped;

/**
 * @brief Enable/disable local audio capture
 * @param [IN] enabled true: Enable local capture; false: Disable local capture
 * @return 0: Succeeded; For other errors, see enum ThunderRet.
 * @remark (1) The interface shall be called after initialization. Uninstalling the SDK will automatically close the         audio capture
          (2) Use enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combined APIs to publish audio and stopLocalAudioStream to publish audio is equivalent.
          (3) The enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs provide more advanced audio publish methods. If you just simply start publishing, use the stopLocalAudioStream method.
          (4) If you have used the enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs for publishing, it is recommended not to use the stopLocalAudioStream API, so as to avoid doubts caused by function coverage, and vice versa.
          (5) If setAudioSourceType is called to set the publishing mode to THUNDER_PUBLISH_MODE_NONE, the call to this API fails.
          (6) If you call setCustomAudioSource to enable external push streaming, the call to this API fails.
 */
- (int)enableLocalAudioCapture:(BOOL)enabled;

/**
 * @brief Enable/disable local audio encoder
 * @param [IN] enabled true: Enable local audio encoder; false: Disable local audio encoder
 * @return 0: Succeeded; For other errors, see enum ThunderRet.
 * @remark (1) The interface shall be called after initialization. Uninstalling the SDK will automatically close the audio encoder
          (2) Use enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combined APIs to publish audio and stopLocalAudioStream to publish audio is equivalent.
          (3) The enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs provide more advanced audio publish methods. If you just simply start publishing, use the stopLocalAudioStream method.
          (4) If you have used the enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs for publishing, it is recommended not to use the stopLocalAudioStream API, so as to avoid doubts caused by function coverage, and vice versa.
          (5) If setAudioSourceType is called to set the publishing mode to THUNDER_PUBLISH_MODE_NONE, the call to this API fails.
          (6) If you call setCustomAudioSource to enable external push streaming, the call to this API fails.
 */
- (int)enableLocalAudioEncoder:(BOOL)enabled;

/**
 * @brief Enable/disable local audio publisher
 * @param [IN] enabled true: Enable local audio publisher; false: Disable local audio publisher
 * @return 0: Succeeded; For other errors, see enum ThunderRet.
 * @remark (1) Call this interface after joining room and receiving onJoinRoomSuccess callback. Leaving the room will automatically disable audio publisher.
          (2) Use enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combined APIs to publish audio and stopLocalAudioStream to publish audio is equivalent.
          (3) The enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs provide more advanced audio publish methods. If you just simply start publishing, use the stopLocalAudioStream method.
          (4) If you have used the enableLocalAudioCapture, enableLocalAudioEncoder, enableLocalAudioPublisher combination APIs for publishing, it is recommended not to use the stopLocalAudioStream API, so as to avoid doubts caused by function coverage, and vice versa.
          (5) It is recommended to use setCustomAudioSource and this interface to start external push streaming.
 */
- (int)enableLocalAudioPublisher:(BOOL)enabled;

/**
 * @brief Whether the local audio is enabled
 * @return YES: enabled; NO: disabled
 * @remark This API should be called after initialization
 */
- (BOOL)isAudioCaptureEnabled;

/**
 @brief Stop/receive all audio data; default value: false
 @param [IN] stopped true: Stop all remote audios; false: Receive all remote audios
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 To determine whether to receive or stop remote audios, view the value of stopRemoteAudioStream first; if stopRemoteAudioStream is not set, view the value of this function.
 */
- (int)stopAllRemoteAudioStreams:(BOOL)stopped;

/**
 @brief Stop/receive designated audio data
 @param [IN] uid User ID
 @param [IN] stopped true: Stop user audio; false: Receive user audio
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 To determine whether to receive or stop remote audios, view the value of this function first; if this function is not set, view the value of stopAllRemoteAudioStreams.
 */
- (int)stopRemoteAudioStream:(NSString*_Nonnull)uid stopped:(BOOL)stopped;

/**
 @brief Set loudspeaker volume.
 */
- (int)setLoudSpeakerVolume:(NSInteger)volume;

/**
 @brief Set microphone volume
 */
- (int)setMicVolume:(NSInteger)volume;

/**
 * deprecated("use registerAudioFrameObserver: instead.")
 @brief Set external audio processor
 */
- (int)setExternalAudioProcessor:(nullable id<ThunderExternalAudioProcessorDelegate>)delegate;

/**
 @brief Set play volume for a single user
 */
- (int)setPlayVolume:(nonnull NSString*)uid volume:(NSInteger)volume;

/**
 @brief Create audio file player
 */
- (nullable ThunderAudioFilePlayer*)createAudioFilePlayer;

/**
 @brief Release the file player object
 */
- (void)destroyAudioFilePlayer:(nonnull ThunderAudioFilePlayer*)filePlayer;

/**
 @brief Enable in-ear monitor
 */
- (int)setEnableInEarMonitor:(BOOL)enabled;

/**
 * @brief set in-ear monitor volume
 * @param volume ranges [0~100]，default 100
 * @return 0: succeeded. For other errors, see{@link ThunderRtcConstant.ThunderRet}
 */
- (int)setEarMonitoringVolume:(NSInteger)volume;

/**
 @brief Enable/Disable equalizer
 */
- (int)setEnableEqualizer:(BOOL)enabled;

/**
 @brief Set equalizer parameters
 */
- (int)setEqGains:(const _Nonnull ThunderEqGainsOc)gains;

/**
 @brief Enable/Disable reverb
 */
- (int)setEnableReverb:(BOOL)enabled;

/**
 @brief  Set reverb parameters
 */
- (int)setReverbParam:(ThunderReverbExParamOc)reverbParam;

/**
 * deprecated("use setEnableLimiter: instead.")
 @brief  Enable/Disable compressor
 */
- (int)setEnableCompressor:(BOOL)enabled;

/**
 * deprecated("use setLimiterParam: instead.")
 @brief  Set compressor parameters
 */
- (int)setCompressorParam:(ThunderCprParamOc)parameter;

/**
 @brief  Enable/Disable pressure limiter
 */
- (int)setEnableLimiter:(BOOL)enabled;

/**
 @brief  Set pressure limiter parameters
 */
- (int)setLimiterParam:(ThunderLimiterParamOc)parameter;

/**
 @brief Enable callback on audio playback data
 */
- (void)enableAudioDataIndication:(BOOL)enabled;

/**
  @brief Set publishing mode
 */
- (void)setAudioSourceType:(ThunderSourceType)sourceType;

/**
 @brief  Disable/enable notification on play spectrum callback
 */
- (void)enableAudioPlaySpectrum:(Boolean)enable;

/**
 @brief Set play spectrum parameters
 @param [IN] spectrumLen Length of spectrum data; value range: 12-256; default value: 256
 @param [IN] notifyIntervalMS Callback interval of spectrum data, which must be multiples of 10; unit: ms; default value: 30 ms
 */
- (void)setAudioPlaySpectrumInfo:(UInt32)spectrumLen notifyIntervalMS:(UInt32)notifyIntervalMS;

/**
 @brief Send service-customized broadcast messages
 @param [IN] msgData  Service-customized broadcast messages
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface sends messages via media UDP channel with features of low latency and unreliability. The specific limitations are as follows
  1. Sender must enter the room. 
  2. Call it when microphone is opened successfully (unavailable for pure audience or upon failure of publishing authentication). 
  3. This interface should be called with a frequency of less than twice each second. msgData should not exceed 200 bytes.
  4. The msg will be dropped if any above condition is not met. 
  5. Not guaranteed to send to all online users in the room, or sent in order. 
  Note 1: Notify causes for failure in sending customized broadcast messages through onSendAppMsgDataFailedStatus
  Note 2: Customized broadcast messages sent by other users will be notified to the application through onRecvUserAppMsgData
 */
- (int)sendUserAppMsgData:(NSData * _Nonnull) msgData;

/**
 @brief Send media extra information (audio/video publishing)
 @param [IN] data Media extra information
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The following describes how to send media extra information in detail: 
 1. The interface can be called only if the sender joins the room and audio publishing succeeds
2. Audio publishing only: The fastest frequency for calling this interface is 100ms once, and the media extra information does not exceed 200 bytes
3. Video publishing: The calling frequency cannot exceed the frame rate, and the media extra information does not exceed 2,048 bytes. 
   For example: Stream publishing applies default frame rate of 15 FPS, that is, the calling frequency cannot exceed 66.7 ms/time (1000/15).
 4. Packet loss may occur.
 5. SDK will try to call back media data at the time when related frames are played.
Note 1: onSendMediaExtraInfoFailedStatus is used to notify the causes for failure in sending media extra information.
 Note 2: onRecvMediaExtraInfo is used to notify the application of the media extra information sent by other users.
 */
- (int)sendMediaExtraInfo:(NSData * _Nonnull)data;

/**
 @brief Set callback and monitoring of media extra information
 @param [IN] delegate Object instance for which ThunderMediaExtraInfoDelegate proxy is implemented
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark Conditions for calling the interface: 
  1. The interface shall be called after SDK is initialized and before entering the channel.
  If no extra information needs to be received, call [setMediaExtraInfoDelegate:nil] to remove callback and monitoring.
 */
- (int)setMediaExtraInfoDelegate:(nullable id<ThunderMediaExtraInfoDelegate>)delegate;

/**
 @brief Enable video mixing carrying media extra information, for example: layout information carried in video-mixing videos
  After enabling, IThunderMediaExtraInfoCallback##onRecvMixVideoInfo callback can be received when this video mixing stream is played on the play terminal
 * @param enable true: enabled false: disabled (disabled by default)
 * @return 0: succeeded. For other errors, see enum ThunderRet
*/
- (int)enableMixVideoExtraInfo:(BOOL)enable;

/**
  @brief Synchronize the play progress of external accompaniment video for video mixing synchronization. Only one of audio accompaniment and video accompaniment is supported.
  @param [IN] currentMs Current play progress
  @return 0: succeeded. For other errors, see enum ThunderRet
  */
- (int)syncMediaPlayingProgress:(int)currentMs;

/**
 @brief Start saving audio data in aac format
 @param [IN] fileName Save path of files, which must be a full path including the file name with suffix .aac. The directory for saving files must be created in advance, and the folder cannot be created by this interface. For example: /sdcard/helloworld.aac
 @param [IN] saverMode Audio saving mode @see ThunderSaverMode
 @param [IN] fileMode File saving mode  @see ThunderFileMode
 @return Success or fail
 */
- (BOOL)startAudioSaver:(NSString* _Nonnull)fileName
              saverMode:(ThunderSaverMode)saverMode
               fileMode:(ThunderFileMode)fileMode;

/**
 @brief Stop saving audio data in aac format
 @return success or fail
 */
- (BOOL)stopAudioSaver;

/**
 @brief Enable/disable callback on audio capture
 @param [IN] enable Enable callback on audio capture data
 @param [IN] sampleRate Set the sampling rate of the data to be called back; value range: [-1, 8000, 16000, 44100, 48000]
 @param [IN] channel Set the number of channels for the data to be called back; value range: [-1, 1, 2]
 @remark
As long as either of sampleRate and channel is set to -1, the callback data is the original data without resampling.
 */
- (void)enableCapturePcmDataCallBack: (BOOL)enable sampleRate:(NSInteger)sampleRate channel:(NSInteger)channel __attribute__((deprecated("[该接口已废弃]使用registerAudioFrameObserver")));

/**
 @brief Enable/disable callback on rendered audio data
 @param [IN] enable Enable callback on rendered audio data
 @param [IN] sampleRate Set the sampling rate of the data to be called back; value range: [-1, 8000, 16000, 44100, 48000]
 @param [IN] channel Set the number of channels for the data to be called back; value range: [-1,1,2]
 @remark
 As long as either of sampleRate and channel is set to -1, the callback data is the original data without resampling.
 */
- (BOOL)enableRenderPcmDataCallBack: (BOOL)enable sampleRate:(NSInteger)sampleRate channel:(NSInteger)channel
__attribute__((deprecated("[该接口已废弃]使用registerAudioFrameObserver")));

/**
 @brief Set different sound effect modes
 @param [IN] mode Audio saving mode @see YSoundEffectMode
 */
- (void)setSoundEffect:(int32_t)mode;

/**
 @brief Set voice change mode
 @param [IN] mode Voice change @see YVoiceChangerMode
 */
- (void)setVoiceChanger:(int32_t)mode;

/**
 @brief Set the mode for using raw audio recording data during onRecordAudioFrame callback
 @param [IN] sampleRate Sampling rate
 @param [IN] channel Audio track: 1: Single track; 2: Dual track
 @param [IN] mode  For use mode of onRecordAudioFrame, see ThunderAudioRawFrameOperationMode.
 @param [IN] samplesPerCall Specify the number of samples for returned data in onRecordAudioFrame; for example, the value is generally 1024 in transcoding and stream publishing. 
  samplesPerCall = (int)(sampleRate × sampleInterval), in which: sampleInterval ≥ 0.01, in seconds. 
 @return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)setRecordingAudioFrameParameters:(NSInteger)sampleRate
                                channel:(NSInteger)channel
                                   mode:(ThunderAudioRawFrameOperationMode)mode
                         samplesPerCall:(NSInteger)samplesPerCall;

/**
@brief Set the mode for using raw audio mix data during onMixedAudioFrame callback
@param [IN] sampleRate Sampling rate
@param [IN] channel Audio track: 1: Single track; 2: Dual track
@param [IN] samplesPerCall Specify the number of samples for returned data in onMixedAudioFrame; for example, the value is generally 1024 in transcoding and stream publishing.
 samplesPerCall = (int)(sampleRate × sampleInterval), in which: sampleInterval ≥ 0.01, in seconds.
@return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)setMixedAudioFrameParameters:(NSInteger)sampleRate
                            channel:(NSInteger)channel
                     samplesPerCall:(NSInteger)samplesPerCall;

/**
 Set the mode for using raw audio playback data during onPlaybackAudioFrame callback
 @param [IN] sampleRate Sampling rate
 @param [IN] channel Audio track: 1: Single track; 2: Dual track
 @param [IN] mode      For use mode of onPlaybackAudioFrame, see ThunderAudioRawFrameOperationMode.
 @param [IN] samplesPerCall Specify the number of samples for returned data in onPlaybackAudioFrame; for example, the value is generally 1024 in transcoding and stream publishing. 
  samplesPerCall = (int)(sampleRate × sampleInterval), in which: sampleInterval ≥ 0.01, in seconds. 
 @return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)setPlaybackAudioFrameParameters:(NSInteger)sampleRate
                               channel:(NSInteger)channel
                                  mode:(ThunderAudioRawFrameOperationMode)mode
                        samplesPerCall:(NSInteger)samplesPerCall;

/**
 @brief Enable external audio capture
 @param [IN] sampleRate Sampling rate of external audio source, which can be set to 8000, 16000, 32000, 44100 or 48000
 @param [IN] channelsPerFrame Number of channels for external audio source (support two at most)
 @return 0: succeeded. For other errors, see enum ThunderRet
 @mark This method must be called before audio publishing.
 */
- (int)enableCustomAudioSource:(NSUInteger)sampleRate channelsPerFrame:(NSUInteger)channelsPerFrame;

/**
 @brief Disable external audio capture
 @return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)disableCustomAudioSource;

/**
 @brief Push external audio streams
 @param [IN] data External audio data
 @param [IN] samples Number of samples for audio data
 @param [IN] timestamp Timestamp of external audio data, which is used for synchronization with external video sources
 @return YES: Method call succeeded; NO: Method call failed
 */
- (BOOL)pushCustomAudioRawData:(void *_Nonnull)data samples:(NSUInteger)samples timestamp:(NSTimeInterval)timestamp;

/**
 @brief Push external audio frames
 @param [IN] sampleBuffer Audio frames
 @return YES: Method call succeeded; NO: Method call failed
 */
- (BOOL)pushCustomAudioSampleBuffer:(CMSampleBufferRef _Nonnull)sampleBuffer;

/**
 @brief Enable/Disable remote user voice stereo; ensure that this method is called before joinRoom.
 @param [IN] enable YES = Enable; NO = Disable
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)enableVoicePosition:(BOOL)enable;

/**
 @brief Set spatial azimuth and volume of remote user’s voices
 @param [IN] uid     Remote stream uid
 @param [IN] azimuth Set the azimuth where the remote user’s voices appear, with the value range of [-90, 90], in which 0: voices appearing right ahead (by default), -90: voices appearing at the left, and 90: voices appearing at the right
 @param [IN] gain    Set the volume of remote user’s voices, with the value range of [0, 100], in which the default value is 100.0 and indicates the original volume of this user. The smaller the value, the lower the volume
     *@return 0: succeeded. For other errors, see enum ThunderRet
 */
- (int)setRemoteUidVoicePosition:(nonnull NSString*)uid azimuth:(NSInteger)azimuth gain:(NSInteger)gain;

@end

#pragma mark interfaceDefine
__attribute__((visibility("default"))) @interface ThunderEngine : NSObject <IThunderRtcVideoEngineKit, IThunderRtcAudioEngineKit>

/**
 @brief Initialize and create RtcEngine
  After the app is created at yylivesdk.yy.com, the system assigns a unique app ID, which cannot be changed after initialization.
 @param [IN] appId Unique ID for accessing the app
 @param [IN] sceneId Scenario ID
 @param [IN] delegate The SDK reports various events at run time to the app through the class.
 @return ThunderEngine object
 */
+ (instancetype _Nonnull)createEngine:(NSString * _Nonnull)appId
                              sceneId:(NSInteger)sceneId
                             delegate:(id<ThunderEventDelegate> _Nullable)delegate;

/**
 @brief Initialize and create RtcEngine
  After the app is created at yylivesdk.yy.com, the system assigns a unique app ID, which cannot be changed after initialization.
 @param [IN] config of ThunderEngine
 @return ThunderEngine object
 */
+ (instancetype _Nonnull)createEngine:(ThunderEngineConfig* _Nonnull)config;
                             
/**
 @brief Destroy the ThunderEngine object
 */
+ (void)destroyEngine;

/**
 @brief Obtain SDK version number
 @return SDK version number; non-empty
 */
+ (NSString * _Nonnull)getVersion;

/**
 @brief Set scenario ID
 @param [IN] sceneId Scenario ID
 */
- (void)setSceneId: (NSInteger)sceneId;

/**
 @brief Set SDK callback event delegate
 @param [IN] delegate Callback protocol
*/
- (void)setThunderEventDelegate:(id<ThunderEventDelegate> _Nullable)delegate;

/**
 @brief Set room attribute
 @param [IN] config Set audio/video mode
 @param [IN] roomConfig Set scenario mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setRoomConfig:(ThunderRtcConfig)config
          roomConfig:(ThunderRtcRoomConfig)roomConfig
          __attribute__((deprecated("this interface has been deprecated, setMediaMode/setRoomMode is recommended")));

/**
 @brief Set country and area of users.
 @param [IN] area Area type (default value: AREA_DEFAULT (domestic))
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface takes effect if it is called before joinRoom. Calling is necessary for abroad users but not for domestic users.
 */
- (int)setArea:(ThunderRtcAreaType)area;

/*!
 @brief Set Thunder attributes
 @param [in]  options Relevant configuration information defined in JSON
 1. Set video group subscription:"JoinWithSubscribeGroup": true
 2. Set video group publishing:"PublishAudioToGroup": true
 3. Set channel number and subchannel number: "setSid":79804098,"setSubsid":79804098
 "setSubsid":79804098,
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset when destroyEngine is called; it is a non-public interface (not recommended unless necessary).
 */
- (int)setParameters:(NSString * _Nonnull)options;

/**
 @brief Set whether to support string-type UIDs
 @param is64bitUid Default value: true
   true: String-type UID, supporting the permutation and combination of characters such as [A, Z], [a, z], [0, 9], -, _, with the length of not more than 64 bytes.
   false: 32-bit unsigned integer, supporting only [0-9]; maximum value: 4294967295
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization and before joinRoom; it is reset when destroyEngine is called; it is a non-public interface (not recommended unless necessary).
 */
-(int)setUse64bitUid:(BOOL)is64bitUid;

/**
 @brief Join room
 @param [IN] token Required for authentication. For details, see "User Authentication Instructions" on the official website.
 @param [IN] roomName  Room number (unique for AppId)
 @param [IN] uid User ID, only supporting the permutation and combination of characters such as [A, Z], [a, z], [0, 9], -, _, with the length of not more than 64 bytes.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 Note 1: If users with SDK 2.2 or an earlier version need to use unsigned 32-bit UIDs, they need to call the setUse64bitUid(false) interface.
 Note 2: If Succeeded is returned after the function is executed, it only indicates that the request is executed successfully. Return of the onJoinRoomSuccess notification indicates joining room successfully.
 */
-(int)joinRoom:(NSString * _Nullable)token
      roomName:(NSString * _Nonnull)roomName
      uid:(NSString * _Nonnull)uid;

/**
 @brief Leave room
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface can be called after joining room successfully.
 */
- (int)leaveRoom;

/**
 @brief Update token
 @param [IN] token Required for authentication. For details, see "User Authentication Instructions" on the official website.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization.
 */
- (int)updateToken:(NSString * _Nonnull)token;

/**
 @brief Set directory for SDK to output log files. A directory with write permissions must be specified. 
 @param [IN] filePath Full log file path
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setLogFilePath:(NSString * _Nonnull)filePath;

/**
 @brief Set log callback; once log callback is set, setLogFilePath is invalid.
 @param [IN] delegate  Log protocol
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)setLogCallback:(nullable id<ThunderRtcLogDelegate>)delegate;

/**
 @brief set log saving level
 @param [IN] level Filter log filter
 @remark Logs with lower level (LogLevel) will be filtered. Only logs with the log level indicated by this value or higher than this value are recorded.
 */
- (void)setLogLevel:(ThunderRtcLogLevel)level;

/**
 @brief Add source stream publishing address [supporting a maximum of five stream publishing addresses]
 @param url [IN] Stream publishing address, in RTMP format; The value does not support special characters such as Chinese.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark After publishing, the server pushes the source stream to the corresponding URL. The interface can be called after joining the room (joinRoom), and the configuration will be cleared after exit from the room.
 */
- (int)addPublishOriginStreamUrl:(NSString* _Nonnull)url;

/**
 @brief Remove source stream publishing address, which can delete one stream publishing address at a time. If multi-channel streams need to be removed, this method shall be called multiple times.
 @param url [IN] Stream publishing address to be removed
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 */
- (int)removePublishOriginStreamUrl:(NSString* _Nonnull)url;

/**
 @brief Add/Update transcoding tasks [a maximum of 5 transcoding tasks supported in one room]
 @param [IN] taskId ID of a transcoding task, which is unique in a room and is managed by users.
                    only supporting the permutation and combination of characters such as [A, Z], [a, z], [0, 9], with the length of not more than 64 bytes.
 @param transcoding [IN] Specific transcoding layout
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark 
 1.After publishing, the server performs transcoding and pushes streams (if any) according to the configured canvas. The interface can be called after joining the room (joinRoom), and the configuration will be cleared after exit from the room.
 2.The configuration parameters in transcodingModeOptions are enabled if transcodingMode in transcodingCfg is equal to 0; Otherwise, they are disabled.
 */
- (int)setLiveTranscodingTask:(NSString* _Nonnull)taskId transcoding:(LiveTranscoding* _Nonnull)transcoding;

/**
 @brief Add stream publishing address for transcoding stream [one transcoding task supports a maximum of five stream publishing addresses]
 @param taskId [IN] ID of a transcoding task
 @param url [IN] Stream publishing address, in RTMP format; The value does not support special characters such as Chinese.
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface can be called after joining the room (joinRoom), and the configuration will be cleared after exit from the room.
 */
- (int)addPublishTranscodingStreamUrl:(NSString* _Nonnull)taskId url:(NSString* _Nonnull)url;

/**
 @brief Remove stream publishing address for transcoding stream
 @param taskId [IN] ID of a transcoding task
 @param url [IN] Stream publishing address to be removed
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface can be called after joining the room (joinRoom).
 1. Removal of a transcoding task does not remove the URL of the task, which needs to be removed by users;
 2. Addition of a stream publishing address does not require users to add a transcoding task first. Addition of a stream publishing address and addition of a transcoding task are independent of each other.
 */
- (int)removePublishTranscodingStreamUrl:(NSString* _Nonnull)taskId url:(NSString* _Nonnull)url;

/**
 @brief Remove a transcoding task
 @param taskId [IN] ID of a transcoding task, which is managed by users; value range: 0-9 a-z A-Z
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark
 1. Removal of a transcoding task does not remove the URL of the task, which needs to be removed by users;
 2. Addition of a stream publishing address does not require users to add a transcoding task first. Addition of a stream publishing address and addition of a transcoding task are independent of each other.
 */
- (int)removeLiveTranscodingTask:(NSString* _Nonnull)taskId;

/**
 @brief Subscribe to specified streams (cross-room).
 @param roomId [IN] Room number [only supporting the permutation and combination of characters such as [A, Z], [a, z], [0, 9], -, _, with the length of not more than 64 bytes.]
 @param uid [IN] User ID
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface can be called after joining the room, and the configuration will be cleared after exit from the room.
 */
- (int)addSubscribe:(NSString* _Nonnull)roomId uid:(NSString* _Nonnull)uid;

/**
 @brief Unsubscribe from streams
 @param roomId [IN] Room number [only supporting the permutation and combination of characters such as [A, Z], [a, z], [0, 9], -, _, with the length of not more than 64 bytes.]
 @param uid [IN] User ID
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface can be called after joining the room.
 */
- (int)removeSubscribe:(NSString* _Nonnull)roomId uid:(NSString* _Nonnull)uid;

/**
 @brief Set media mode
 @param [IN] mode Media mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization and before joining room; it is reset only when destroyEngine is called.
 */
- (int)setMediaMode:(ThunderRtcConfig)mode;

/**
 @brief Set room mode
 @param [IN] mode Room mode
 @return 0: Succeeded; For other errors, see enum ThunderRet.
 @remark The interface shall be called after initialization; it is reset only when destroyEngine is called.
 */
- (int)setRoomMode:(ThunderRtcRoomConfig)mode;

/**
 * @brief 启动/关闭啸叫检测
 * @param [IN] enabled true:启动啸叫检测；false:关闭啸叫检测；默认为false
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置，检测结果会通过onHowlingDetectResult通知
 */
- (int)enableHowlingDetector:(BOOL)enabled;

/**
 * @brief 启动/关闭漏回声检测
 * @param [IN] enabled true:启动漏回声检测；false:关闭漏回声检测；默认为false
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置，检测结果会通过onEchoDetectResult通知
 */
- (int)enableEchoDetector:(BOOL)enabled;

/**
 * @brief 启动采集设备检测
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置，检测结果会通过onAudioInputDeviceTest通知
 */
- (int)startInputDeviceTest;

/**
 * @brief 停止采集设备检测
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置
 */
- (int)stopInputDeviceTest;

/**
 * @brief 启动播放设备检测
 * @param filePath 音频文件路径
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置，检测结果会通过onAudioOutputDeviceTest通知
 */
- (int)startOutputDeviceTest:(NSString* _Nullable)filePath;

/**
 * @brief 停止播放设备检测
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置
 */
- (int)stopOutputDeviceTest;

/**
 * @brief 启动/关闭 麦克风采集 降噪功能
 * @param enabled true:开启 降噪； false:关闭降噪
 * @return 0:成功，其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置
 */
- (int) enableMicDenoise:(BOOL)enabled;

/**
 * @brief 查询当前是否开启/关闭 麦克风采集降噪功能
 * @return YES:当前已经开启降噪；NO：当前已经关闭降噪。 默认返回true
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置
 */
- (BOOL) isMicDenoiseEnabled;


/**
 * @brief 启动/关闭 音频自动增益功能
 * @param enabled true:开启 自动增益； false:关闭自动增益
 * @return 0:成功，其它错误参见enum ThunderRet
 * @remark 需要"初始化"后调用，仅在destroyEngine时重置
 */
- (int) enableAGC:(BOOL)enabled;

/**
 * @brief 设置语音音调M
 * @param pitch 语音音调，参数范围：[-12, 12]；默认值为0
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark pitch取值越小，则音调越低
 */
- (int)setVoicePitch:(float)pitch;

/**
 * @brief 摄像头是否打开
 * @return YES: 摄像头打开；NO: 摄像头没打开
 * @remark (1) 需要“初始化”后调用
 *        (2) 默认判断前置摄像头是否打开，如需判断后置摄像头请先调用switchFrontCamera进行切换
 */
- (BOOL)isCameraOpen;

/**
 * @brief 是否前置摄像头
 * @return YES: 是前置摄像头；NO: 是后置摄像头
 */
- (BOOL)isFrontCamera;

/**
 * @brief 摄像头方向查询
 * @return 返回摄像头的方向，具体的值参考ThunderVideoCaptureOrientation
 * @remark   (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
 *         (2) 默认判断前置摄像头，如需判断后置摄像头请先调用switchFrontCamera进行切换
 *         (3) 切换了摄像头(调用了switchFrontCamera)，需要重新判断
 */
- (ThunderVideoCaptureOrientation)getVideoCaptureOrientation;

/**
* @brief  摄像头是否支持缩放
* @return YES: 摄像头支持缩放；NO: 摄像头不支持缩放
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认判断前置摄像头，如需判断后置摄像头请先调用switchFrontCamera进行切换
*                 (3) 切换了摄像头(调用了switchFrontCamera)，需要重新调用
*/- (BOOL)isCameraZoomSupported;

/**
 * @brief 得到摄像头的最大缩放值
 * @return 调用成功返回最大的摄像头缩放值
 * @remark (1) 如果调用失败，返回-1
 *         (2) 默认前置摄像头，如需查询后置摄像头请先调用switchFrontCamera进行切换
 *         (3) 切换了摄像头(调用了switchFrontCamera)，需要重新调用
 */
- (float)getCameraMaxZoomFactor;

/**
* @brief 设置摄像头缩放比例
* @param [IN] zoomFactor 缩放比例
* @return 调用成功返回设置的缩放比例，如果设置失败返回值<0
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 如果设置的zoomFactor超过了最大的缩放值，则返回最大的缩放值
*                 (3) 如果设置的zoomFactor超过了最小的缩放值，则返回最小的缩放值
*                 (4) 默认设置前置摄像头，如需设置后置摄像头请先调用switchFrontCamera进行切换
*                 (5) 切换了摄像头(调用了switchFrontCamera)，需要重新设置
*/
- (CGFloat)setCameraZoomFactor:(CGFloat)zoomFactor;

/**
* @brief 摄像头是否支持人脸对焦功能
* @return YES: 摄像头支持人脸对焦功能；NO: 摄像头不支持人脸对焦功能
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认判断前置摄像头是否支持该功能，如需判断后置摄像头请先调用switchFrontCamera进行切换
*/
- (BOOL)isCameraAutoFocusFaceModeSupported;
 
/**
* @brief 开启/关闭人脸对焦功能
* @return 0:成功, 其它错误参见enum ThunderRet
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认设置前置摄像头，如需设置后置摄像头请先调用switchFrontCamera进行切换
*                 (3) 切换了摄像头(调用了switchFrontCamera)，需要重新设置
*                 (4) 成功调用该方法后，会触发onCameraFocusAreaChanged回调
*/
- (int)setCameraAutoFocusFaceModeEnabled:(BOOL)enabled;

/**
* @brief 设置摄像头对焦位置
* @param [IN] position 对焦位置，范围为:左上角(0,0)到右下角(1,1)，默认的位置为：画面中心((0.5,0.5)
* @return 0:成功, 其它错误参见enum ThunderRet
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 成功调用该方法后，会触发onCameraFocusAreaChanged回调
*                 (3) 默认设置前置摄像头，如需设置后置摄像头请先调用switchFrontCamera进行切换
*                 (4) 切换了摄像头(调用了switchFrontCamera)，需要重新设置
*                (5) 当检测到视频主体区域发生重大变化时，会自动调节对焦和曝光
*/
- (int)setCameraFocusPosition:(CGPoint)position;

/**
* @brief 设置摄像头曝光位置
* @param [IN] position 曝光位置，范围为:左上角(0,0)到右下角(1,1)，默认的位置为：画面中心((0.5,0.5)
* @return 0:成功, 其它错误参见enum ThunderRet
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 成功调用该方法后，会触发onCameraExposureAreaChanged回调
*                 (3) 默认设置前置摄像头，如需设置后置摄像头请先调用switchFrontCamera进行切换
*                 (4) 切换了摄像头(调用了switchFrontCamera)，需要重新设置
*                 (5) 当检测到视频主体区域发生重大变化时，会自动调节对焦和曝光
*/
- (int)setCameraExposurePosition:(CGPoint)position;

/**
* @brief 摄像头是否支持手电筒功能
* @return YES: 摄像头支持手电筒功能；NO: 摄像头不支持手电筒功能
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认判断前置摄像头，如需判断后置摄像头请先调用switchFrontCamera进行切换
*                 (3) 切换了摄像头(调用了switchFrontCamera)，需要重新判断
*/
- (BOOL)isCameraTorchSupported;
 
/**
 * @brief 开启/关闭摄像头手电筒功能
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark (1) 默认设置前置摄像头，如需设置后置摄像头请先调用switchFrontCamera进行切换
 *         (2) 切换了摄像头(调用了switchFrontCamera)，需要重新设置
 */
- (int)setCameraTorchOn:(BOOL)isOn;

/**
 * @brief 获取
 * @param [IN] config 具体的编码配置
 * @return 0:成功, 其它错误参见enum ThunderRet
 * @remark 需在"初始化"后调用
 */
- (ThunderVideoEncodeParam* _Nonnull) getVideoEncoderParam:(ThunderVideoEncoderConfiguration* _Nonnull)config;

/**
 @brief 查询网络连接状态
 @return 连接状态，参见enum ThunderConnectionStatus
 @remark 需在"初始化"后调用
 */
- (ThunderConnectionStatus)getConnectionStatus;

/**
* @brief 摄像头是否支持手动对焦
* @return YES: 摄像头支持手动对焦功能；NO: 摄像头不支持手动对焦功能
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认判断前置摄像头是否支持该功能，如需判断后置摄像头请先调用switchFrontCamera进行切换
*/
- (BOOL)isCameraManualFocusPositionSupported;

/**
* @brief 摄像头是否支持手动曝光
* @return YES: 摄像头支持手动曝光功能；NO: 摄像头不支持手动曝光功能
* @remark (1) 调用前需要先打开摄像头，可以通过isCameraOpen判断摄像头是否打开
*                 (2) 默认判断前置摄像头是否支持该功能，如需判断后置摄像头请先调用switchFrontCamera进行切换
*/
- (BOOL)isCameraManualExposurePositionSupported;

@end
