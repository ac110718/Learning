//
//  CardStore.swift
//  Card App
//
//  Created by Allen Chan on 7/31/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import SwiftUI
import Combine

class CardStore: ObservableObject
{
    @Published var fileList = [String]()
    var activeFile = 0
    
    private var autosaveCancellable: AnyCancellable?

    init() {
        let defaultsKey = "CardStore.default1"
        
        fileList = UserDefaults.standard.array(forKey: defaultsKey) as? [String] ?? Array(arrayLiteral: "untitled")
        if (fileList.count == 0) {
            fileList.append("untitled")
        }
        
        autosaveCancellable = $fileList.sink { fileList in
            UserDefaults.standard.set(fileList, forKey: defaultsKey)
        }
    }
    
    func setName(_ name: String) {
        fileList[activeFile] = name
        fileList = Array(Set(fileList)).sorted()
        if let i = fileList.firstIndex(where: {$0 == name}) {
            activeFile = i
        }
    }
    
    func addCard(named name: String) {
        fileList.append(name)
        fileList = Array(Set(fileList)).sorted()
        if let i = fileList.firstIndex(where: {$0 == name}) {
            activeFile = i
        }
    }
    
    func deleteCard(named name: String) {
        if (fileList.count > 1) {
            fileList = fileList.filter {$0 != name}
            activeFile = max(activeFile-1, 0)
            UserDefaults.standard.set(nil, forKey: "CardModel.\(name)")
        }
    }
    
    func setFile(_ name: String) {
        if let i = fileList.firstIndex(where: {$0 == name}) {
            activeFile = i
        }
    }
    
}
