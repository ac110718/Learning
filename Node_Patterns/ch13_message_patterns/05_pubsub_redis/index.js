import { createServer } from 'http'
import staticHandler from 'serve-handler'
import ws from 'ws'
import Redis from 'ioredis'

// streams allow for access and processing of same stream in different ways
const redisClient = new Redis()
const redisClientXRead = new Redis()

const server = createServer((req, res) => {
    return staticHandler(req, res, { public: 'www' })
})

const wss = new ws.Server({ server })
wss.on('connection', async client => {
    console.log('Client connected' )
    client.on('message', msg => {
        console.log(`Message: ${msg}`)
        // name of stream, * auto generate ID monotonic, key, value
        redisClient.xadd('chat_stream', '*', 'message', msg)
    })

    // load history
    const logs = await redisClient.xrange(
        'chat_stream', '-', '+') // highest and lowest IDs
    // destructuring of something like [recordId, [propertyId, message]]
    for (const [, [, message]] of logs) {
        client.send(message)
    }
})

function broadcast (msg) {
    for (const client of wss.clients) {
        if (client.readyState === ws.OPEN) {
            client.send(msg)
        }
    }
}

let lastRecordId = '$' // highest ID currently in stream

async function processStreamMessages () {
    while (true) {
        const [[, records ]] = await redisClientXRead.xread(
            // block until new message arrive, timeout or 0 forever waiting, details of stream,
            // last record where we want to start reading the stream
            'BLOCK', '0', 'STREAMS', 'chat_stream', lastRecordId)
            for (const [recordId, [, message]] of records) {
                console.log(`Message from stream: ${message}`)
                broadcast(message)
                lastRecordId = recordId
            }
    }
}

processStreamMessages().catch(err => console.error(err))

server.listen(process.argv[2] || 8080)