import { readFile } from 'fs'

const cache = new Map()

function inconsistentRead (filename, cb) {
    if (cache.has(filename)) {
        // synchronous execution immediately
        cb(cache.get(filename))
    } else {
        // callback gets invoked at a later time
        readFile(filename, 'utf8', (err, data) => {
            cache.set(filename, data)
            cb(data)
        })
    }
}

function createFileReader (filename) {
    const listeners = []
    // apply each listener function to each value
    inconsistentRead(filename, value => {
        listeners.forEach(listener => listener(value))
    })

    return {
        // function that adds listener to list
        onDataReady: listener => listeners.push(listener)
    }
}

const reader1 = createFileReader('data.txt')
reader1.onDataReady(data => {
    console.log(`First call data: ${data}`)
    // nested version won't work because by the time this gets called, 
    // you just return the cached version before you have chance to register new callback
    const reader2 = createFileReader('data.txt')
    reader2.onDataReady(data => {
        console.log(`Second call data: ${data}`)
    })
})

// readFile still hasn't been executed yet. Will go through entire code before actually reading the data file, so there's still time
const reader3 = createFileReader('data.txt')
reader3.onDataReady(data => {
    console.log(`Third call data: ${data}`)
})