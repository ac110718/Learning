import { createServer } from 'http'
import staticHandler from 'serve-handler'
import ws from 'ws'
import yargs from 'yargs'
import zmq from 'zeromq'

const server = createServer((req, res) => {
    return staticHandler(req, res, { public: 'www' })
})

let pubSocket
function initializeSockets () {
    pubSocket = new zmq.socket("pub")
    pubSocket.bindSync(`tcp://127.0.0.1:${yargs.argv.pub}`)

    const subSocket = new zmq.socket("sub")
    const subPorts = [].concat(yargs.argv.sub)
    for (const port of subPorts) {
        console.log(`Subscribing to ${port}`)
        subSocket.connect(`tcp://127.0.0.1:${port}`)
    }
    subSocket.subscribe('chat')

    subSocket.on("message", (topic, message) => {
        console.log(`Message on ${topic} channel: ${message}`)
        broadcast(message.toString())
    })
}

initializeSockets()

const wss = new ws.Server({ server })
wss.on('connection', client => {
    console.log('Client connected')
    client.on('message', msg => {
        console.log(`Message: ${msg}`)
        broadcast(msg)
        pubSocket.send(["chat", msg])
    })
})

function broadcast (msg) {
    for (const client of wss.clients) {
        if (client.readyState === ws.OPEN) {
            client.send(msg)
        }
    }
}

server.listen(yargs.argv.http || 8080)