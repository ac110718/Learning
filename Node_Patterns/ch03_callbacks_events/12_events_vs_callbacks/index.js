import { EventEmitter } from 'events'

function helloEvents () {
    const eventEmitter = new EventEmitter()
    setTimeout(() => eventEmitter.emit('complete', 'hello world'), 100)
    return eventEmitter
}

function helloCallback (cb) {
    setTimeout(() => cb(null, 'hello world'), 100)
}

// functionally the same but...
// use events to signal something has happened
// use callback to RETURN a result in an asynchronous way

helloEvents().on('complete', message => console.log("event: " + message))
helloCallback((err, message) => console.log("cb: " + message))