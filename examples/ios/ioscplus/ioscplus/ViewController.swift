//
//  ViewController.swift
//  ioscplus
//
//  Created by song on 2021/5/19.
//

import UIKit
class ViewController: UIViewController {
    var name = "view";
    
    func convertToRawPointer<T>(obj: T) -> UnsafeMutableRawPointer where T : AnyObject {
        return UnsafeMutableRawPointer(Unmanaged<T>.passUnretained(obj).toOpaque());
    }

    func printResult(result:NSString) {
        print("testCallback result=", result, self.name);
    }
    
    func testNormalTypes() {
        let result = MyBridge.flushBridgeTask();
        print("result=", result);
        MyBridge.printCPlusString("swift string");
        MyBridge.testStruct("nativeString", widthLength: 100);
        // 把当前对象转换成C++识别的指针类型void *
        let observer = self.convertToRawPointer(obj: self);
        MyBridge.testCallback("swift", widthCallBack: { (result: UnsafePointer<Int8>?, observer: UnsafeMutableRawPointer?) in
            // 把C++返回的对象指针转换成ViewController
            let mySelf = Unmanaged<ViewController>.fromOpaque(observer!).takeUnretainedValue();
            // let mySelf = self.fromPointer(observer: observer!) as ViewController;
            mySelf.printResult(result: NSString(utf8String: result!) ?? "");
        }, withTarget: observer);
//        MyBridge.engineTest();Ï
    }
    
    func testEngine() {
        var sourceCode = "";
        var srouceURL = "";
        do
        {
            srouceURL = Bundle.main.path(forResource: "main", ofType: "js")!;
            sourceCode = try String(contentsOfFile: srouceURL)
        }
        catch
        {
            print("Contents could not be loaded.")
        }
        let scope = MyBridge.createScope(2);
        scope!.evaluateJavaScript(sourceCode, widthSourceURL: srouceURL, widthStartLine: 0);
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        print("hello world!");
        MyBridge.initBridge();
        self.testEngine();
        
        
        let param = ["key1": "value1", "key2": "value2"];
        let title = param["title"] as? String ?? "提示";
        let message = param["message"]  as? String ?? "";
        let cancelButtonTitle = param["cancelButtonTitle"] as? String ?? "取消"
        let okButtonTitle = param["okButtonTitle"] as? String ?? "确定"
        let contextId = param["contextId"] as? String ?? ""
        let alertController = UIAlertController(title: title,
                                                message: message , preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: cancelButtonTitle, style: .cancel, handler: {
            action in
            print("点击了取消")
        })

        let okAction = UIAlertAction(title: okButtonTitle, style: .default, handler: {
            action in
            print("点击了确定")
        })

        alertController.addAction(cancelAction)
        alertController.addAction(okAction)
        DispatchQueue.main.async { [weak self] in
            self?.present(alertController, animated: true, completion: nil)
        }
    }
}
