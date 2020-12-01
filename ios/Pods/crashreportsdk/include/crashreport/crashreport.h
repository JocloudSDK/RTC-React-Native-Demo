//
//  crashreport.h
//  crashreport
//
//  Created by DH.Zhang on 15/5/26.
//  Copyright (c) 2015年 DW. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CrashDB;
@class CrashUploader;
@class UIViewController;

/**
 * 用于表示不同异常类型的枚举.
 */
typedef NS_ENUM(NSUInteger,AbnormalMsgType){
    /**
     *  异常类型:崩溃防护
     */
    AbnormalTypeCrashGuard,
    /**
     *  异常类型:ANR
     */
    AbnormalTypeANR,
    /**
     *  异常类型:Flutter
     */
    AbnormalTypeFlutter,
};

/**
 * CrashReport提供C++及OC崩溃捕获，ANR检测功能.
 *
 * CrashReport实例的获取方式: [CrashReport sharedObject].
 *
 */

@interface CrashReport : NSObject {
@protected
    CrashDB *crashDB_;
    CrashUploader *crashUploader_;
    NSMutableArray *userLogList_;
   
    void(^crash_callback_)(NSString*, NSString*);
    void(^anr_callback_)(void);
    NSString* (^getYSPStack)(void);
    void (^preparationForAbnormalMsg)(AbnormalMsgType,NSString*);
    void (^notifyGuardedCrashCallback)(NSString*);
    UIViewController *(^getCurrentTopViewControllerBlock)(void);
}

/**
 * @brief CrashReport单例对象获取接口.
 */
+(CrashReport *)sharedObject;

/**
 * @brief 进行crashreport sdk初始化.
 *
 * @param appId 业务方向服务器申请的app标识.
 * @see CrashReport#initWithAppid:market:.
 */
-(void)initWithAppid:(NSString *)appId;

/**
 * @brief 进行crashreport sdk初始化.
 *
 * @param appId 业务方向服务器申请的app标识.
 * @param market 市场信息.
 * @see CrashReport#initWithAppid:appVersion:market:.
 */
-(void)initWithAppid:(NSString *)appId market:(NSString *)market;

/**
 * @brief 进行crashreport sdk初始化.
 *
 * @param appId 业务方向服务器申请的app标识.
 * @param appVersion 业务方指定的版本号,不使用默认的CFBundleShortVersionString.
 * @param market 市场信息.
 */
-(void)initWithAppid:(NSString *)appId appVersion:(NSString*)appVersion market:(NSString *)market;

/**
 * @brief 进行crashreport sdk初始化.
 *
 * @param appId 业务方向服务器申请的app标识.
 * @param appVersion 业务方指定的版本号,不使用默认的CFBundleShortVersionString.
 * @param market 市场信息.
 * @param deviceid 海度SDK的设备信息号
 */
-(void)initWithAppid:(NSString *)appId appVersion:(NSString*)appVersion market:(NSString *)market deviceId:(NSString *)deviceid;

/**
 * @brief 使用set_terminate函数，主要为了处理C++ throw的问题.
 *
 */
-(void)useSetterminate;

/**
 * @brief 反初始化.
 * @warning 请在程序退出时调用(terminateWithStatus)，否则kill app可能会当成崩溃上报.
 *
 */
-(void)unInit;

/**
 * @brief 设置用户LOG路径，在崩溃发生时，将一起上传该日志.
 *
 * @param logFile 日志文件全路径.
 */
-(void)setUserLogFile:(NSString *)logFile;

/**
 * @brief 设置用户LOG，在崩溃发生时，将一起上传该日志.
 *
 * @param logFileList 日志文件列表 需全路径 NSArray(NSString*).
 */
-(void)setUserLogList:(NSArray *)logFileList;

/**
 调用方可通过此接口设置自己的崩溃回调逻辑.

 @param callback 非崩溃线程回调，crashId 崩溃ID ，crashDumpFile 崩溃文件路径.
 */
-(void)setCrashCallback:(void(^)(NSString* crashId, NSString* crashDumpFile))callback;

/**
 * @brief 发送反馈信息.
 *
 * @param content 反馈信息的内容.
 * @param screenCapture 是否发送当前的屏幕快照.
 */
- (void)sendFeedback:(NSString *)content screenCapture:(BOOL)screenCapture;

/**
 * @brief 发送反馈信息.
 *
 * @param feedbackType  反馈的模块分类.
 * @param content 反馈信息的内容.
 * @param screenCapture 是否发送当前的屏幕快照.
 */
- (void)sendFeedback:(int)feedbackType content:(NSString *)content screenCapture:(BOOL)screenCapture;

/**
 * @brief 发送反馈信息.
 *
 * @param content 反馈信息的内容.
 * @param imageList 和反馈信息一起上传的一组截图.
 */
- (void)sendFeedback:(NSString *)content imageList:(NSArray *)imageList;

/**
 * @brief 发送反馈信息.
 *
 * @param feedbackType  反馈的模块分类.
 * @param content 反馈信息的内容.
 * @param imageList 和反馈信息一起上传的一组截图.
 */
-(void)sendFeedback:(int)feedbackType content:(NSString *)content
          imageList:(NSArray *)imageList;

/**
 * @brief 发送反馈信息.
 *
 * @param content 反馈信息的内容.
 * @param fileList 和反馈信息一起上传的一组文件.
 */
-(void)sendFeedback:(NSString *)content
           fileList:(NSArray *)fileList;

/**
 * @brief 发送反馈信息.
 *
 * @param feedbackType  反馈的模块分类.
 * @param content 反馈信息的内容.
 * @param fileList 和反馈信息一起上传的一组文件.
 */
-(void)sendFeedback:(int)feedbackType content:(NSString *)content
           fileList:(NSArray *)fileList;

/**
 * @brief 添加上报扩展信息，设置之后崩溃时会一起上报.
 *
 * @param extInfo 扩展信息 {@(String): @(String)}.
 */
-(void) setExtInfo:(NSDictionary*) extInfo;

/**
 * @brief 设置UID.
 *
 * @param uid 用户id.
 */
-(void) setUid:(uint) uid;

/**
 *  @brief 开启ANR(应用程序卡顿)检测(采用默认的卡顿检测阀值 5 second).
 */
- (void)enableANRDetection;

/**
 *  @brief 开启ANR(应用程序卡顿)检测.
 *
 *  @param anrThreshold 卡顿检测的阀值(单位:second).
 */
- (void)enableANRDetection:(double)anrThreshold;

/**
 *  @brief 关闭ANR(应用程序卡顿)检测.
 */
- (void)disableANRDetection;

/**
 *  @brief 调用方可通过此接口设置自己的卡顿回调逻辑.
 *  @param callback block形式的回调接口，crashreportsdk检测到ANR时会调用callback.
 */
-(void)setAnrCallback:(void(^)(void))callback;

/**
 *  @brief 调用ANR回调.
 */
-(void)callAnrCallback;

/**
 *  @brief 获取最近的一条崩溃信息记录.
 *
 *  @return NSDictionary* 字典形式的最近一条崩溃信息.
 *  @warning 若最近未发生崩溃则返回值可能是nil.
 *  @discussion 崩溃信息的内容格式为 : @{@"crash_id" : @"crashIdString", @"data" : @"crashInfoNyyData", @"dump_file_key" : @"crashDumpFileName", @"log_file_key" : @"crashLogFileName", @"user_log_file_key" : @"userLogFileFullPath"}.
 */
- (NSDictionary *)latestCrashInfo;

/**
 *  @brief 获取最近的一条ANR记录.
 *  @return NSDictionary* 字典形式的最近一条ANR信息.
 *  @warning 若最近未发生ANR则返回值可能是nil.
 */
- (NSDictionary *)latestANRInfo;

/**
 *  @brief 删除最近的一条崩溃信息记录.
 */
- (void)deleteLatestCrashInfo;

/**
 *  @brief 删除最近的一条ANR记录.
 */
- (void)deleteLatestANRInfo;

/**
 * @brief 测试崩溃收集.
 * @discussion 可以调用此方法触发崩溃，然后到崩溃系统查看上报是否成功，调用时不要开启调试器.
 */
-(void)testCrash;

/**
 * @brief 设置ysp栈获取接口.
 * @param getter block形式的ysp栈获取回调接口.
 */
- (void)setYSPStackGetter:(NSString*(^)(void))getter;

/**
 *  该接口会将当前堆栈上报，展示在崩溃详情面板
 *
 * @brief 上报异常.
 * @param msg 异常描述.
 * @param type 异常类型.
 */
- (void)reportAbnormalMsg:(NSString*)msg forType:(AbnormalMsgType)type;

/**
 *  该接口不会上报当前堆栈，会使用传入dumpFile文本展示在崩溃详情面板
 *
 * @brief 上报异常.
 * @param msg 异常描述.
 * @param dumpFile dump文件，调用该接口不会z
 * @param type 异常类型.
 */
- (void)reportAbnormalMsg:(NSString *)msg dumpFile:(NSString *)dumpFile forType:(AbnormalMsgType)type;
/**
 * @brief 上报异常之前填充必要信息的回调.
 * @param preparation crashreportsdk检测到异常之后，处理异常之前执行的回调，主要用于外部准备好extinfo.
 * @see CrashReport#setExtInfo:.
 */
- (void)setPreparationForAbnormalMsgBlock:(void(^)(AbnormalMsgType,NSString*))preparation;

/**
 * @brief 获取当前是否在进行崩溃处理.
 * @return BOOL 当前是否有崩溃正在处理.
 */
+ (BOOL)isHandlingCrash;

/**
 * @brief 崩溃异常发生时的回调.
 * @param notifyGuardedCrashBlock crashreportsdk检测到崩溃防护之后，处理防护之前执行回调.
 */
- (void)setNotifyGuardedCrash:(void(^)(NSString*))notifyGuardedCrashBlock;

/**
 * @brief 设置崩溃上报appversion.
 * @param appversion 崩溃上报使用的app版本字符串.
 */
- (void)reviseAppVersion:(NSString*)appversion;

/**
 * @brief 崩溃上报时获取当前顶层 vc
 */
- (void)setGetCurrentTopViewControllerBlock:(UIViewController *(^)(void))block;

/**
 会重定向控制台输出，崩溃时携带最后【msgline】行控制台信息上传崩溃后台

 @param msgline 行数
 */
- (void)printConsoleMsg:(NSUInteger)msgline;

/**
 为了支持extension ，[UIApplication sharedApplication].applicationState 需要从外部获取

 @param block 获取applicationState
 */
@property (nonatomic, copy) NSInteger(^applicationStateGetterBlock)(void);


/**
 * @brief 打印外部传进来的信息到崩溃错误日志上
 * @param log 需要w额外上报的信息.
 */
- (void)printExtendLog:(NSString *)log;

/**
 返回最后几个崩溃日志，

 @param count 最大数量
 */
- (NSArray <NSString*> *)getLastCrashSyslogs:(NSUInteger)count;


/**
 崩溃上报前将dmp文件准备好，期间如果发生错误会把错误信息放进拓展字段 crashsdkErrorMsg 中

 @param prezip 默认是YES
 */
- (void)setPreZipDumpIfCrash:(BOOL)prezip;


/**
 获取崩溃线程

 @return glibc库的线程id，线程控制块tcb首地址 pthread
 */
- (pthread_t)getCrashThread;

@end
