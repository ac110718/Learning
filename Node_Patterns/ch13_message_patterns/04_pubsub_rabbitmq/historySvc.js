import { createServer } from 'http'
import level from 'level'
import timestamp from 'monotonic-timestamp'
import JSONStream from 'JSONStream'
import amqp from 'amqplib'

async function main () {
    const db = level('./msgHistory')
    const connection = await amqp.connect('amqp://localhost')
    // listen for anything on chat channel
    const channel = await connection.createChannel()
    await channel.assertExchange('chat', 'fanout') // make sure exchange exists or create, type fanout to connect to all nodes
    const { queue } = channel.assertQueue('chat_history') // queue is for consumption. Exchange is for sorting / subscribing
    await channel.bindQueue(queue, 'chat') // subscribe to chat exchange

    channel.consume(queue, async msg => {
        const content = msg.content.toString()
        console.log(`Saving message: ${content}`)
        await db.put(timestamp(), content)
        channel.ack(msg) // if not acknowledged, keep in the queue to be processed again
    })

    // respond with contents of database via stream
    createServer((req, res) => {
        res.writeHead(200)
        db.createValueStream()
            .pipe(JSONStream.stringify())
            .pipe(res)
    }).listen(8090)
}

main().catch(err => console.error(err))