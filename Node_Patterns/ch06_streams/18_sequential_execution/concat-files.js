import { createWriteStream, createReadStream } from 'fs'
import { Readable, Transform } from 'stream'

export function concatFiles (dest, files) {
    return new Promise((resolve, reject) => {
        const destStream = createWriteStream(dest)
        Readable.from(files) // streams in fileNAMES
            .pipe(new Transform({
                objectMode: true,
                transform (filename, enc, done) {
                    const src = createReadStream(filename)
                    src.pipe(destStream, { end: false }) // keep going
                    src.on('error', done)
                    src.on('end', done)
                }
            }))
            .on('error', reject)
            .on('finish', () => {
                destStream.end() // end at the outer level
                resolve()
            })
    })
}