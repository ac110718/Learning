import { readFile } from 'fs'

function readJSON (filename, callback) {
    readFile(filename, 'utf8', (err, data) => {
        let parsed
        if (err) {
            // propagate error back to callback
            // callbacks are like return of function
            return callback(err)
        }
        try {
            parsed = JSON.parse(data)
        } catch (err) {
            return callback(err)
        }
        // error first parameter
        // if you try callback(null, JSON.parse(data)) error is uncaught and goes up to calling program rather than callback
        callback(null, parsed)
    })
}

const cb = (err, data) => {
    if (err) {
        return console.error(`Caught error ${err.message}`)
    }
    console.log(data)
}

readJSON('valid_json.json', cb)
readJSON('invalid_json.json', cb)