import { Writable } from 'stream'
import { promises as fs } from 'fs'
import { dirname } from 'path'
import mkdirp from 'mkdirp-promise'

export class ToFileStream extends Writable {
    constructor (options) {
        super({ ...options, objectMode: true })
    }
    
    // custom writable for struct that has path and content objects
    _write (chunk, encoding, cb) {
        mkdirp(dirname(chunk.path))
            .then(() => fs.writeFile(chunk.path, chunk.content))
            .then(() => cb())
            .catch(cb)
    }
}