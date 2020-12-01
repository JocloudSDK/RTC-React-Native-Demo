//
//  CrashreportSetup.m
//  SCloudAudio
//
//  Created by iPhuan on 2019/12/13.
//  Copyright © 2019 JLY. All rights reserved.
//

#import "CrashreportSetup.h"
#import <UIKit/UIKit.h>
#import "crashreport.h"
#import "Utils.h"

static NSString * const kCrashreportAppId = @"RtcRNdemo-ios"; // 对接崩溃系统AppID


@interface CrashreportSetup ()

@end

@implementation CrashreportSetup

+ (void)load {
    [[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationDidFinishLaunchingNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
        [self p_setupCrashreport];
    }];

    [[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationWillTerminateNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
        [[CrashReport sharedObject] unInit];
    }];
}


+ (void)p_setupCrashreport {
    [[CrashReport sharedObject] initWithAppid:kCrashreportAppId appVersion:[Utils appVersion] market:@"dev"];

    UIApplicationState state = [UIApplication sharedApplication].applicationState;
    [[CrashReport sharedObject] setApplicationStateGetterBlock:^NSInteger {
        return state;
    }];
    
    // ANR检测 TODO: app set custom ANR threshold
    [[CrashReport sharedObject] enableANRDetection:5];
    
}

@end
