#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>

@interface FeedbackModule : RCTEventEmitter <RCTBridgeModule>

+ (instancetype _Nullable )sharedModule;

@end
