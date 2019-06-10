//
//  PlayerRTMPFile.hpp
//  vsNet
//
//  Created by ricky on 2017/12/13.
//  Copyright © 2017年 ricky. All rights reserved.
//

#ifndef PlayerRTMPFile_h
#define PlayerRTMPFile_h
#import <Foundation/Foundation.h>
#import "ImageNotifyProtocol.h"
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/AudioFile.h>
#include <AudioToolbox/AudioQueue.h>
#include <stdio.h>

#include "CircleBuf.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include "libswresample/swresample.h"
}

#define  NUM_BUFFERS 3
typedef void (*AudioBufferCallback)(void *inUserData,AudioQueueRef inAQ,AudioQueueBufferRef buffer);
class CPlayerRTMPFile
{
public:
    CPlayerRTMPFile();
    ~CPlayerRTMPFile();
    //      播放文件
    int     StartPlayerFile(const char* szFilePath);
    //      停止播放
    void    StopPlayer();
    //设置解码数据回调
    void    SetPlayViewImageNotifyDelegate(id<ImageNotifyProtocol> delegate);
    //void    SetPlaybackDelegate(id<PlaybackProtocol> playbackDelegate);
    
    //开启声音播放，默认是开启的
    void    StartVoice();
    void    StopVoice();
    //暂停播放 YES暂停，NO:恢复播放
    void    Pause(BOOL isPause);
    //快进 快退
    void    SeekPlayback(int nSecond);
private:
    static     void* PlayDataThread(void *param);
    void       PlayDataProess();
    void       IsPlaySleep(int pts);
    
    int  readPacketsIntoBuffer(AudioQueueBufferRef buffer);
    void initAudioPlayer(AudioBufferCallback BuffCallback);
    static void AudioBuffer_Callback(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef buffer);
private:
    AVFormatContext*   m_pFormatCtx;
    AVCodecContext*    m_videoCodecCtx;
    AVCodecContext*    m_audioCodecCtx;
    long long          m_nLastPlayMobileTime; //最近播放手机时间
    bool               m_bResetCoder;
    int                m_nLastPts;
    
    pthread_t          m_PlayThreadID;
    int                m_nExit;
    int                m_videoStreamsIndex;
    int                m_audioStreamsIndex;
    
    int                m_nMedianDuration;
    float              m_nVideoFps;
    int                m_nFpsMs;
    
    id<ImageNotifyProtocol>    m_PlayViewImageNotifyDelegate;
    //id<PlaybackProtocol>       m_playbackDelegate;
    
    NSCondition*       m_playLock;
    
    AudioStreamBasicDescription     m_dataFormat;
    AudioQueueRef                   m_queue;
    AudioStreamPacketDescription*   m_packetDescs;
    AudioQueueBufferRef             m_buffers[NUM_BUFFERS];
    CircleBuf*                      m_pAudioBuf;
    BOOL                            isVoice;
    BOOL                            m_isPause;
};

#endif /* PlayerRTMPFile_h */
