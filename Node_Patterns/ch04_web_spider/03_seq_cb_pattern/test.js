let count = 0
function asyncOperation (cb) {
    count++
    console.log(`task ${count} initiated...`)
    process.nextTick(cb)
}

function task1 (cb) {
    asyncOperation(() => {
        task2(cb)
    })
}

function task2 (cb) {
    asyncOperation(() => {
        task3(cb)
    })
}

function task3 (cb) {
    asyncOperation(() => {
        cb() // cb gets drilled through and executed here
    })
}

task1(() => {
    console.log('tasks 1, 2, and 3 executed')
})