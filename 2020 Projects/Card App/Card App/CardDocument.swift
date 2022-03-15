//
//  CardDocument.swift
//  Card App
//
//  Created by Allen Chan on 7/26/20.
//  Copyright © 2020 Allen Chan. All rights reserved.
//

import SwiftUI
import Combine

class CardDocument: ObservableObject
{
    @Published private var cardModel: CardModel
    
    private var autosaveCancellable: AnyCancellable?

    init(_ key: String) {
        
        let defaultsKey = "CardModel.\(key)"
        cardModel = CardModel(json: UserDefaults.standard.data(forKey: defaultsKey)) ?? CardModel()
        autosaveCancellable = $cardModel.sink { cardModel in
            UserDefaults.standard.set(cardModel.json, forKey: defaultsKey)
        }
        fetchImageData()
    }
    
    @Published private(set) var cardImage: UIImage?
    
    func save(_ key: String) {
        UserDefaults.standard.set(cardModel.json, forKey: "CardModel.\(key)")
    }

    var textItems: [CardModel.TextItem] { cardModel.textItems }
    var graphic: String { cardModel.cardImage }
    var activeIndex: Int = 0
    var activeText: String = ""
    var cardBackground: Int {cardModel.cardBackground }
    var fontColor: Int {cardModel.textItems[activeIndex].fontColor}
    var fontSize: CGFloat {CGFloat(cardModel.textItems[activeIndex].size)}
    var fontFamily: String {cardModel.textItems[activeIndex].fontFamily}
    var textWidth: CGFloat {CGFloat(cardModel.textItems[activeIndex].textWidth)}
    var textAlign: Int {Int(cardModel.textItems[activeIndex].alignment)}
    var isBold: Bool {cardModel.textItems[activeIndex].isBold}
    var isItalic: Bool {cardModel.textItems[activeIndex].isItalic}
    var picLocation : CGPoint {CGPoint(x: CGFloat(cardModel.picX), y: CGFloat(cardModel.picY))}
    var picScale : CGFloat {CGFloat(cardModel.picScale)}
    var picAngle : CGFloat {CGFloat(cardModel.picAngle)}
    var coinLocation : CGPoint {CGPoint(x: CGFloat(cardModel.coinX), y: CGFloat(cardModel.coinY))}
    var isCoin: Bool {cardModel.isCoin }
    
    var picURL: URL? {
        get {
            cardModel.picURL
        } set {
            cardModel.picURL = newValue
            fetchImageData()
        }
    }
    
    private var fetchImageCancellable: AnyCancellable?
    
    private func fetchImageData() {
        cardImage = nil
        if let url = self.cardModel.picURL {
            fetchImageCancellable?.cancel()
            print(url)
            fetchImageCancellable = URLSession.shared.dataTaskPublisher(for: url)
                .map {data, urlResponse in UIImage(data: data)}
                .receive(on: DispatchQueue.main)
                .replaceError(with: nil)
                .assign(to: \.cardImage, on: self)
        }
    }
    
    // MARK: - Intent(s)
    
    func setCoin() {
        cardModel.isCoin = !cardModel.isCoin
    }
    
    func setBorder(_ toggle: Bool) {
        cardModel.textItems[activeIndex].textBorder = toggle
        DispatchQueue.main.asyncAfter(deadline: .now() + 5) {
            self.cardModel.textItems[self.activeIndex].textBorder = false
        }
    }
    
    func deletePic() {
        self.picURL = nil
        cardModel.picX = 250
        cardModel.picY = 350
        cardModel.picScale = 1
    }
    
    func setPicScale(_ scale: CGFloat) {
        cardModel.picScale = Float(scale)
    }
    
    func addPicURL(_ text: String) {
        self.picURL = URL(string: text)
    }
    
    func addTextItem(_ text: String, at location: CGPoint, size: CGFloat) {
        cardModel.addText(text, x: Int(location.x), y: Int(location.y), size: Int(size), isBold: false, isItalic: false, fontFamily: "Helvetica Neue", alignment: 0)
    }
    
    func setActiveIndex(_ textItem: CardModel.TextItem) {
        if let index = cardModel.textItems.firstIndex(where: { $0.id == textItem.id }) {
            activeIndex = index
            activeText = cardModel.textItems[activeIndex].text
        }
    }
    
    func setBold() {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].isBold = !cardModel.textItems[activeIndex].isBold
            print("hi")
        }
    }
    
    func setItalic() {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].isItalic = !cardModel.textItems[activeIndex].isItalic
        }
    }
    
    func updateText(_ text: String) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].text = text
            activeText = text
        }
    }
    
    func updateImage(_ cardImage: String) {
        cardModel.cardImage = cardImage
    }
    
    func updateBackground(_ int: Int) {
        cardModel.cardBackground = int
    }
    
    func updateColor(_ int: Int) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].fontColor = int
        }
    }
    
    func updateSize(_ size: CGFloat) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].size = Int(size)
        }
    }
    
    func updateFamily(_ string: String) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].fontFamily = string
        }
    }
    
    func remove() {
        if (cardModel.textItems.count > 1) {
            cardModel.textItems = cardModel.textItems.filter {$0.id != cardModel.textItems[activeIndex].id}
            activeIndex = max(0,activeIndex-1)
            activeText = cardModel.textItems[activeIndex].text
        }
    }
    
    func updateLocation(_ value: CGPoint) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].x = Int(value.x)
            cardModel.textItems[activeIndex].y = Int(value.y)
        }
    }
    
    func updateCoinLocation(_ value: CGPoint) {
        cardModel.coinX = Int(value.x)
        cardModel.coinY = Int(value.y)
    }
    
    func updatePicLocation(_ value: CGPoint) {
        cardModel.picX = Int(value.x)
        cardModel.picY = Int(value.y)
    }
    
    func updatePicAngle(_ value: Double) {
        cardModel.picAngle = Float(value)
    }
    
    func updateWidth(_ value: CGFloat) {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].textWidth = Int(value)
        }
    }
    
    func toggleAlignment() {
        if (cardModel.textItems.count > 0) {
            cardModel.textItems[activeIndex].alignment += 1
        }
    }
}

extension CardModel.TextItem {
    var fontSize: CGFloat { CGFloat(self.size) }
    var location: CGPoint { CGPoint(x: CGFloat(x), y: CGFloat(y)) }
}
