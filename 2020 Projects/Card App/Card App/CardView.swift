//
//  CardView.swift
//  Card App
//
//  Created by Allen Chan on 7/26/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import SwiftUI

struct CardView: View {

    @ObservedObject var document: CardDocument
    @State var activeText: String = "Edit Text Here"
    @State var fontColor: Int = 0
    @State var fontSize: CGFloat = 15
    @State var fontFamily: String = ""
    @State var textWidth: CGFloat = 270
    @State var activeImage: String = "birthday01"
    @State var cardBackgroundColor: Int = 0
    @State var showURLBox = false
    var colors: [Color] = [
        Color.white,
        Color(red: 5/255, green: 27/255, blue: 50/255),
        Color(red: 6/255, green: 46/255, blue: 75/255),
        Color(red: 140/255, green: 30/255, blue: 30/255),
        Color(red: 140/255, green: 30/255, blue: 30/255),
        Color(red: 250/255, green: 234/255, blue: 209/255),
        Color(red: 0.8, green: 0.8, blue: 0.8),
        Color(red: 0.5, green: 0.5, blue: 0.5),
        Color(red: 0.3, green: 0.3, blue: 0.3),
        Color.black
    ]
    var alignment: [TextAlignment] = [.leading, .center, .trailing]
    
    var fonts: [String] = ["Arial", "Georgia", "Helvetica Neue", "Noteworthy-Light", "Times New Roman"]
    
    func cardBackground() -> Color {
        switch self.document.graphic {
            case "birthday01"   : return self.colors[1]
            case "birthday02"   : return self.colors[2]
            case "cny01"        : return self.colors[3]
            case "cny02"        : return self.colors[4]
            case "wedding03"    : return self.colors[5]
            default             : return self.colors[0]
        }
    }
    
    func refresh() {
        if (self.document.textItems.count>0) {
            self.activeText = "Edit Text Here"
            self.fontColor = self.document.fontColor
            self.fontSize = self.document.fontSize
            self.fontFamily = self.document.fontFamily
            self.activeImage = self.document.graphic
            self.cardBackgroundColor = self.document.cardBackground
            self.textWidth = self.document.textWidth
            self.showURLBox = false
       }

    }
    
    var body: some View {
        return VStack {

            
            Toolbar(document: document, activeText: $activeText, activeImage: $activeImage, colors: colors, cardBackgroundColor: $cardBackgroundColor, fontColor: $fontColor, fontSize: $fontSize, fontFamily: $fontFamily, fonts: fonts, textWidth: $textWidth, showURLBox: $showURLBox)
                .padding(.bottom, 20)
            
            ScrollView(.vertical) {
                ZStack {
                    ForEach(self.document.textItems) { textItem in
                        Text(textItem.text)
                            .font(appliedStyle(for: textItem))
                            .multilineTextAlignment(self.alignment[textItem.alignment%3])
                            .foregroundColor(self.colors[textItem.fontColor])
                            .overlay(Rectangle().stroke(Color.gray, lineWidth: textItem.textBorder ? 1 : 0))
                            .shadow(color: Color.white, radius: 0.0)
                            .position(textItem.location)
                            .frame(maxWidth: CGFloat(textItem.textWidth))
                            .gesture(DragGesture()
                                .onChanged({ value in
                                    self.document.setActiveIndex(textItem)
                                    self.document.updateLocation(value.location)
                                })
                                .onEnded({ value in
                                    self.document.setActiveIndex(textItem)
                                    self.activeText = self.document.activeText
                                    self.fontColor = self.document.fontColor
                                    self.fontSize = self.document.fontSize
                                    self.fontFamily = self.document.fontFamily
                                })
                            )
                            .onTapGesture {
                                self.document.setActiveIndex(textItem)
                                self.activeText = self.document.activeText
                                self.fontColor = self.document.fontColor
                                self.fontSize = self.document.fontSize
                                self.fontFamily = self.document.fontFamily
                                self.showURLBox = false
                            }
                            .zIndex(1)
                        .onAppear{ self.refresh()}
                        
                    }
                    VStack {
                        ZStack {
                            Image(self.document.graphic)
                                .resizable()
                                .aspectRatio(contentMode: .fit)
                                .zIndex(1)
                                .frame(minHeight: 260, maxHeight: 270)
                            self.cardBackground()
                        }
                        Rectangle()
                            .fill(self.colors[self.document.cardBackground])
                            .frame(height:270)
                            .zIndex(1)
                            
                    }
                    .padding(0)
                    
                    if (self.document.isCoin) {
                        Image(systemName: "gift.fill")
                            .resizable()
                            .frame(width: 30, height: 30)
                            .shadow(radius: 10)
                            .foregroundColor(Color.gray)
                            .zIndex(2)
                            .opacity(0.5)
                            .position(self.document.coinLocation)
                            .gesture(DragGesture()
                            .onChanged({ value in
                                self.document.updateCoinLocation(value.location)
                            }))
                    }
                    
                        
                    if (self.document.cardImage != nil) {
                          Image(uiImage: self.document.cardImage!)
                                .resizable()
                                .aspectRatio(contentMode: .fit)
                                .overlay(Rectangle().stroke(Color.white, lineWidth:10))
                                .frame(width: 100, height: 100)
                                .position(self.document.picLocation)
                                .shadow(radius: 5)
                            .scaleEffect(self.document.picScale)
                            .rotationEffect(Angle(degrees: Double(self.document.picAngle)))
                                .gesture(DragGesture()
                                    .onChanged({ value in
                                        self.document.updatePicLocation(value.location)
                                    }))
                        .gesture(MagnificationGesture()
                            .onChanged {amount in
                                self.document.setPicScale(amount)
                            }
                        )
                        .simultaneousGesture(RotationGesture()
                            .onChanged {angle in
                                self.document.updatePicAngle(Double(angle.degrees))
                            }
                        )
                      }
                }
            }
                .background(self.colors[self.document.cardBackground])
                .shadow(radius: 10)
                .zIndex(-1)
        }
    }
}

private func appliedStyle (for textItem: CardModel.TextItem) -> Font {
    var appliedStyle = Font
            .custom(textItem.fontFamily, size: textItem.fontSize)
            .weight(textItem.isBold ? .heavy : .regular)
    if (textItem.isItalic) { appliedStyle = appliedStyle.italic() }
    return appliedStyle
}




    
