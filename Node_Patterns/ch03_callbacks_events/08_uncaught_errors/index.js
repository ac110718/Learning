import { readFile } from 'fs'

function readJSONThrows (filename, callback) {
    readFile(filename, 'utf8', (err, data) => {
        if (err) {
            return callback(err)
        }
        callback(null, JSON.parse(data))
    })
}

try {
    // there's no error because you're just REGISTERING the callback.. 
    // what happens if the error happens at the callback level later?
    readJSONThrows('invalid_json.json', (err) => console.error(err))
} catch (err) {
    console.log('This will NOT catch the JSON parsing exception')
}

process.on('uncaughtException', (err) => {
    console.error(`This will catch at last the JSON parsing exception: ${err.message}`)
    // terminate with error code 1 exit. Otherwise application would continue
    process.exit(1)
})