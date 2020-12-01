
#import "FeedbackModule.h"
#import <SSZipArchive.h>
#import "AFNetworking.h"
#import "crashreport.h"


@interface FeedbackModule()

@end

@implementation FeedbackModule

RCT_EXPORT_MODULE();
#define kLogFilePath [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/rnthunderbolt"]

+ (instancetype)sharedModule
{
    static FeedbackModule* module = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        module = [[FeedbackModule alloc] init];
    });
    return module;
}

RCT_EXPORT_METHOD(getLogPath :(NSDictionary *)options resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
  resolve(kLogFilePath);
}

RCT_EXPORT_METHOD(crashTest:(NSDictionary *)options resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
  [[CrashReport sharedObject] testCrash];
}

RCT_EXPORT_METHOD(getAppVersionName:(NSDictionary *)options resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
  NSDictionary *infoDic = [[NSBundle mainBundle] infoDictionary];
  NSString *appVersion = [NSString stringWithFormat:@"%@-%@", [infoDic objectForKey:@"CFBundleShortVersionString"], [infoDic objectForKey:@"CFBundleVersion"]];
  resolve(appVersion);
}

RCT_EXPORT_METHOD(getABI:(NSDictionary *)options resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
  resolve(@"");
}


//提交意见反馈
RCT_EXPORT_METHOD(doFeedback:(NSDictionary *)options resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
  NSString *appId = @"RtcRNdemo-ios";
  NSString *uid = options[@"uid"];
  NSString *feedbackMsg = options[@"feedbackMsg"];
  
  // 压缩日志文件
  NSString *zipPath = [self compressionLogFileData];
  if (!zipPath.length) {
      resolve(@(-1));
      return;
  }
  
  // 初始化上传数据
  
  NSString *uploadContent = feedbackMsg;
  NSString *marketChannel = @"Demo";
  NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
  NSString *appVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
  NSString *guid = @"123456";
  NSString *systemVersion = [UIDevice currentDevice].systemVersion;
  NSString *reportType = @"UFB";
  NSString *deviceName = [[UIDevice currentDevice] systemName];
  
  NSDictionary *dataDict = @{
      @"feedback" : uploadContent,
      @"uid" : uid,
      @"marketChannel" : marketChannel,
      @"productVer" : appVersion,
      @"guid" : guid,
      @"osVer" : systemVersion,
      @"reportType" : reportType,
      @"phoneType" : deviceName,
  };
  
  NSString *postData = [NSString stringWithFormat:@"{\"appId\":\"%@\",\"sign\":\"\",\"data\":%@}", appId, [self jsonStringFromObject:dataDict]];
  
  // 上传日志文件
  [[AFHTTPSessionManager manager] POST:@"https://imobfeedback.yy.com/userFeedback" parameters:nil  constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
      [formData appendPartWithFormData:[postData dataUsingEncoding:NSUTF8StringEncoding] name:@"nyy"];
      if (zipPath) {
          NSData *zipData = [NSData dataWithContentsOfFile:zipPath];
          if (zipData == nil || zipData.length == 0) {
              return;
          }
          [formData appendPartWithFileData:zipData
                                      name:@"file"
                                  fileName:@"sylog.zip"
                                  mimeType:@"multipart/form-data"];
          
          if ([[NSFileManager defaultManager] fileExistsAtPath:zipPath isDirectory:nil]) {
              [[NSFileManager defaultManager] removeItemAtPath:zipPath error:nil];
          }
      }
  } progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
      NSInteger statusCode = ((NSHTTPURLResponse *)task.response).statusCode;
      if (statusCode == 204 || statusCode == 206) {
          resolve(@(0));
          dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{});
      } else {
        resolve(@(-1));
      }
  } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
    resolve(@(-1));
  }];

}

- (NSString *)jsonStringFromObject:(id)object
{
    NSString *jsonString = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:object
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    if (!jsonData) {
        NSLog(@"object to json faile, object: %@, error: %@", object, error.localizedDescription);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return jsonString;
}

// 压缩日志
// Compression log
- (NSString *)compressionLogFileData
{
    NSString *logFile = kLogFilePath;
    NSString *zipPath = [NSTemporaryDirectory() stringByAppendingPathComponent:@"feedback.zip"];
    if ([[NSFileManager defaultManager] fileExistsAtPath:zipPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:zipPath error:nil];
    }
    BOOL isSuccess = NO;
    if ([[NSFileManager defaultManager] fileExistsAtPath:logFile]) {
        if ([self isDirectory:logFile]) {
            isSuccess = [SSZipArchive createZipFileAtPath:zipPath withContentsOfDirectory:logFile];
        } else {
            NSArray *files = @[logFile];
            isSuccess = [SSZipArchive createZipFileAtPath:zipPath withFilesAtPaths:files];
        }
    }
    return isSuccess ? zipPath : @"";
}

- (BOOL)isDirectory:(NSString *)filePath
{
    BOOL isDirectory = NO;
    [[NSFileManager defaultManager] fileExistsAtPath:filePath isDirectory:&isDirectory];
    return isDirectory;
}

- (NSArray<NSString *> *)supportedEvents
{
  return @[@"feedback"];
}

@end
