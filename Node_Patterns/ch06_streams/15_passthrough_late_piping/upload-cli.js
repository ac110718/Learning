import { createReadStream } from 'fs'
import { createBrotliCompress } from 'zlib'
import { PassThrough } from 'stream'
import { basename } from 'path'
import { upload } from './upload.js'

const filepath = process.argv[2]
const filename = basename(filepath)
const contentStream = new PassThrough()

upload(`${filename}.br`, contentStream)
    .then((response) => {
        console.log(`Server response: ${response.data}`)
    })
    .catch((err) => {
        console.error(err)
        process.exit(1)
    })

createReadStream(filepath)
    .pipe(createBrotliCompress())
    .pipe(contentStream) // this serves as connector stream to upload function