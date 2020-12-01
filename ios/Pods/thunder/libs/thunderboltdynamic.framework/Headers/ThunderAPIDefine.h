#pragma once
#import <Foundation/Foundation.h>
/**
 * @typedef
 * @brief Enumeration of types of error codes returned by interface
 */
typedef enum
{
  // Error code returned from the synchronization interface [-1 ~ -1000]
  THUNDER_RET_SUCCESS = 0, // Processing succeeded
  THUNDER_RET_NOT_INITIALIZED = -1, // Not initialized
  THUNDER_RET_WRONG_INIT_STATUS = -2, // A wrong initialization status. Before the initialization or destroying is finished, this error will be returned back when this interface is called.
  THUNDER_RET_NO_JOIN_ROOM = -3, // Not joining a room [If the interface only can be called after joining room, the error will be returned if the interface is called before joining room]
  THUNDER_RET_ALREADY_JOIN_ROOM = -4, // Already joining a room [If a interface is only called before joining room, the error will be returned when this interface is called after joining room]
  THUNDER_RET_WRONG_JOIN_STATUS = -5, // A wrong joining status. Before room joining or room quitting is finished, this error will be returned back when this interface is called.
  THUNDER_RET_NOT_IN_THUNDER = -6, // Not in a Thunder mode (This error will be returned back only if an interface called by Thunder is called in a ThunderBolt mode)
  THUNDER_RET_NOT_IN_THUNDERBOLT = -7, // Not in a ThunderBolt mode (This error will be returned back only if an interface called by ThunderBolt is called in a Thunder mode)
  THUNDER_RET_INVALID_UID = -8, // Invalid uid
  THUNDER_RET_INVALID_ROOMID = -9, // Invalid roomId
  THUNDER_RET_INVALID_URL = -10, // Invalid url
  THUNDER_RET_INVALID_TASKID = -11, // Invalid task
  THUNDER_RET_CAPACITY_LIMIT = -12, // SDK capacity limit (super-threshold of a stream publishing address)
  THUNDER_RET_INVALID_ARGUMENT = -13, // Invalid parameters (when necessary parameters are null or illegal)
  THUNDER_RET_START_AUDIO_CAPTURE_ERR = -14, // Error in starting audio capture
  THUNDER_RET_NO_START_AUDIO_CAPTURE = -15, // Not starting audio capture. In the case of not enabling capture, this error will be returned when external data is pushed.
  THUNDER_RET_ALREADY_START_AUDIO_CAPTURE = -16, // Already starting audio capture. This error will be returned when resetting is executed during capturing.
  THUNDER_RET_NO_START_AUDIO_PUBLISH = -17, // Not starting audio publishing. In the case of not starting publishing, this error will be returned when external data is pushed.
  THUNDER_RET_ALREADY_START_AUDIO_ENCODE = -18, // Already starting audio capture. This error will be returned when parameters are reset during capturing.
  THUNDER_RET_ALREADY_START_AUDIO_PUBLISH = -19, // Already starting audio publishing. This error will be returned when parameters are reset during capturing.
  THUNDER_RET_NOT_ON_FRONT_CAMERA = -20, // This error will be returned if a camera mirror is set on a rear camera.
  THUNDER_RET_NOT_ON_MULTI_TYPE = -21, // When a multi-user microphone connection layout is set, this error will be returned if a remote play type is set before users join a room.
  THUNDER_RET_INVALID_SEATINDEX = -22, // This error will be returned when the preset seat number for multi-user microphone connection exceeds a layout setting range.
  THUNDER_RET_WRONG_AUDIO_CAPTURE_TYPE = -23, // 错误的音频采集类型
  THUNDER_RET_ALREADY_START_CUSTOM_AUDIO = -24, // 已启动外部音频推流
  THUNDER_RET_CALL_TOO_FREQUENT = -25, // 接口调用太频繁
  THUNDER_RET_NOT_CUSTOM_AUDIO_SOURCE = -26, // 不是外部音频推流源
  THUNDER_RET_INVALID_VIDEO_STREAM_TYPE = -27, // 错误视频流类型
  THUNDER_RET_ALREADY_START_VIDEO_PUBLISH = -28, // 已启动视频开播，设置发送端大小流模式开播必须在视频开播之前
  THUNDER_RET_START_AUDIO_ENCODE_ERR = -29, // Error starting audio encoding
  THUNDER_RET_ALREADY_START_VIDEO_CAPTURE = -30, // Video capture has started

  // Video mixing related [-101 ~ -200]
  THUNDER_RET_INVALID_TRANSCODING_MODE = 101, // Invalid transcodingMode

  // Warning codes returned asynchronously [-1001 ~ -2000]

  // Error codes returned asynchronously [-2001 ~ -3000]
  THUNDER_NOTIFY_JOIN_FAIL = -2001, // Notifying that room joining fails when SDK does not receive services due to network (SDK will execute room quitting operation if the room joining fails)

  // Error codes used in the audio library [-3001 ~ -4000]
  THUNDER_RET_AUDIO_ENGINE_ERROR = -3001, // Returning an audio engine error. It is required to check logs for specific reasons.
  THUNDER_RET_AUDIO_DISABLE_VOICE_POSITION = -3002, // Not enabling voice stereo of remote users.
  THUNDER_RET_AUDIO_PUBLISH_MODE_NONE = -3003, // When SourceType is THUNDER_PUBLISH_MODE_NONE and is used to publish, this error will be returned.

  // Error codes used in the video library [-4001 ~ -5000]
  THUNDER_RET_VIDEO_ENGINE_ERROR = -4001, // Returning a video engine error. It is required to check logs for specific reasons.

  // Error codes used in the transmission library [-5001 ~ -6000]
  THUNDER_RET_TRANS_ENGINE_ERROR = -5001, // Returning a transfer engine error. It is required to check logs for specific reasons.

  // Error codes used in the configuration library (argo) [-6001 ~ -7000]
  THUNDER_RET_ARGO_ENGINE_ERROR = -6001, // Returning a configuration engine error. It is required to check logs for specific reasons.

  // Error codes used in the SEVICE library [-7001 ~ -8000]
  THUNDER_RET_SERVICE_ENGINE_ERROR = -7001, // Returning a SERVICE engine error. It is required to check logs for specific reasons.

  // Error codes used in the LOG library [-8001 ~ -9000]
  THUNDER_RET_LOG_ENGINE_ERROR = -8001, // Returning a log engine error. It is required to check logs for specific reasons.
}ThunderRet;

/**
 @typedef
 @brief Area
 */
typedef enum
{
  THUNDERAREA_DEFAULT = 0, // Default value (domestic)
  THUNDERAREA_RUSSIA = 1, // Russia
  THUNDERAREA_MALAYSIA = 2, // Malaysia
  THUNDERAREA_FOREIGN = 100, // Overseas
  THUNDERAREA_RESERVED = 101, // reserved
} ThunderAreaType;

/**
 @typedef
 @brief Userâ€™s role
 */
typedef enum
{
  THUNDERUSER_ROLE_AUDIENCE = 0, // Only audience
  THUNDERUSER_ROLE_ANCHOR = 1 // If the audience interacts with the anchor, it will become an anchor
} ThunderUserRole;

/**
 @typedef
 @brief Log level
 */
typedef enum
{
  THUNDERLOG_LEVEL_TRACE = 0,
  THUNDERLOG_LEVEL_DEBUG = 1,
  THUNDERLOG_LEVEL_INFO = 2,
  THUNDERLOG_LEVEL_WARN = 3,
  THUNDERLOG_LEVEL_ERROR = 4,
  THUNDERLOG_LEVEL_RELEASE = 10,
} ThunderLogLevel;


#pragma mark --Publish
/**
 @typedef
 @brief Publishing method
 */
typedef enum
{
  THUNDERPUBLISH_PLAY_SINGLE = 0, // Single publishing
  THUNDERPUBLISH_PLAY_INTERACT = 1, // Microphone-connection video publishing
  THUNDERPUBLISH_PLAY_SCREENCAP = 2, // Screen recording publishing
  THUNDERPUBLISH_PLAY_MULTI_INTERACT = 3, // Multi-person microphone connection publishing
} ThunderPublishPlayType;

/**
 * @typedef
 * @brief Video encoding type
 */
typedef enum
{
  THUNDERPUBLISH_VIDEO_MODE_DEFAULT = -1, // Undefined. The broadcast definition is determined by configuration
  THUNDERPUBLISH_VIDEO_MODE_NORMAL = 1, // Ordinary
  THUNDERPUBLISH_VIDEO_MODE_HIGHQULITY = 2, // High definition
  THUNDERPUBLISH_VIDEO_MODE_SUPERQULITY = 3, // Ultra definition
  THUNDERPUBLISH_VIDEO_MODE_BLUERAY_2M = 4, // Blue ray 2M
  THUNDERPUBLISH_VIDEO_MODE_BLUERAY_4M = 5, // Blue ray 4M
  THUNDERPUBLISH_VIDEO_MODE_BLUERAY_6M = 6, // Blue ray 6M
  THUNDERPUBLISH_VIDEO_MODE_BLUERAY_8M = 7, // Blue ray 8M
  THUNDERPUBLISH_VIDEO_MODE_FLUENCY = 8, // Fluent
} ThunderPublishVideoMode;

/**
 * @typedef
 * @brief Video publishing in portrait or landscape orientation
 */
typedef enum
{
  THUNDERVIDEO_PUBLISH_VIDEO_ORIENTATION_PORTRAIT = 0,  // Portrait
  THUNDERVIDEO_PUBLISH_VIDEO_ORIENTATION_LANDSPACE = 1, // Landscape
}ThunderPublishVideoScreenOrientation;

#pragma mark --Player
/**
 * @typedef
 * @brief Video rendering mode
 */
typedef enum
{
    THUNDER_VIDEOVIEW_SCALE_MODE_FILL = 0,
    THUNDER_VIDEOVIEW_SCALE_MODE_ASPECT_FIT = 1,
    THUNDER_VIDEOVIEW_SCALE_MODE_CLIP_TO_BOUNDS = 2,
} ThunderVideoViewScaleMode;

/**
 * @typedef
 * @brief Video data format
 */
typedef enum
{
  THUNDERVIDEO_DATA_FORMAT_YUVI420 = 0,
  THUNDERVIDEO_DATA_FORMAT_H264 = 1,
} ThunderVideoDataFormat __attribute__((deprecated("enumeration to be deprecated")));

/**
 * @typedef
 * @brief Video definition
 */
typedef enum
{
  THUNDERVIDEO_LEVEL_NORMAL = 1, /*! Ordinary */
  THUNDERVIDEO_LEVEL_HIGHQULITY = 2, /*! High definition */
  THUNDERVIDEO_LEVEL_SUPERQULITY = 3, /*! Ultra definition */
  THUNDERVIDEO_LEVEL_BLUERAY_2M = 4, /*! Blue ray 2M */
  THUNDERVIDEO_LEVEL_BLUERAY_4M = 5, /*! Blue ray 4M */
  THUNDERVIDEO_LEVEL_BLUERAY_6M = 6, /*! Blue ray 6M */
  THUNDERVIDEO_LEVEL_BLUERAY_8M = 7, /*! Blue ray 8M */
} ThunderVideoLevel __attribute__((deprecated("enumeration to be deprecated")));

/*!
 * @typedef
 * @brief Flash mode
 */
typedef enum
{
  THUNDERPUBLISH_CAPTURE_TORCH_MODE_OFF = 0,
  THUNDERPUBLISH_CAPTURE_TORCH_MODE_ON = 1,
  THUNDERPUBLISH_CAPTURE_TORCH_MODE_AUTO = 2,
} ThunderPlubishCaptureTorchMode __attribute__((deprecated("enumeration to be deprecated")));

/*!
@typedef
*/
// Clockwise rotation angle of video. If the angle is set as other numbers, the system will ignore it automatically.
typedef NS_ENUM(NSInteger, ThunderVideoRotation)
{
  THUNDER_VIDEO_ROTAION_NONE = 0, // Rotate 0 degree clockwise
  THUNDER_VIDEO_ROTAION_90 = 1, // Rotate 90 degree clockwise
  THUNDER_VIDEO_ROTAION_180 = 2, // Rotate 180 degree clockwise
  THUNDER_VIDEO_ROTAION_270 = 3, // Rotate 270 degree clockwise
};

/*!
@typedef
*/
// Image format
typedef NS_ENUM(NSInteger, ThunderVideoPixelFormat)
{
  THUNDER_VIDEO_PIXELFORMAT_I420 = 0,
  THUNDER_VIDEO_PIXELFORMAT_BGRA = 1,
  THUNDER_VIDEO_PIXELFORMAT_NV12 = 2,
};

/*!
@typedef
*/
// Buffer type
typedef NS_ENUM(NSInteger, ThunderVideoBufferType)
{
  THUNDER_VIDEOBUFFER_TYPE_PIXELBUFFER = 1, // Buffer using Pixel Buffer type
  THUNDER_VIDEOBUFFER_TYPE_RAWDATA = 2, // Buffer using Raw Data type
};

/*!
@typedef
*/
// video capture type
typedef enum
{
  THUNDER_CAPTURE_TYPE_DEFAULT_CAMERA = 0, // Camera
  THUNDER_CAPTURE_TYPE_SCREEN_RECORD = 1, // Screen recording
  THUNDER_CAPTURE_TYPE_EXTERNAL_SOURCE = 2, // External stream publishing yuv
}LiveEngineCaptureType __attribute__((deprecated("enumeration to be deprecated")));
