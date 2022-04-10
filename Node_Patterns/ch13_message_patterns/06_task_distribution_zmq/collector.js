import zmq from 'zeromq'

async function main () {
    const sink = new zmq.socket("pull")
    sink.connect('tcp://127.0.0.1:5017')

    sink.on("message", (rawMessage) => {
        console.log('Message from worker: ', rawMessage.toString())
    })
}

main().catch(err => console.error(err))