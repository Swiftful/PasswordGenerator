//
//  SwiftUIView.swift
//  Generator
//
//  Created by Xose on 02.09.25.
//

import SwiftUI

class ViewModel: ObservableObject {
    @Published var isStart = false
    @Published var isGenerating = false
    @Published var model: Model = Model(length: 0, count: 0, isLetter: false, isUpper: false, isLower: false, isPunk: false, isDigit: false)
    
    var code: Int32 = -1
    var time: Double = -1
    var hashset = HashSet_Init()
    
    func WriteData(url: URL, Data: UnsafeMutablePointer<HashSet>!) async -> Bool{
        return await withCheckedContinuation { continuation in
            DispatchQueue.global(qos: .userInitiated).async {
                let result = WRITE(url.appendingPathComponent("Data.txt").relativePath, Data)
                continuation.resume(returning: result)
            }
        }
    }
    
    @MainActor
    func updateGeneratingState(_ isGenerating: Bool) {
        self.isGenerating = isGenerating
    }
    
    func Api() async -> Int32 {
        return await withCheckedContinuation { continuation in
            DispatchQueue.global(qos: .userInitiated).async {
                let result = API(self.model)
                continuation.resume(returning: result)
            }
        }
    }
    
    func Start() async -> Double {
        return await withCheckedContinuation { continuation in
            DispatchQueue.global(qos: .userInitiated).async {
                let result = START(self.model, self.hashset)
                continuation.resume(returning: result)
            }
        }
    }
    
    func Exit() async -> Bool {
        return await withCheckedContinuation { continuation in
            DispatchQueue.global(qos: .userInitiated).async {
                let result = EXIT(self.hashset)
                continuation.resume(returning: result)
            }
        }
    }
}
