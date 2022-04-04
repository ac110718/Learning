import { randomBytes } from 'crypto'

function promisify (callbackBasedApi) {
    return function promisified (...args) { // function wrapper will have same interface as original, less the callback
        return new Promise((resolve, reject) => {
            const newArgs = [
                ...args,
                function (err, result) { // replace callback with promise implementation
                    if (err) {
                        return reject(err)
                    }
                    resolve(result)
                }
            ]
            callbackBasedApi(...newArgs) // promise args + hand-written cb using promises
        })
    }
}

const randomBytesP = promisify(randomBytes)
randomBytesP(32)
    .then(buffer => {
        console.log(`Random bytes: ${buffer.toString()}`)
    })