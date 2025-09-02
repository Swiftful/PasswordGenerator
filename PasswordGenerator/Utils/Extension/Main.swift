//
//  Extensions.swift
//  Generator
//
//

import SwiftUI

extension MainView{
    func startGeneration() async {
        await clearData()
        await MainActor.run {
            status = "Initializing..."
            viewModel.isGenerating = true
        }
        
        let apiResult = await viewModel.Api()
        viewModel.code = apiResult
        
        if viewModel.code == -1 {
            await MainActor.run {
                status = "Error: Invalid parameters"
                viewModel.isGenerating = false
            }
            return
        }
        
        await MainActor.run {
            status = "Generating passwords..."
        }
        
        let startTime = await viewModel.Start()
        viewModel.time = startTime
        viewModel.isStart = true
        
        await MainActor.run {
            status = "Generation completed!"
            viewModel.isGenerating = false
        }
        
        try? await Task.sleep(nanoseconds: 2_000_000_000)
        await MainActor.run {
            status = ""
        }
    }
    
    func clearData() async {
        if viewModel.isStart {
            _ = await viewModel.Exit()
            viewModel.hashset = HashSet_Init()
            viewModel.code = -1
            viewModel.time = -1
            viewModel.isStart = false
        }
    }
    
    func saveData() async {
        PickFolder()
        
        await MainActor.run {
            status = "Writing to file..."
        }
        
        let success = await viewModel.WriteData(url: folderUrl, Data: viewModel.hashset)
        
        await MainActor.run {
            status = success ? "File saved successfully!" : "Error saving file"
        }
        
        // Clear status after 2 seconds
        try? await Task.sleep(nanoseconds: 2_000_000_000)
        await MainActor.run {
            status = ""
        }
    }
    
    func PickFolder() {
        let panel = NSOpenPanel()
        panel.canChooseDirectories = true
        panel.canCreateDirectories = true
        panel.allowedContentTypes = [.folder]
        if panel.runModal() == .OK {
            if let url = panel.url {
                folderUrl = url
            }
        }
    }
}
