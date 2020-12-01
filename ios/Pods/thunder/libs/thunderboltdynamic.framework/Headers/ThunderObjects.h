#pragma once
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ThunderNetworkType)
{
  THUNDER_NETWORK_TYPE_UNKNOWN = 0, // Unknown network connection type
  THUNDER_NETWORK_TYPE_DISCONNECTED = 1, // The network has been disconnected
  THUNDER_NETWORK_TYPE_CABLE = 2, // Cable network
  THUNDER_NETWORK_TYPE_WIFI = 3, // Wi-Fi (hotspot included)
  THUNDER_NETWORK_TYPE_MOBILE = 4, // Mobile network. 2G, 3G and 4G network cannot be differentiated
  THUNDER_NETWORK_TYPE_MOBILE_2G = 5, // 2G mobile network
  THUNDER_NETWORK_TYPE_MOBILE_3G = 6, // 3G mobile network
  THUNDER_NETWORK_TYPE_MOBILE_4G = 7, // 4G mobile network
};

typedef NS_ENUM(NSInteger, ThunderPublishCDNErrorCode)
{
  THUNDER_PUBLISH_CDN_ERR_SUCCESS = 0, // Stream publishing succeeded
  THUNDER_PUBLISH_CDN_ERR_TOCDN_FAILED = 1, // Publishing stream to external server (CDN) is failed. 1. Check whether the URL is correct.
                                            // 2. Check whether the token in the URL is valid (generally, token is required during cdn stream publishing and can be ignored if it doe not exist).
  THUNDER_PUBLISH_CDN_ERR_THUNDERSERVER_FAILED = 2, // Publishing the stream to thunder internal server is failed.
                                                    // 1. Check the anchor uplink network, 2. Contact us to locate internal transmission faults.
  THUNDER_PUBLISH_CDN_ERR_THUNDERSERVER_STOP = 3, // Stop stream publishing
};

typedef NS_ENUM(NSInteger, ThunderTranscodingModeType)
{
  TRANSCODING_MODE_NON = 0,
  TRANSCODING_MODE_320X180 = 1,
  TRANSCODING_MODE_320X240 = 2,
  TRANSCODING_MODE_640X360 = 3,
  TRANSCODING_MODE_640X480 = 4,
  TRANSCODING_MODE_960X544 = 5,
  TRANSCODING_MODE_1280X720 = 6,
  TRANSCODING_MODE_1920X1080 = 7
};

__attribute__((visibility("default"))) @interface TranscodingUserObj : NSObject

@property(copy, nonatomic) NSString* uid; // Anchor ID
@property(copy, nonatomic) NSString* roomId; // Anchor’s current publish room
@property(assign, nonatomic) BOOL bStandard; // Standard stream user or not, default to false, competition stream is generally regarded as standard stream in a competition scenario
@property(assign, nonatomic) int layoutX; // User’s x coordinate of the begin point in video mixing canvas
@property(assign, nonatomic) int layoutY; // User’s y coordinate of the begin point in video mixing canvas
@property(assign, nonatomic) int layoutW; // User’s width in video mixing canvas
@property(assign, nonatomic) int layoutH; // User’s height in video mixing canvas
@property(assign, nonatomic) int zOrder; // Layer number of user frame on the live video.
                                         // The value range is the integer in [0, 100], and the minimum value is 0 (default value), indicating that the image in this region is at the lowest level
@property(assign, nonatomic) BOOL bCrop; // The way in which the source stream adapts to the video mixing window
                                         // true: crop extra parts after zooming; false: mend black edge after zooming; this is applied to the crop region if such a region is set.
@property(assign, nonatomic) int cropX; // X coordinate of the begin point in the crop region of current anchor’s source video
@property(assign, nonatomic) int cropY; // Y coordinate of the begin point in the crop region of current anchor’s source video
@property(assign, nonatomic) int cropW; // Width of the crop region of current anchor’s source video
@property(assign, nonatomic) int cropH; // Height of the crop region of current anchor’s source video
@property(assign, nonatomic) float alpha; // Transparency of user video on the live video. The value range is [0.0, 1.0].
                                          // 0.0 indicates that the image in this region is completely transparent, while 1.0 indicates completely opaque. The default is 1.0
@property(assign, nonatomic) int audioChannel; // Not yet realized

- (NSString*)description;
- (BOOL)isEqual:(id)obj;

@end

__attribute__((visibility("default"))) @interface MediaStreamLayoutObj : NSObject

@property(assign, nonatomic) int layoutX; // X coordinate of begin point of the media in video mixing canvas
@property(assign, nonatomic) int layoutY; // Y coordinate of begin point of the media in video mixing canvas
@property(assign, nonatomic) int layoutW; // Width of the media in video mixing canvas
@property(assign, nonatomic) int layoutH; // Height of the media in video mixing canvas
@property(assign, nonatomic) int zOrder; // Layer number of the media video frame on the live video. The value range is the integer in [0, 100],
                                         // and the minimum value is 0 (default value), indicating that the image in this region is at the lowest level
@property(assign, nonatomic) BOOL bCrop; // The way in which the source stream adapts to the video mixing window, true: crop extra parts after zooming;
                                         // false: mend black edge after zooming; this is applied to the crop region if such a region is set.
@property(assign, nonatomic) int cropX; // X coordinate of the begin point in the crop region of current anchor’s source video
@property(assign, nonatomic) int cropY; // Y coordinate of the begin point in the crop region of current anchor’s source video
@property(assign, nonatomic) int cropW; // Width of the crop region of current anchor’s source video
@property(assign, nonatomic) int cropH; // Height of the crop region of current anchor’s source video
@property(assign, nonatomic) float alpha; // Transparency of media video on the live video. The value range is [0.0, 1.0].
                                          // 0.0 indicates that the image in this region is completely transparent, while 1.0 indicates completely opaque. The default is 1.0
@property(assign, nonatomic) int audioChannel; // Not yet realized

- (NSString*)description;
- (BOOL)isEqual:(id)obj;

@end

__attribute__((visibility("default"))) @interface TranscodingImage : NSObject

@property(assign, nonatomic) int x; // 以左上角为原点横轴坐标,默认0
@property(assign, nonatomic) int y; // 以左上角为原点纵轴坐标,默认0
@property(assign, nonatomic) int width; // 图片宽,默认0
@property(assign, nonatomic) int height; // 图片高,默认0
@property(copy, nonatomic) NSString* url; // 图片url地址,默认空值
@property(assign, nonatomic) int scale; // 缩放/裁剪模式,参考TranscodingImageScaleType,默认TRANSCODING_IMAGESCALE_RATIO_TYPE
@property(assign, nonatomic) float alpha; // 透明度,取值范围为[0.0, 1.0],0.0完全透明,1.0完全不透明,默认1.0

@end

__attribute__((visibility("default"))) @interface TranscodingTimestamp : NSObject

@property(assign, nonatomic) int x; // 以左上角为原点横轴坐标,默认0
@property(assign, nonatomic) int y; // 以左上角为原点纵轴坐标,默认0
@property(copy, nonatomic) NSString* format; // 支持posix时间格式显示格式,默认空值,比如:
                                             // %Y/%m/%d: 2020/01/01
                                             // %Y-%m-%d: 2020-01-01
                                             // %H:%M:%S: 13:00:00
                                             // %Y/%m/%d %H:%M:%S: 2020/01/01 13:00:00
                                             // %Y-%m-%d %H:%M:%S: 2020-01-01 13:00:00
@property(copy, nonatomic) NSString* font; // 字体,目前仅支持NotoSansCJK一种字体,默认空值
@property(assign, nonatomic) int size; // 字体大小,默认0
@property(assign, nonatomic) int color; // 字体颜色,RGB定义下的Hex值,默认值黑色#000000
@property(assign, nonatomic) int backgroundColor; // 背景色,RGB定义下的Hex值,默认值-1表示不设置背景色
@property(assign, nonatomic) float alpha; // 透明度,取值范围为[0.0, 1.0],0.0完全透明,1.0完全不透明,默认1.0

@end

__attribute__((visibility("default"))) @interface TranscodingText : NSObject

@property(assign, nonatomic) int x; // 以左上角为原点横轴坐标,默认0
@property(assign, nonatomic) int y; // 以左上角为原点纵轴坐标,默认0
@property(copy, nonatomic) NSString* content; // 文字内容,默认空值
@property(copy, nonatomic) NSString* font; // 字体,目前仅支持NotoSansCJK一种字体,默认空值
@property(assign, nonatomic) int size; // 字体大小,默认0
@property(assign, nonatomic) int color; // 字体颜色,RGB定义下的Hex值,默认值黑色#000000
@property(assign, nonatomic) int backgroundColor; // 背景色,RGB定义下的Hex值,默认值-1表示不设置背景色
@property(assign, nonatomic) float alpha; // 透明度,取值范围为[0.0, 1.0],0.0完全透明,1.0完全不透明,默认1.0

@end

typedef NS_ENUM(NSInteger, ThunderAudioCodecType)
{
    ThunderAudioCodecTypeUNKNOW   = 0,
    ThunderAudioCodecTypeEAACPlus = 1,
    ThunderAudioCodecTypeAAC      = 2,
};
 
typedef NS_ENUM(NSInteger, ThunderAudioSample)
{
    ThunderAudioSample32000    = 32000,
    ThunderAudioSample44100    = 44100,
    ThunderAudioSample48000    = 48000,
};

//Encoding type of videos
typedef NS_ENUM(NSInteger, ThunderVideoCodecType)
{
    ThunderVideoCodecTypeUNKNOW   = 0,
    ThunderVideoCodecTypeVP8      = 1,
    ThunderVideoCodecTypeH264     = 2,
    ThunderVideoCodecTypeH265     = 3,
};

__attribute__((visibility("default"))) @interface CustomTranscodingOptions : NSObject
 
@property (assign, nonatomic) ThunderVideoCodecType videoCodecType; // Encoding type: H264 or H265
@property(assign, nonatomic) int videoBitrate; // Video bitrate (required for video streams), range: (0,10000], unit: kbps
@property(assign, nonatomic)  int videoFps; // Video frame rate (required for video streams)，range: (0,60]
@property(assign, nonatomic) int videoGop; // Video GOP in frames (required for video streams), which is a multiple of fps (If the set value does not meet this condition, gop will be rounded up to the next multiple of fps); range: (0,200], unit: fps
@property(assign, nonatomic) int videoHeight; // Video height (required for video streams), which should be mutiples of 4, range: (0,1920]
@property(assign, nonatomic) int videoWidth;  // Video width (required for video streams), which should be mutiples of 4, range: (0,1920]
@property(assign, nonatomic) ThunderAudioCodecType audioCodecType; // Audio encoding type：AAC / eAAC+，default value:0
@property(assign, nonatomic) ThunderAudioSample audioSample; // Audio sampling rate：32kHz/44.1kHz / 48kHz，default value:44.1kHz
@property(assign, nonatomic) int audioBitrate; // Audio bit rate：default value：64kbps，range: [24，192]
@property(assign, nonatomic) int audioChannel; // Audio channel：range: [1,2]，1 - mono channel, 2 - stereo,default value:2,Audio in EAAC + format does not support mono channel


@end

__attribute__((visibility("default"))) @interface LiveTranscoding : NSObject
// @property(nonatomic, strong)NSMutableDictionary *mExtendInfo;
@property(nonatomic, strong)NSString *mAudioUrl; // URL of the standard audio file; support audio files in Mp3 format
@property(nonatomic, strong)NSString *mLyricUrl; // URL of lyric in LRC format, and the lyric file should be encoded in UTF-8 format.
                                                 // If this field is not configured, the audio will be played without lyrics;
                                                 // Otherwise, the lyrics will be added to the mixed video in the default style.
@property(nonatomic, strong)NSString *mMediaUrl; // Video file url as standard
@property(nonatomic, strong)MediaStreamLayoutObj* mMediaStreamLayout; // Layout of video standard stream in video mixing.

/**
 @brief Add a user to the video mixing layout
 @param [IN] user See TranscodingUser
 @return 0 Succeeded
 */
- (int)addUser:(TranscodingUserObj*)user;

/**
 @brief Set video mixing layout of users in batches
        This method is used to set all users who participate in image integration. With this method, the new user data is used to replace the original data. 
 @param [IN] users All video mixing users in the channel
 */
- (void)setUsers:(NSMutableArray*)users;

/**
 @brief Obtain the information about the current user location
 @return Obtain the information about all users in the channel in video mixing canvas
 */
- (NSMutableArray*)getUsers;

/**
 @brief Delete the users who participate in video mixing
 @param [IN] uid ID of the user to be deleted
 @return 0 Succeeded
 */
- (int)removeUserWithUid:(NSString*)uid;

/**
 @brief Delete video mixing of the channel, that is, users do not use video mixing any more.
 @return 0 Succeeded
 */
- (int)removeAllUsers;

/**
 @brief Obtain the number of people who participated in video mixing
 @return Number of people
 */
- (int)getUserCount;

/**
 @brief Set Mixed Video Parameters
 @param [IN] options Mixed Video Parameters
*/
- (void)setCustomTranscodingOptions:(CustomTranscodingOptions*)options;

/**
 @brief Obtain Mixed Video Parameters
 @return Mixed Video Parameters
*/
- (CustomTranscodingOptions*)getCustomTranscodingOptions;

/**
 @brief Set the bracket of the output video mixing
 @param [IN] transCodingMode mode
*/
- (void)setTransCodingMode:(ThunderTranscodingModeType)transCodingMode;

/**
 @brief Obtain the bracket of the output video mixing
 @return mode
 */
- (ThunderTranscodingModeType)getTransCodingMode;

/**
 * @brief set live trancoding video background
 * @param color rgb值
 */
- (void)setBackgroundColor:(int)color;

/**
 * @brief obtain live transcoding output video background color
 * @return color value
 */
- (int)getBackgroundColor;

/**
 * @brief set live transcoding video background image
 * @param image include image url and scale
 */
- (void)setBackgroundImage:(TranscodingImage*)image;

/**
 * @brief obtain live transcoding output video background image
 * @return ThunderBoltImage contains url and scale information
 */
- (TranscodingImage*)getBackgroundImage;

/**
 * @brief set live transcoding video timestamp
 * @param timestamp watermark
 */
- (void)setTimestamp:(TranscodingTimestamp*)timestamp;

/**
 * @brief obtain live transcoding video timestamp
 * @return ThunderBoltTimestamp contains format etc.
 */
- (TranscodingTimestamp*)getTimestamp;

/**
 * @brief Set video watermark text
 *        This method is used to set text who participate in image integration. With this method, the new text data is used to replace the original data.
 * @param [IN] text one video mixing text in the channel
 */
- (void)addText:(TranscodingText*)text;

/**
 * @brief Set video watermark texts in batches
 *        This method is used to set all texts who participate in image integration. With this method, the new text data is used to replace the original data.
 * @param [IN] texts All video mixing texts in the channel
 */
- (void)setTexts:(NSMutableArray*)texts;

/**
 * @brief Obtain the information about the text information
 * @return Obtain the information about all texts in the channel in video mixing canvas
 */
- (NSMutableArray*)getTexts;

/**
 * @brief Delete video mixing of the channel, that is, texts do not use video mixing any more.
 * @return 0 Succeeded
 */
- (int)removeAllTexts;

/**
 * @brief Obtain the number of texts participated in video mixing
 * @return Number of texts
 */
- (int)getTextCount;

/**
 * @brief Set video watermark image in batches
 *        This method is used to set text who participate in image integration. With this method, the new text data is used to replace the original data.
 * @param [IN] image one video mixing text in the channel
 */
- (void)addImage:(TranscodingImage*)image;

/**
 * @brief Set video watermark images in batches
 *        This method is used to set all texts who participate in image integration. With this method, the new text data is used to replace the original data.
 * @param [IN] images All video mixing texts in the channel
 */
- (void)setImages:(NSMutableArray*)images;

/**
 * @brief Obtain the information about the image information
 * @return Obtain the information about all images in the channel in video mixing canvas
 */
- (NSMutableArray*)getImages;

/**
 * @brief Delete video mixing of the channel, that is, images do not use video mixing any more.
 * @return 0 Succeeded
 */
- (int)removeAllImages;

/**
 * @brief Obtain the number of images participated in video mixing
 * @return Number of images
 */
- (int)getImageCount;

/**
 @brief Return whether to enable video mixing with media extra information
 @return true: Enable; false: Disable
*/
- (BOOL)isEnableMixVideoExtraInfo;

/**
 @brief Set whether external audio URL is mixed video standard stream The play progress of the standard stream is required for video mixing synchronization internally, and interface setMediaStandardSream cannot be used at the same time. Therefore, the client is required to play this audio using ThunderAudioFilePlayer and to call setMixStandard in ThunderAudioFilePlayer to set the standard stream. 
   If users want to use custom-style lyrics in mixed videos, the anchor terminal may send the lyrics progress using the sendMediaExtraInfo interface and call setAudioOnlyStandardSreamUrl to set lyricUrl to null.
   The audience terminal will be able to receive the callback on IThunderMediaExtraInfoCallback onRecvMediaExtraInfo when playing this mixed video stream. Then, the audience terminal reads the corresponding lyrics progress and renders lyrics according to the progress.
 @param [IN] audioUrl URL of the benchmark audio file
 @param [IN] lyricUrl URL of the lyrics file corresponding to the audio; blank indicates that there is no lyrics. Otherwise, the lyrics will be added to the mixed video in the default style. 
 @return 0: Succeeded; <0: Failed
*/
- (int)setAudioOnlyStandardSreamUrl:(NSString*)audioUrl lyricUrl:(NSString*)lyricUrl;

/**
 @brief Set the external video media stream as a standard stream for video mixing; the interface setAudioOnlyStandardSreamUrl cannot be used at the same time..
 @param [IN] mediaUrl URL of the benchmark video file
 @param [IN] layout  Layout information about the video media stream in video mixing 
 @return 0: Succeeded; <0: Failed
*/
- (int)setMediaStandardSream:(NSString*) mediaUrl layout:(MediaStreamLayoutObj*) layout;

- (NSString*)description;

@end

typedef NS_ENUM(NSInteger, ThunderAudioDeviceStatus)
{
  THUNDER_AUDIO_DEVICE_STATUS_INIT_CAPTURE_SUCCESS = 0, // Callback on successful initialization of audio capture device
  THUNDER_AUDIO_DEVICE_STATUS_INIT_CAPTURE_ERROR_OR_NO_PERMISSION = 1, // Callback on initialization failure of audio capture. It may be caused by no permission
  THUNDER_AUDIO_DEVICE_STATUS_RELEASE_CAPTURE_SUCCESS = 2, // Callback on successful release of audio capture device
};

NS_ASSUME_NONNULL_END
