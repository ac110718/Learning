import { PassThrough } from 'stream'

let bytesWritten = 0
const monitor = new PassThrough()
monitor.on('data', (chunk) => {
    bytesWritten += chunk.length
})
monitor.on('finish', () => {
    console.log(`${bytesWritten} bytes written`)
}) // no tangible side effects, just recording properties of the stream

monitor.write('Hello!')
monitor.end()