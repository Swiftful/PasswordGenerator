//
//  GeneratorApp.swift
//  Generator
//
//

import SwiftUI

@main
struct GeneratorApp: App {
    var body: some Scene {
        WindowGroup {
            RootView()
                .frame(width: 400, height: 250)
        }
        .windowResizability(.contentSize)
    }
}
