#pragma once
#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <AVFoundation/AVFoundation.h>
#import "ThunderAPIDefine.h"

/**
 @protocol
 @brief Interface for pushing video data
 @remark
 The [ThunderVideoCaptureProtocol startCapture] interface provides a ThunderVideoPublisherProtocol object to the external;
 The object calls the pushing interface to push external video data.
 */
__attribute__((visibility("default"))) @protocol ThunderVideoPublisherProtocol <NSObject>

@required

/**
 @brief Interface for pushing raw video data
 @param [IN] pixelBuffer Raw video data (one frame)
 @param [IN] pts The current frame displays the system time, in unit of ms.
 */
- (void)pushVideoData:(nonnull CVPixelBufferRef)pixelBuffer pts:(int64_t)pts;

/**
 @brief Interface for pushing encoded video data
 @param [IN] encodedData Encoded video data (one frame)
 @param [IN] format Video encoding format
 @param [IN] dts System time when the current frame is encoded; unit: ms
 @param [IN] pts System time when the current frame is displayed; unit: ms
 */
//- (void)pushVideoData:(NSData*)encodedData format:(ThunderVideoDataFormat)format dts:(int64_t)dts pts:(int64_t)pts;

/**
 @brief Interface for external stream publishing data (screen recording)
 @param [IN] sampleBuffer Video data of external stream publishing
 */
- (void)pushExtVideoData:(nonnull CMSampleBufferRef)sampleBuffer;

@optional
/**
 @brief Interface for pushing raw video data
 @param [IN] pixelBuffer Raw video data (one frame)
 @param [IN] pts System time when the current frame is displayed; unit: ms
 @param [IN] rotation Clockwise rotation angle
 */
- (void)pushVideoData:(nonnull CVPixelBufferRef)pixelBuffer pts:(int64_t)pts rotation:(ThunderVideoRotation)rotation;


/**
 @brief Interface for pushing raw video data
 @param [IN] rawData Raw video data (one frame)
 @param [IN] pts Set a timestamp for each video frame
 @param [IN] format Image format
 @param [IN] size Size of video naked data
 @param [IN] rotation Clockwise rotation angle for video
 */
- (void)pushRawData:(void *_Nonnull)rawData
                pts:(int64_t)pts
                format:(ThunderVideoPixelFormat)format
                size:(CGSize)size
                rotation:(ThunderVideoRotation)rotation;

@end

/**
 @protocol
 @brief Interface for implementing video capture
 */
__attribute__((visibility("default"))) @protocol ThunderVideoCaptureProtocol <NSObject>

@required

/**
 @brief Start capturing
 @param [IN] protocol Interface for pushing data @see ThunderVideoPublisherProtocol
 */
- (void)startCapture:(nullable id<ThunderVideoPublisherProtocol>)protocol;

/**
 @brief End capturing
 */
- (void)stopCapture;

@end

/**
 @protocol
 @brief Callback delegate on audio data 
 */
__attribute__((visibility("default"))) @protocol ThunderDefaultCameraDataDelegate <NSObject>

@required

/**
 @brief Callback interface for video data
 @param [OUT] pixelBuffer Raw video data
 @param [OUT] pts Capture time of the current frame
 */
- (void)onVideoDataCallback:(nonnull CVPixelBufferRef)pixelBuffer pts:(int64_t)pts;

@end

/**
 @class
 @brief Default camera capture object of SDK
 */
__attribute__((visibility("default"))) @interface ThunderDefaultCamera : NSObject <ThunderVideoCaptureProtocol>

- (nonnull instancetype)initWithOrientation:(ThunderPublishVideoScreenOrientation) orientation
                            CapturePosition:(AVCaptureDevicePosition)position;

/**
 @brief Set callback on camera capture data
 @param [IN] delegate Callback on video data
 @remark
 After callback on camera data is set, the [ThunderDefaultCamera pushCameraDataBack:pts:] interface shall be called to send data back to the SDK after data is processed.
 */
- (void)setCameraDataCallback:(nullable id<ThunderDefaultCameraDataDelegate>)delegate;

/**
 @brief The callback video data is sent back to the SDK via this result after being processed.
 @param [OUT] pixelBuffer Raw video data
 @param [OUT] pts Capture time of the current frame
 */
- (void)pushCameraDataBack:(nonnull CVPixelBufferRef)pixelBuffer pts:(int64_t)pts;

/**
 @brief Obtain externally configured callbacks on data captured by camera
 @return Externally configured data callbacks
 */
- (nullable id<ThunderDefaultCameraDataDelegate>)getCameraDataCallback;


/**
 @brief Set portrait/landscape of stream publishing
 @param [IN] orientation Portrait; enumeration type
 */
- (void)setPublishVideoOrientation:(ThunderPublishVideoScreenOrientation)orientation;

/**
 @brief Obtain portrait/landscape of stream publishing previously set
 @return Portrait; enumeration type
 */
- (ThunderPublishVideoScreenOrientation) getPublishVideoOrientation;


/**
 @brief Set front and rear cameras
 @param [IN] capturePosition Front and rear cameras; enumeration
 */
- (void)setCapturePosition:(AVCaptureDevicePosition)capturePosition;


/**
 @brief Obtain the configured front and rear cameras
 @return Front and rear cameras; enumeration
 */
- (AVCaptureDevicePosition) getCapturePosition;

@end

/*
 @brief Test code; the service terminal is required to implement similar classes; data of external stream publishing; video
 */
__attribute__((visibility("default"))) @interface ThunderScreenCapture : NSObject <ThunderVideoCaptureProtocol>
- (void)pushScreenData:(nonnull CMSampleBufferRef)sampleBuffer;
@end
