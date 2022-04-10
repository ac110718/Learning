import { createServer } from 'http'
import staticHandler from 'serve-handler'
import ws from 'ws'
import Redis from 'ioredis'

const redisSub = new Redis() // different channels required as certain methods become unavailable
const redisPub = new Redis()

const server = createServer((req, res) => {
    return staticHandler(req, res, { public: 'www' })
})

const wss = new ws.Server({ server })
wss.on('connection', client => {
    console.log('Client connected')
    client.on('message', msg => {
        console.log(`Message: ${msg}`)
        // can connect from different ports or launch different ports
        // de-couple port launch from broadcasting to same redis channel
        redisPub.publish('chat_messages', msg) // public to this channel
    })
})

redisSub.subscribe('chat_messages')
redisSub.on('message', (channel, msg) => {
    for (const client of wss.clients) {
        if (client.readyState === ws.OPEN) {
            client.send(msg)
        }
    }
})

server.listen(process.argv[2] || 8080)