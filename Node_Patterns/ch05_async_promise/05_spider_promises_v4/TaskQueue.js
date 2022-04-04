export class TaskQueue {
    constructor (concurrency) {
        this.concurrency = concurrency
        this.running = 0
        this.queue = []
    }

    runTask (task) {
        return new Promise((resolve, reject) => {
            this.queue.push(() => {
                return task().then(resolve, reject) // pass the resolve, reject after task has been run back to caller which pushed into Queue
            })
            process.nextTick(this.next.bind(this))
        })
    }

    next () {
        while (this.running < this.concurrency && this.queue.length) {
            const task = this.queue.shift()
            task().finally(() => {
                this.running--
                this.next()
            })
            this.running++
        }
    }
}