//
//  ImageHelper.swift
//  ioscplus
//
//  Created by song on 2021/8/25.
//

import Foundation
import UIKit

public class ImageHelper {
    public static var imageCache = NSCache<NSString, UIImage>()

    public static func loadImageUsingCache(withUrl urlString : String, completion: @escaping (UIImage?) -> ()) {
        let url = URL(string: urlString)
        if url == nil {
            completion(nil)
        }

        if let cachedImage = imageCache.object(forKey: urlString as NSString)  {
            completion(cachedImage)
            return
        }

        URLSession.shared.dataTask(with: url!, completionHandler: { (data: Data?, response: URLResponse?, error: Error?) in
            if error != nil {
                completion(nil)
                return
            }

            if let image = UIImage(data: data!) {
                imageCache.setObject(image, forKey: urlString as NSString)
                completion(image)
            } else {
                completion(nil)
            }
        }).resume()
    }
}
