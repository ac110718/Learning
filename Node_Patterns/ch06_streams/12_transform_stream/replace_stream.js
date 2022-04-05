import { Transform } from 'stream'

export class ReplaceStream extends Transform {
    constructor (searchStr, replaceStr, options) {
        super({ ...options })
        this.searchStr = searchStr
        this.replaceStr = replaceStr
        this.tail = ''
    }

    _transform (chunk, encoding, callback) {
        const pieces = (this.tail + chunk).split(this.searchStr) // make sure search encaptures leftover that was unprocessed
        const lastPiece = pieces[pieces.length - 1]
        const tailLen = this.searchStr.length - 1
        this.tail = lastPiece.slice(-tailLen) // make sure to save enough of search length to examine when chunk holdover
        pieces[pieces.length - 1] = lastPiece.slice(0, -tailLen) // last bit considered "processed"

        this.push(pieces.join(this.replaceStr)) // push into read stream the "processed" parts with replacement string
        callback()
    }

    _flush (callback) {
        this.push(this.tail) // last call for unprocessed
        callback()
    }
}