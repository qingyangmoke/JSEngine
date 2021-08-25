//
//  ViewController.swift
//  ioscplus
//
//  Created by song on 2021/5/19.
//

import UIKit
import YogaKit
class ViewController: UIViewController {
    var name = "view";
    
    func convertToRawPointer<T>(obj: T) -> UnsafeMutableRawPointer where T : AnyObject {
        return UnsafeMutableRawPointer(Unmanaged<T>.passUnretained(obj).toOpaque());
    }

    func printResult(result:NSString) {
        print("testCallback result=", result, self.name);
    }
    
    func testEngine() {
        var sourceCode = "";
        var sourceURL = "";
        do
        {
            sourceURL = Bundle.main.path(forResource: "main", ofType: "js")!;
            sourceCode = try String(contentsOfFile: sourceURL)
        }
        catch
        {
            print("Contents could not be loaded.")
        }
        let scope = OCSwiftEngineProxy.createScope(view: self)
        scope.evaluateJavaScript(sourceCode: sourceCode, sourceURL: sourceURL, startLine: 0);
        scope.invokeJSModule(moduleName: "JSTimers", methodName: "sayHi", args: "from swift");
        
//        scope.evaluateJavaScript(sourceCode, widthSourceURL: srouceURL, widthStartLine: 0);
//        scope.invokeJSModule("JSTiremoveScopemers", widthMethodName: "sayHi", widthArgs: "from swift");
        // 销毁
//        OCSwiftEngineProxy.removeScope(contextId: scope.getContextId());
    }

    func testAlert() {
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
    
    func yogaTest() {
        let contentView = YogaUIView()
        contentView.backgroundColor = .lightGray
        contentView.configureLayout { (layout) in
          layout.isEnabled = true
          layout.flexDirection = .row
          layout.width = 320
          layout.height = 80
          layout.marginTop = 40
          layout.marginLeft = 10
        }
        
        let child1 = YogaUIView()
        child1.backgroundColor = .yellow
        child1.configureLayout{ (layout)  in
          layout.isEnabled = true
          layout.width = 80
        }
        contentView.addSubview(child1)
        
        let child2 = YogaUIView()
        child2.backgroundColor = .blue
        child2.configureLayout{ (layout)  in
          layout.isEnabled = true
          layout.flex = 0
          layout.width = 80
          layout.flexGrow = 1
        }
        contentView.addSubview(child2)
        
        view.addSubview(contentView)
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        print("hello world!")
        MyBridge.initBridge()
        self.testEngine()
        
    }
}
