import zmq from 'zeromq'
import { processTask } from './processTask.js'

async function main () {
    const fromVentilator = zmq.socket("pull")
    fromVentilator.connect("tcp://127.0.0.1:5016")
    
    const toSink = zmq.socket("push")
    toSink.connect('tcp://127.0.0.1:5017')

    fromVentilator.on("message", (rawMessage) => {
        console.log("working on it...")
        const found = processTask(JSON.parse(rawMessage.toString()))
        if (found) {
            console.log(`Found!! => ${found}`)
            toSink.send('Found: ${found}')
        }
    })
}

main().catch(err => console.error(err))