//
//  VSNet.h
//  vsNet
//
//  Created by 莫晓文 on 16/6/14.
//  Copyright © 2016年 莫晓文. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VSNetProtocol.h"

@interface VSNet : NSObject
+ (VSNet *)shareinstance;
//获取本库版本号
-(NSInteger) GetSDKVersion;
#pragma mark /**************************初始化接口************************************/
- (void)CLOUDE_API_PPPP_Initialize;

- (void)CLOUDE_API_PPPP_DeInitialize;

- (void)CLOUDE_API_RussP2P;

- (void) CLOUDE_API_Eye4P2P;
- (void) CLOUDE_API_ELSOP2P;

- (void) CLOUDE_API_XQP2P_Initialize;

- (void) CLOUDE_API_XQP2P_DeInitialize;

- (int)  CLOUDE_API_XQP2P_GetAPIVersion;

- (void) CLOUDE_API_XQP2P_NetworkDetect;

#pragma mark /**************************连接与断开连接设备的接口************************************/
/**
 *  开始链接指定设备
 *  @param deviceIdentity 设备id
 *  @param user           用户名
 *  @param pwd            密码
 *  @param initializeStr  P2P串（此值尽量不要空，“前4个字符决定固定串”都应有固定的串，如果空了首次连接可能会失败）
 *  @param LanSearch      指定服务器
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_start:(NSString*) deviceIdentity withUser:( NSString*)user withPassWord:(NSString*)pwd initializeStr:(NSString *)initializeStr LanSearch:(int) nEnable ;

/**
 *  开始链接指定设备（用于AP模式下的P2P连接）
 *  @param deviceIdentity 设备id
 *  @param user           用户名
 *  @param pwd            密码
 *  @param initializeStr  P2P串（此值尽量不要空，“前4个字符决定固定串”设备都应有固定的串，如果空了首次连接可能会失败）
 *  @param LanSearch      指定服务器
 *  @return true or false
 */
- ( BOOL )  CLOUDE_API_startAPMode:(NSString*) deviceIdentity withUser:( NSString*)user withPassWord:(NSString*)pwd initializeStr:(NSString *)initializeStr LanSearch:(int) nEnable;

/**
 *  开始链接指定设备（用于低功耗设备快速连接）
 *  @param deviceIdentity 设备id
 *  @param user           用户名
 *  @param pwd            密码
 *  @param initializeStr  P2P串（此值尽量不要空，“前4个字符决定固定串”设备都应有固定的串，如果空了首次连接可能会失败）
 *  @param LanSearch      指定服务器
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_startLiteos:(NSString*) deviceIdentity withUser:( NSString*)user withPassWord:(NSString*)pwd initializeStr:(NSString *)initializeStr LanSearch:(int) nEnable ;

/**
 *  停止链接指定设备
 *  @param deviceIdentity 设备id
 *  @return true or false
 */
- ( BOOL )  CLOUDE_API_stop:(NSString*) deviceIdentity;

/**
 *  断开已经连接上的设备(正在连接的不处理)
 *  @param deviceIdentity 设备id
 *  @return true or false
 */
//- ( BOOL ) disconnect:(NSString*) deviceIdentity;

/**
 *  停止所有设备的链接
 *  @return true or false
 */
- ( void ) CLOUDE_API_stopAll;

#pragma mark /**************************设置代理接口************************************/
/**
 *  设置状态代理 设备状态通知
 *  @param deviceIdentity 设备id
 *  @param delegate       代理
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_setStatusDelegate: (NSString*) deviceIdentity  withDelegate: (id<VSNetStatueProtocol>) delegate;

/**
 *  设置参数代理，发送指令后设备回复
 *  @param deviceIdentity 设备id
 *  @param delegate       代理
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_setControlDelegate: (NSString*) deviceIdentity withDelegate: (id<VSNetControlProtocol>) delegate;

/**
 *  设置对码代理
 *  @param deviceIdentity 设备id
 *  @param delegate       代理
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_setDuimaDelegate: (NSString*) deviceIdentity withDelegate: (id<VSNetDuimaProtocol>) delegate;

/**
 *  设置报警代理
 *  @param deviceIdentity 设备id
 *  @param delegate       代理
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_setAlarmDelegate: (NSString*) deviceIdentity withDelegate: (id <VSNetAlarmProtocol>) delegate;

/**
 *  设置视频数据代理,视频数据通过改代理返回
 *  @param deviceIdentity 设备id
 *  @param delegate       代理
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_setDataDelegate: (NSString*) deviceIdentity withDelegate: (id <VSNetDataProtocol>) delegate;

#pragma mark /**************************实时视频接口************************************/
/**
 *  开始预览视频
 *  @param deviceIdentity 设备id
 *  @param stream         主码流 APP定为10
 *  @param substream      子码流 0、1、14、15、16、17、18、19、20、21、22 -> 1280*720
                                2、3、7、8、9、10、11、12 -> 640*360
                                5、6 -> 320*180
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_startLivestream:(NSString*) deviceIdentity withStream: (int) stream withSubStream: (int) substream;

/**
 *  停止预览视频
 *  @param deviceIdentity 设备id
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_stopLivestream : (NSString*) deviceIdentity ;

/**
 *  录制当前视频
 *  @param strPath 存放路径
 *  @param deviceIdentity 设备id
 *  @param completion  成功与失败
 */
- (void)CLOUDE_API_StartRecord:(NSString*) strPath cameraUid:(NSString *)deviceIdentity completion:(void (^)(BOOL success, int nError)) returnResult;

//停止录制视频
- (void)CLOUDE_API_StopCameraUid:(NSString *)deviceIdentity;

#pragma mark /**************************发送指令到设备接口************************************/
/**
 *  发送cgi指令
 *  @param cgi            cgi 指令
 *  @param deviceIdentity 设备id
 *  @return true or false
 */
- ( BOOL ) CLOUDE_API_sendCgiCommand: (NSString*) cgi withIdentity: (NSString*) deviceIdentity;

- ( BOOL ) CLOUDE_API_sendCgiCommandWithCgi: (NSString*) cgi withIdentity: (NSString*) deviceIdentity;
#pragma mark /**************************对讲与监听接口************************************/
/**
 *  打开监听
 *  @param deviceIdentity 设备id
 *  @param withEchoCancellationVer 是否支持双向对讲
 */
- ( void ) CLOUDE_API_startAudio:(NSString *) deviceIdentity withEchoCancellationVer:(BOOL)echoCancellationVer;

/**
 *  关闭监听
 *  @param deviceIdentity 设备id
 */
- ( void) CLOUDE_API_stopAudio:(NSString *) deviceIdentity;

/**
 *  打开对讲
 *  @param deviceIdentity 设备id
 *  @param withEchoCancellationVer 是否支持双向对讲
 */
- (void) CLOUDE_API_startTalk:(NSString *) deviceIdentity withEchoCancellationVer:(BOOL)echoCancellationVer;

/**
 *  关闭对讲
 *  @param deviceIdentity 设备id
 */
- (void) CLOUDE_API_stopTalk:(NSString *) deviceIdentity;
#pragma mark/**************************TF卡回放接口beg************************************/
/**
 *  播放 SD 卡
 *  @param deviceIdentity 设备id
 *  @param Name           文件名
 *  @param offset         播放偏移
 *  @param size           文件大小
 *  @param SupportHD      设备是否支持1440高清 0不支持，1支持
 *  @param delegate      @protocol TFCardProtocol
 */

- (void) CLOUDE_API_startPlayBack:(NSString *)deviceIdentity fileName:(NSString *)Name withOffset:(NSInteger)offset fileSize:(NSInteger) size delegate:(id) delegate SupportHD:(int) isHD;

/**
 *  录制TF卡
 *  @param deviceIdentity 设备id
 *  @param fileName       录制文件存放路
  * @param width          视频宽
  * @param height         视频高
 */

- (void) CLOUDE_API_startRcrodTF:(NSString *)deviceIdentity fileName:(NSString *)strRecordPath width:(int)videoW height:(int)videoH ;

//停止录制TF卡
- (void) CLOUDE_API_stopRcrodTF:(NSString *)deviceIdentity ;

//拖动回放进度
- (NSInteger) CLOUDE_API_movePlaybackPos:(NSString *)deviceIdentity POS:(float) fos ;

//根据拖动回放进度去设置回放进度
- (void)  CLOUDE_API_setPlaybackPos:(NSString *)deviceIdentity time:(NSUInteger) time ;

/**
 *  停止播放 SD 卡
 *
 *  @param deviceIdentity 设备id
 */
- (void) CLOUDE_API_stopPlayBack:(NSString *)deviceIdentity ;

/**
 *  暂停回放
 *  @param deviceIdentity 设备id
 *  @param isPause      0:暂停回放与录制 1:恢复回放与录制 2:暂停回放 3:恢复回放 4:暂停录制 5:恢复录制
 */
- (void) CLOUDE_API_PausePlayback:(NSString *)deviceIdentity pause:(int) isPause;

#pragma mark/**************************TF卡回放接口end************************************/

#pragma mark/**************************低功耗设备端接口beg************************************/
//置前台需要连接服务器
- (int)CLOUDE_API_MagLowpowerDeviceConnect:(NSString*) strIP;

//置后台需要断开服务器
- (void)CLOUDE_API_MagLowpowerDeviceDisconnect;

- (void)CLOUDE_API_setLowpowerDeviceDelegate: (id <LowpowerDeviceProtocol>) delegate;

- (int)CLOUDE_API_GetMagLowpowerServerConnectStatus;

//初化设备
- (int)CLOUDE_API_MagLowpowerInitDevice:(NSString *)deviceIdentity;

//取设备状态
- (int)CLOUDE_API_MagLowpowerGetDeviceStatus:(NSString *)deviceIdentity;

//唤醒设备
- (int)CLOUDE_API_MagLowpowerAwakenDevice:(NSString *)deviceIdentity;

//是IPV6的网络
-(void)CLOUDE_API_SetMagLowpowerSocketIPV6;
#pragma mark/**************************低功耗设备端接口end************************************/

#pragma mark/**************************局域网内搜索在线设备接口********************************/
//开始搜索 delegate是代理，回调搜索到的设备
-(void)CLOUDE_API_StartSearchDVS:(id<VSNetSearchCameraResultProtocol>)delegate;

//停止搜索
-(void)CLOUDE_API_StopSearchDVS;

//h265设备接口改变设备编码器，Operation:0切成h264 1切成H265 2查当前使用的编码器
-(int) CLOUDE_API_SwitchDeviceEncoder:(NSString *)deviceIdentity Operation:(int) opt;

//APP是否进入后台，IsBG=YES:是 IsBG=NO:否
-(void) CLOUDE_API_EnterBackground:(BOOL)IsBG;

//特殊设备指定视频解码回调
- (void)CLOUDE_API_setCameraIsPanorama:(BOOL)isPanorama withUid:(NSString *)deviceIdentity;

//重置视频解码器
- (void)CLOUDE_API_ResetH264Init:(NSString *)deviceIdentity;

/**
 * 修改设备密码
 * @param deviceIdentity 设备id
 * @param Restart        是否重启设备
 * @param admimUser      管理员用户名
 * @param adminPWD       管理员新密码
 * @param OperatorUser   操作员用户名(不修改时填空nil)
 * @param OperatorPWD    操作员新密码(不修改时填空nil)
 * @param VisitorUser    访客用户名(不修改时填空nil)
 * @param VisitorPWD     访客新密码(不修改时填空nil)
 * @return 1发送成功，0失败
 */
- (int) CLOUDE_API_ModifyPassword:(NSString *)deviceIdentity Restart:(BOOL)IsRestart
             admimUser:(NSString*) strAdminUser adminPWD:(NSString*) strAdPwd
          OperatorUser:(NSString*) strOpUser  OperatorPWD:(NSString*) strOpPWd
           VisitorUser:(NSString*) strVsUser  VisitorPWD:(NSString*) strVsPWd;


/*服务器加密解密接口*/
//解密 返回nil代表解密失败
-(NSString *)CLOUDE_API_SeverDecryptStr:(NSString *)sValue;

//加密 返回nil代表加密失败
-(NSString *)CLOUDE_API_SeverEncryptStr:(NSString *)sValue;

//生成key
-(NSString*)CLOUDE_API_GetDevEncryptKey:(NSString*)strUser PW:(NSString*)strPW;

//解密 返回nil代表解密失败
//sValue:密文 strKey:key
-(NSString*)CLOUDE_API_DeviceDecryptStr:(NSString*)sValue KEY:(NSString*)strKey;

//加密 返回nil代表加密失败
//sValue:明文 strKey:key
-(NSString*)CLOUDE_API_DeviceEncryptStr:(NSString*)sValue KEY:(NSString*)strKey;

#pragma mark/***********************合并视频文件接口*****************************/
/**
 * 开始合并视频文件
 * @param deviceIdentity 设备id
 * @param strInPath      输入文件(单个文件)
 * @param strOutPath     输出文件
 * @param nCount         输入文件个数(总文件个数)
 * @param delegate       进度回调代理
 * @return 1成功，0失败
 */
-(int) CLOUDE_API_StratMergeMP4File:(NSString*)deviceIdentity InputPath:(NSString*)strInPath OutPath:(NSString*)strOutPath FileCount:(int)nCount Delegate:(id <MergerVideoProtocol>) delegate;

/**
 * 往合并视频列表中添加文件
 * @param deviceIdentity 设备id
 * @param strInPath      输入文件(单个文件)
 * @return 1成功，0失败
 */
-(int) CLOUDE_API_PutFile:(NSString*)deviceIdentity InputPath:(NSString*)strInPath;

/**
 * 获取合并文件的合并文件进度
 * @param deviceIdentity 设备id
 * @return 0~1.0进度  -1代表错误
 */
-(float) CLOUDE_API_GetMergeMP4FilePos:(NSString*)deviceIdentity;

/**
 * 中断合并
 * @param deviceIdentity 设备id
 * @return 1成功，0失败
 */
-(int) CLOUDE_API_StopMergeMP4File:(NSString*)deviceIdentity;

@end