//
//  ContentView.swift
//  Generator
//
//

import SwiftUI

struct RootView: View {
    @StateObject var viewModel = ViewModel()
    
    var body: some View {
        VStack {
            MainView(viewModel: viewModel)
        }
        .padding()
    }
}

#Preview {
    RootView()
}
