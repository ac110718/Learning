import { TaskQueue } from './TaskQueue.js'

// each task needs to take a callback so that the "next" task can be embedded as a callback

function makeSampleTask (name) {
    return (cb) => {
        console.log(`${name} started`)
        setTimeout(() => {
            console.log(`${name} completed`)
            cb()
        }, Math.random() * 2000)
    }
}

const queue = new TaskQueue(2)
queue.on('error', (err) => console.error(err.message))
queue.on('empty', () => console.log('Queue drained'))

function task1 (cb) {
    console.log('Task 1 started')
    queue
        .pushTask(makeSampleTask('task1 -> subtask 1'))
        .pushTask(makeSampleTask('task1 -> subtask 2'))
    setTimeout(() => {
        console.log('Task 1 completed')
        cb()
    }, Math.random() * 2000)
}

function task2 (cb) {
    console.log('Task 2 started')
    queue
        .pushTask(makeSampleTask('task2 -> subtask 1'))
        .pushTask(makeSampleTask('task2 -> subtask 2'))
        .pushTask((done) => done(new Error ('Simulated error')))
        .pushTask(makeSampleTask('task2 -> subtask 3'))
    setTimeout(() => {
        console.log('Task 2 completed')
        cb()
    }, Math.random() * 2000)
}

queue
    .pushTask(task1)
    .pushTask(task2)