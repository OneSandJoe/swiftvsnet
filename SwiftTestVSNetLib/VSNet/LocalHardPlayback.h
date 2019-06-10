//
//  LocalPlayback.h
//  P2PCamera
//
//  Created by mac on 12-11-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef P2PCamera_LocalHardPlayback_h
#define P2PCamera_LocalHardPlayback_h
#import "ImageNotifyProtocol.h"
#import <QuartzCore/QuartzCore.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/AudioFile.h>
#include <AudioToolbox/AudioQueue.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#define NUM_BUFFERS 3
#define _AVCODEC_MAX_AUDIO_FRAME_SIZE  5120

typedef void (*AudioBufferCallback)(void *inUserData,AudioQueueRef inAQ,AudioQueueBufferRef buffer);
@class H264FileHardDecoder;
class CircleBuf;
class CAdpcm;
class CLocalHardPlayback
{
public:
    CLocalHardPlayback();
    ~CLocalHardPlayback();
    //设置解码数据回调
    void SetPlayViewImageNotifyDelegate(id<ImageNotifyProtocol> delegate);
    
    //播放文件
    BOOL StartPlayback(char *szFilePath);
    //暂停播放 YES暂停，NO:恢复播放
    void Pause(BOOL bPause);
    //停止播放
    void StopPlayback();
    void SetFileEnd(char *szFilePath);
    //BOOL isYuncunchu;
    
    //开启声音播放，默认是开启的
    void StartVoice();
    void StopVoice();
    
    //倍速
    void SetPlaySeed(VSSDK_SPEEDPLAY speedTpye);
    
protected:
    static void* PlaybackThread(void* param);
    void PlaybackProcess();
    //BOOL PlayNextFile();
    void IsSleep(double frameTime);
    
    int readPacketsIntoBuffer(AudioQueueBufferRef buffer);
    void initAudioPlayer(AudioBufferCallback BuffCallback);
    static void AudioBuffer_Callback(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef buffer);
    
    int  SpeedVideoParameter(BOOL  iFrame);
    int  SpeedAudioParameter();
private:
    void PlayH264();
    
    FILE *                      m_pfile;
    
    pthread_t                   m_PlaybackThreadID;
    int                         m_bPlaybackThreadRuning;

    id<ImageNotifyProtocol>     m_PlayViewImageNotifyDelegate;
    
    BOOL m_bPause;
    NSCondition *            m_playbackLock;
    H264FileHardDecoder*     m_pHardDecoder;
    int                      m_nPlayIndxe;
    NSArray*                 m_arrayFiles;
    
    double                   m_nLastPlayFrameTime;
    long long                m_nLastPlayMobileTime;
    BOOL                     m_bResetCoder;
    
    AudioStreamBasicDescription m_dataFormat;
    AudioQueueRef m_queue;
    AudioStreamPacketDescription *  m_packetDescs;
    AudioQueueBufferRef             m_buffers[NUM_BUFFERS];
    CircleBuf *                     m_pAudioBuf;
    CAdpcm *                        m_pAudioAdpcm;
    
    BOOL isVoice;
    NSCondition *                   m_playbackPlayLock;
    
    VSSDK_SPEEDPLAY                 m_nSpeedplay;//倍速
    int                             m_nSeedVideoIndex;//
    int                             m_nSeedAudioIndex;//
    int                             m_nVideoFps;     //视频fps
};


#endif
