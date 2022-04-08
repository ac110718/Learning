import zeromq from 'zeromq'
import { ZmqMiddlewareManager } from './zmqMiddlewareManager.js'
import { jsonMiddleware } from './jsonMiddleware.js'
import { zlibMiddleware } from './zlibMiddleware.js'

async function main () {
    const socket = zeromq.createSocket("rep")
    await socket.bind('tcp://127.0.0.1:5000')

    const zmqm = new ZmqMiddlewareManager(socket)
    zmqm.use(zlibMiddleware()) // inflate
    zmqm.use(jsonMiddleware()) // deserialize
    // logging inbound step
    zmqm.use({
        async inbound (message) {
            console.log('Received', message)
            if (message.action === 'ping') {
                await this.send({ action: 'pong', echo: message.echo })
            }
            return message
        }
    })

    console.log('Server started')
}

main()