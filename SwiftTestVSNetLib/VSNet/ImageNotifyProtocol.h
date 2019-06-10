//
//  ImageNotifyProtocol.h
//  P2PCamera
//
//  Created by mac on 12-7-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

@protocol ImageNotifyProtocol <NSObject>
@optional
- (void) ImageNotify: (UIImage *)image timestamp: (NSInteger)timestamp DID:(NSString *)did;
/**
 *  解码出来的视频数据
 *  @param yuv              yuv数据
 *  @param length           yuv数据大小
 *  @param width            视频宽
 *  @param height           视频高
 *  @param timestamp        当前帧时间
 *  @param duration         视频总时长
 */
- (void) YUVNotify: (Byte*) yuv length:(int)length width: (int) width height:(int)height timestamp:(unsigned int)timestamp DID:(NSString *)did duration:(int)duration;
- (void) H264Data: (Byte*) h264Frame length: (int) length type: (int) type timestamp: (NSInteger) timestamp;

//解码出来的视频
- (void) HardH264Data:(CVPixelBufferRef ) pixeBuffer;
//播放结束 type =0 ：代表是文件结束 。 -2代表：文件协议头错误  -3代表：视频时间错误 其它是内部错误
- (void) BackStop:(int)type;
//当前视频帧UTC时间
- (void) BackGMTTime:(long)currentGMTTime;
//当前视频帧H264数据大小
- (void) BackFileSize:(int)size;
@end

//倍速播放参数
typedef NS_ENUM(NSUInteger, VSSDK_SPEEDPLAY){
    VSSDK_SPEEDPLAY_1 = 0,            //正常播放速度
    VSSDK_SPEEDPLAY_1_5 = 1,          //1.5倍速
    VSSDK_SPEEDPLAY_2   = 2,          //2倍速
    VSSDK_SPEEDPLAY_2_5 = 3,          //2.5倍速
    VSSDK_SPEEDPLAY_3 = 4,            //3倍速
    VSSDK_SPEEDPLAY_3_5 = 5,          //3.5倍速
    VSSDK_SPEEDPLAY_4 = 6,            //4倍速
    VSSDK_SPEEDPLAY_4_5 = 7,          //4.5倍速
    VSSDK_SPEEDPLAY_5 = 8,            //5倍速
};
