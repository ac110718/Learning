export class TaskQueue {
    constructor (concurrency) {
        this.concurrency = concurrency
        this.running = 0
        this.queue = []
    }

    pushTask (task) {
        this.queue.push(task)
        // iterate next() one more time on nextTick
        process.nextTick(this.next.bind(this)) // next function needs this context
        return this
    }

    next () {
        while (this.running < this.concurrency && this.queue.length) {
            const task = this.queue.shift() // take one out of the queue
            task(() => {
                this.running--
                process.nextTick(this.next.bind(this))
            })
            this.running++
        }
    }
}