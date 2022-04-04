export class TaskQueuePC {
    constructor (concurrency) {
        this.taskQueue = []
        this.consumerQueue = []

        // spawn consumers
        for (let i = 0; i < concurrency; i++) {
            this.consumer()
        }
    }

    // consumer instances
    async consumer () {
        while (true) {
            try {
                const task = await this.getNextTask() // always try to grab task. But if not resolved, just standby
                await task() // finish completion
            } catch (err) {
                console.error(err)
            }
        }
    }

    getNextTask () {
        return new Promise((resolve) => {
            if (this.taskQueue.length !== 0) {
                return resolve(this.taskQueue.shift()) // awaken consumer if taskQueue is non-empty. Resolve getNextTask()
            }
            this.consumerQueue.push(resolve) // if taskQueue IS indeed empty, then push consumer back to queue with empty resolve and go back to sleep
        })
    }

    runTask (task) {
        return new Promise((resolve, reject) => {
            const taskWrapper = () => {
                const taskPromise = task()
                taskPromise.then(resolve, reject)
                return taskPromise
            }
            // if there is non-busy consumer
            if (this.consumerQueue.length !== 0) {
                const consumer = this.consumerQueue.shift()
                consumer(taskWrapper) // "resolve" (from getNextTask consumerQueue.push(resolve)) with the wrapped task
            } else {
                this.taskQueue.push(taskWrapper) // no consumers available push back into the taskQueue for later time.
            }
        })
    }
}