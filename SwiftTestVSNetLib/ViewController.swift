//
//  ViewController.swift
//  SwiftTestVSNetLib
//
//  Created by ricky on 2019/6/3.
//  Copyright © 2019 Ricky. All rights reserved.
//

import UIKit

class ViewController: UIViewController,VSNetStatueProtocol,VSNetDataProtocol{
    var myUID = ""
     var mypwd = "";
    var displayView: IJKSDLGLView!
    var videoData:NSData!;
   
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let getFrame:CGRect =  UIScreen.main.bounds;
        displayView = IJKSDLGLView(frame:CGRect(x: 0, y: 0, width: getFrame.width, height: getFrame.height - 80.0));
        displayView.backgroundColor = UIColor.black;
        self.view.addSubview(displayView);
        
        //连接设备
        VSNet.shareinstance()?.start(myUID, withUser:"admin", withPassWord:mypwd, initializeStr: nil, lanSearch: 1);
        //设置连接状态回调代理
        VSNet.shareinstance()?.setStatusDelegate(myUID, withDelegate:self);
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated);
        

    }
    
    //请求视频
    @IBAction func ClickPlay(sender:UIButton){
        VSNet.shareinstance()?.startLivestream(myUID, withStream: 10, withSubStream: 2);
        //设置视频数据回调代理
        VSNet.shareinstance()?.setDataDelegate(myUID, withDelegate: self);
    }
    
    //VSNetStatueProtocol 设备状态回调代理
    func vsNetStatus(_ deviceIdentity: String!, statusType: Int, status: Int) {
        if(deviceIdentity != myUID){
            return ;
        }
        
        NSLog(deviceIdentity);
    }
    
    //VSNetDataProtocol 视频数据回调代理
    func vsNetYuvData(_ deviceIdentity: String!, data buff: UnsafeMutablePointer<UInt8>!, withLen len: Int, height: Int, width: Int, time timestame: UInt, origenelLen oLen: Int) {
        if(deviceIdentity != myUID){
            return ;
        }
        
        //buff 是解码出来的视频数据。要及时使用或者保存起来，出了作用域(跳出回调方法)后就会释放掉。
        DispatchQueue.main.sync {
            var overlay : SDL_VoutOverlay = SDL_VoutOverlay(w: Int32(Int(width)), h: Int32(Int(height)), pitches: (UInt16(width),UInt16(width) / 2,UInt16(width) / 2), pixels: (buff, buff + width * height, buff + width * height * 5 / 4))
            self.displayView.display(&overlay);
        }
    }
    
    func vsNetVideoData(_ deviceIdentity: String!, length: Int32) {
        
    }
    
    func vsNetH264Data(_ deviceIdentity: String!, data buff: UnsafeMutablePointer<UInt8>!, withLen len: Int, height: Int, width: Int, time timestame: UInt, withType type: Int) {
        
    }
    

    func vsNetHardH264Data(_ deviceIdentity: String!, data pixeBuffer: CVPixelBuffer!, time timestame: UInt, origenelLen oLen: Int) {
        
    }
    
    func vsNetImageNotify(_ deviceIdentity: String!, withImage imageData: Data!, timestamp: Int) {
        
    }
    
    func vsNetParamNotify(_ paramType: Int32, params: UnsafeMutableRawPointer!) {
        
    }
    
    func vsNetVideoBufState(_ deviceIdentity: String!, state: Int32) {
        
    }
}

