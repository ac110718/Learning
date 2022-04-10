import zmq from 'zeromq'
import delay from 'delay'
import { generateTasks } from './generateTasks.js'

const ALPHABET = 'abcdefghijklmnopqrstuvwxyz'
const BATCH_SIZE = 10000

const [, , maxLength, searchHash] = process.argv

async function main () {
    const ventilator = new zmq.socket("push")
    ventilator.bindSync('tcp://127.0.0.1:5016') // note port 5016
    await delay(1000) // wait for all workers to connect

    const generatorObj = generateTasks(searchHash, ALPHABET, maxLength, BATCH_SIZE)
    for (const task of generatorObj) {
        await ventilator.send(JSON.stringify(task))
        console.log(task)
    }

    // const fromVentilator = zmq.socket("pull")
    // fromVentilator.connect("tcp://127.0.0.1:5016")
    // fromVentilator.on("message", (rawMessage) => {console.log("HALO")})
}

main().catch(err => console.error(err))