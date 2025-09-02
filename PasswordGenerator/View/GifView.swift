//
//  GifView.swift
//  Generator
//
//

import SwiftUI

struct MacGifView: NSViewRepresentable {
    let gifName: String
    
    func makeNSView(context: Context) -> NSImageView {
        let imageView = NSImageView()
        imageView.imageScaling = .scaleProportionallyUpOrDown
        return imageView
    }
    
    func updateNSView(_ imageView: NSImageView, context: Context) {
        guard let gifUrl = Bundle.main.url(forResource: gifName, withExtension: "gif") else { return }
        imageView.image = NSImage(contentsOf: gifUrl)
    }
}
