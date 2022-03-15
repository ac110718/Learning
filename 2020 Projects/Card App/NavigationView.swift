//
//  NavigationView.swift
//  Card App
//
//  Created by Allen Chan on 7/30/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import SwiftUI

struct NavigationView: View {
    @ObservedObject var store = CardStore()
    @State private var showPopover = false
    @State private var fileName : String = ""
    var body: some View {
        return VStack {
            HStack {
                
                TextField(self.store.fileList[self.store.activeFile], text: $fileName, onCommit: {
                    CardDocument(self.store.fileList[self.store.activeFile]).save(self.fileName)
                    self.store.setName(self.fileName)
                    self.fileName = self.store.fileList[self.store.activeFile]
                })
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                Image(systemName:"plus.square.on.square")
                    .onTapGesture {
                        self.store.addCard(named:"NewCard\(self.store.fileList.count+1)")
                        self.fileName = self.store.fileList[self.store.activeFile]
                    }
                Image(systemName:"folder")
                    .onTapGesture {
                        self.showPopover = true
                    }
                    .popover(
                        isPresented: $showPopover,
                        content: {
                            List {
                                ForEach(self.store.fileList, id: \.self) { fileName in
                                    HStack {
                                        HStack {
                                            Text(fileName)
                                            Spacer()
                                        }
                                            .contentShape(Rectangle())
                                            .onTapGesture {
                                                self.store.setFile(fileName)
                                                self.fileName = fileName
                                                self.showPopover = false
                                            }
                                        Image(systemName: "trash.circle").imageScale(.medium).foregroundColor(Color.gray)
                                            .padding(.horizontal, 20)
                                            .onTapGesture {
                                                self.store.deleteCard(named: fileName)
                                        }
                                    }
                                }
                                HStack {
                                    Text("Add Card").foregroundColor(Color.blue)
                                    Spacer()
                                }
                                    .contentShape(Rectangle())
                                    .onTapGesture {
                                        self.store.addCard(named:"NewCard\(self.store.fileList.count+1)")
                                    }
                            }
                        }
                    )
            }
            CardView(document: CardDocument(self.store.fileList[self.store.activeFile]))
            .zIndex(-2)
        }
        .padding(.horizontal, 20)
    }
}


