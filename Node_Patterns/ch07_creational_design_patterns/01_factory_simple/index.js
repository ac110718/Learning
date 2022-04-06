import { Image } from './image.js'

function createImage (name) {
    // what if you want different logic in here?
    return new Image(name) // indirection to create under Factory function
}

const image = createImage('photo.jpeg')
console.log(image)