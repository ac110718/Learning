import { createServer } from 'http'
import Chance from 'chance'

const chance = new Chance()

const server = createServer((req, res) => {
    let count = 1
    res.writeHead(200, { 'Content-Type': 'text/plain' })
    function generateMore() {
        while (chance.bool({ likelihood: 95 })) {
            const randomChunk = chance.string({ length: (16 * 1024) - 1 }) // 16kB is near high water mark
            const shouldContinue = res.write(`CHUNK ${count.toString().padEnd(2)}:${randomChunk}\n`)
            count++
            if (!shouldContinue) {
                console.log('back-pressure')
                return res.once('drain', generateMore) // call self once on 'drain' event from res
            }
        }
        res.end('\n\n')
    }
    generateMore()
    res.on('finish', () => console.log('All data sent'))
})

server.listen(8080, ()=> {
    console.log('listening on http://localhost:8080')
})