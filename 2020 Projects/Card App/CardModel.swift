//
//  CardModel.swift
//  Card App
//
//  Created by Allen Chan on 7/26/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import Foundation

struct CardModel: Codable {
    var textItems : [TextItem] = [TextItem(id: 0, text: "[Message Here]", x: 125, y: 350, size: 15, isBold: false, isItalic: false, fontFamily: "Arial", alignment: 0, fontColor: 3, textWidth: 270)]
    var cardImage = "birthday01"
    var cardBackground = 0
    var picURL : URL?
    var picX = 250
    var picY = 350
    var picScale : Float = 1
    var picAngle : Float = 0
    var coinX = 150
    var coinY = 400
    var isCoin = false
    
    var json: Data? {
        return try? JSONEncoder().encode(self)
    }
    
    init?(json: Data?) {
        if json != nil, let newCardModel = try? JSONDecoder().decode(CardModel.self, from: json!) {
            self = newCardModel
        } else {
            return nil
        }
    }
    
    init() { }
    
    struct TextItem: Identifiable, Codable {
        let id: Int
        var text: String
        var x: Int
        var y: Int
        var size: Int
        var isBold: Bool
        var isItalic: Bool
        var fontFamily: String
        var alignment: Int
        var fontColor: Int
        var textWidth: Int
        var textBorder: Bool
        
        fileprivate init(id: Int, text: String, x: Int, y: Int, size: Int, isBold: Bool, isItalic: Bool, fontFamily: String, alignment: Int, fontColor: Int, textWidth: Int) {
            self.id = id
            self.text = text
            self.x = x
            self.y = y
            self.size = size
            self.isBold = isBold
            self.isItalic = isItalic
            self.fontFamily = fontFamily
            self.alignment = alignment
            self.fontColor = fontColor
            self.textWidth = textWidth
            self.textBorder = false
        }
    }
    
    private var uniqueTextId = 1
    
    mutating func addText(_ text: String, x: Int, y: Int, size: Int, isBold: Bool, isItalic: Bool, fontFamily: String, alignment: Int) {
        textItems.append(TextItem(id: uniqueTextId, text: text, x: x, y: y, size: size, isBold: isBold, isItalic: isItalic, fontFamily: fontFamily, alignment: alignment, fontColor: 6, textWidth: 270))
        uniqueTextId += 1
    }
}
