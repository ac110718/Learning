//
//  Toolbar.swift
//  Card App
//
//  Created by Allen Chan on 7/26/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import SwiftUI

struct Toolbar: View {
    @ObservedObject var document: CardDocument
    @Binding var activeText: String
    @Binding var activeImage: String
    var colors: [Color]
    @Binding var cardBackgroundColor: Int
    @Binding var fontColor: Int
    @Binding var fontSize: CGFloat
    @Binding var fontFamily: String
    var fonts: [String]
    @Binding var textWidth: CGFloat
    @State var picURL = ""
    @Binding var showURLBox: Bool
    
    var body: some View {
        
        
        return VStack {
            HStack {
                Image(systemName: "pencil.and.ellipsis.rectangle").imageScale(.medium).foregroundColor(colors[2])
                    .onTapGesture {
                        self.document.addTextItem("New Text Box", at: CGPoint(x: 150, y: 350), size: 20.0)
                        self.document.setActiveIndex(self.document.textItems[self.document.textItems.count-1])
                        self.activeText = self.document.activeText
                        self.fontColor = self.document.fontColor
                        self.fontSize = self.document.fontSize
                        self.fontFamily = self.document.fontFamily
                }
                Image(systemName: "pencil.slash").imageScale(.medium).foregroundColor(colors[2])
                   .onTapGesture { self.document.remove() }

                Image(systemName: "bold").imageScale(.medium).foregroundColor(colors[self.document.isBold ? 2 : 6])
                    .onTapGesture { self.document.setBold() }
                Image(systemName: "italic").imageScale(.medium).foregroundColor(colors[self.document.isItalic ? 2 : 6])
                    .onTapGesture { self.document.setItalic() }
                Image(systemName: self.document.textAlign%3 == 0 ? "text.alignleft" :
                    (self.document.textAlign%3 == 1 ? "text.aligncenter" : "text.alignright"))
                    .imageScale(.medium)
                    .onTapGesture {
                        self.document.toggleAlignment()
                        print(self.document.textAlign)
                }
                Image(systemName: "camera.viewfinder").imageScale(.medium)
                    .onTapGesture { self.showURLBox = !self.showURLBox}
                                   
               Image(systemName: "pin.slash").imageScale(.medium)
                   .onTapGesture { self.document.deletePic() }
                   .zIndex(1)
                HStack {
                    Image(systemName: "arrow.left.and.right.square")
                    Slider(value: self.$textWidth.onChange(self.document.updateWidth), in: 50...270, step:2)
                        .accentColor(Color.init(UIColor(red: 0.9, green: 0.9, blue: 0.9, alpha: 1.0)))
                    Image(systemName: "textformat.size").zIndex(1)
                    Slider(value: self.$fontSize.onChange(self.document.updateSize), in: 10...40, step:1)
                        .accentColor(Color.init(UIColor(red: 0.7, green: 0.7, blue: 0.7, alpha: 1.0)))
                        .opacity(0.8)
                    }
                        .padding(0)
                
                    
                    Picker(selection: self.$fontFamily.onChange(self.document.updateFamily), label: EmptyView()) {
                        ForEach(0 ..< self.fonts.count) {  index in
                            ZStack {
                                Text((self.fonts[index]).components(separatedBy: CharacterSet.letters.inverted).first!)
                                    .foregroundColor(Color.black)
                                    .font(Font.custom(self.fonts[index], size: 14))
                                    .frame(width: 70, height: 30)
                                    .overlay(
                                        RoundedRectangle(cornerRadius: 5, style: .continuous)
                                            .stroke(self.colors[8], lineWidth: 1)
                                    )
                            }
                                .tag(self.fonts[index])
                        }
                    }
                         .pickerStyle(WheelPickerStyle())
                         .zIndex(-2)
                         .frame(maxWidth: 80, maxHeight: 30).clipped()
            }
            .zIndex(1000)
//
            HStack {
                
                
                ZStack {
                    TextField(self.activeText, text: $activeText.onChange(self.document.updateText))
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .opacity(showURLBox ? 0 : 1)
                    HStack {
                        TextField("Paste Image URL Here", text: self.$picURL, onCommit: {
                            self.document.addPicURL(self.picURL)
                        })
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .opacity(showURLBox ? 1 : 0)
                    }
                }
                
                Picker(selection: self.$fontColor.onChange(self.document.updateColor), label: EmptyView()) {
                                   ForEach(0 ..< self.colors.count) {  index in
                                       ZStack {
                                           Image(systemName: "textformat").imageScale(.small).foregroundColor(Color.gray).zIndex(1)
                                           RoundedRectangle(cornerRadius: 5, style: .continuous)
                                           .fill(self.colors[index])
                                           .frame(width: 27, height: 27)
                                           .overlay(
                                               RoundedRectangle(cornerRadius: 5, style: .continuous)
                                                   .stroke(self.colors[8], lineWidth: 1)
                                                   .frame(width: 25, height: 25)
                                           )
                                       }
                                           .tag(index)
                                   }
                               }
                                   .pickerStyle(WheelPickerStyle())
                                   .zIndex(-2)
                                   .frame(maxWidth: 35, maxHeight: 30).clipped()

            }
//
            HStack {
                
                Image(systemName: "gift.fill").resizable().frame(maxWidth: 20, maxHeight:20).foregroundColor(self.document.isCoin ? colors[1] : colors[6])
                    .onTapGesture { self.document.setCoin() }
                
                Picker(selection: $activeImage.onChange(self.document.updateImage), label: EmptyView()) {
                    cardIcon(icon: "🎂", sub: "1").tag("birthday01")
                    cardIcon(icon: "🎂", sub: "2").tag("birthday02")
                    cardIcon(icon: "🎂", sub: "3").tag("birthday03")
                    cardIcon(icon: "🐲", sub: "1").tag("cny01")
                    cardIcon(icon: "🐲", sub: "2").tag("cny02")
                    cardIcon(icon: "🥂", sub: "1").tag("wedding01")
                    cardIcon(icon: "🥂", sub: "2").tag("wedding02")
                    cardIcon(icon: "🥂", sub: "3").tag("wedding03")
                }.pickerStyle(SegmentedPickerStyle())
                

                Picker(selection: self.$cardBackgroundColor.onChange(self.document.updateBackground), label: EmptyView()) {
                    ForEach(0 ..< self.colors.count) { index in
                        ZStack {
                            Image(systemName: "book").imageScale(.small).foregroundColor(Color.gray).zIndex(1)
                            RoundedRectangle(cornerRadius: 5, style: .continuous)
                            .fill(self.colors[index])
                            .frame(width: 27, height: 27)
                            .overlay(
                                RoundedRectangle(cornerRadius: 5, style: .continuous)
                                    .stroke(self.colors[8], lineWidth: 1)
                                    .frame(width: 25, height: 25)
                            )
                        }
                            .tag(index)
                    }
                }
                    .pickerStyle(WheelPickerStyle())
                    .frame(maxWidth: 35, maxHeight: 30).clipped()
            }
            .zIndex(-1)
        }
        
    }
}

struct cardIcon: View {
    var icon: String
    var sub: String
    var body: some View {
            Text(icon).font(.callout)
    }
}

extension Binding {
    func onChange(_ handler: @escaping (Value) -> Void) -> Binding<Value> {
        return Binding(
            get: { self.wrappedValue },
            set: { selection in
                self.wrappedValue = selection
                handler(selection)
        })
    }
}

