//
//  MainView.swift
//  Generator
//
//

import SwiftUI

struct MainView: View {
    @State var status = ""
    @State var folderUrl: URL = URL.desktopDirectory
    @ObservedObject var viewModel: ViewModel
    
    var body: some View {
        ZStack{
            MacGifView(gifName: "background")
            HStack{
                Link(destination: URL(string: "https://github.com/Swiftful/PasswordGenerator")!){
                    Image(systemName: "link")
                        .foregroundStyle(.green)
                }
            }
            .frame(width: 400, height: 240, alignment: .topTrailing)
            VStack {
                VStack() {
                    HStack{
                        Text("Length")
                        TextField("Length", value: $viewModel.model.length, format: .number)
                    }
                    HStack{
                        Text("Count ")
                        TextField("Count", value: $viewModel.model.count, format: .number)
                    }
                }
                .textFieldStyle(.roundedBorder)
                .frame(maxWidth: 250)
                
                HStack {
                    Toggle("Digit", isOn: $viewModel.model.isDigit)
                    Toggle("Special", isOn: $viewModel.model.isPunk)
                    Toggle("Letter", isOn: $viewModel.model.isLetter)
                    Toggle("Upper", isOn: $viewModel.model.isUpper)
                        .disabled(!viewModel.model.isLetter)
                    Toggle("Lower", isOn: $viewModel.model.isLower)
                        .disabled(!viewModel.model.isLetter)
                }
                HStack{
                    Text(status)
                        .foregroundStyle(.green)
                        .scaledToFill()
                    if status != "" { ProgressView() }
                }

                HStack {
                    Button("Start") {
                        Task {
                            await startGeneration()
                        }
                    }
                    .disabled(viewModel.isGenerating)
                    
                    if viewModel.time != -1 {
                        Button("Save") {
                            Task {
                                await saveData()
                            }
                        }
                        .disabled(viewModel.isGenerating)
                        Text("\(Int(viewModel.time)) second")
                    }
                }
                .buttonStyle(.borderedProminent)
                .padding(3)
            }
        }
    }
}
#Preview{
    MainView(viewModel: ViewModel())
}
