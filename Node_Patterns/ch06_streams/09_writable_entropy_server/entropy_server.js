import { createServer } from 'http'
import Chance from 'chance'

const chance = new Chance()

const server = createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' })
    let count = 1
    while (chance.bool({ likelihood: 95 })) {
        res.write(`${count.toString().padEnd(2)} ${chance.string()}\n`)
        count++
    }
    res.end('\n\n')
    res.on('finish', () => console.log('All data sent'))
})

server.listen(8080, () => {
    console.log('listening on http://localhost:8080')
})