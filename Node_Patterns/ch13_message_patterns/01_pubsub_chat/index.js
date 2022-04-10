import { createServer } from 'http'
import staticHandler from 'serve-handler'
import ws from 'ws'

const server = createServer((req, res) => {
    return staticHandler(req, res, { public: 'www' }) // serve from public www directly
})

// pub sub pattern.. publisher doesn't know in advance who recipients are, making two sides loosely coupled

const wss = new ws.Server({ server })
wss.on('connection', client => {
    console.log('Client connected')
    client.on('message', msg => {
        console.log(`Message: ${msg}`)
        broadcast(msg) // send to all connected clients
    })
})

function broadcast (msg) {
  for (const client of wss.clients) {
    if (client.readyState === ws.OPEN) {
      client.send(msg)
    }
  }
}

server.listen(process.argv[2] || 8080)