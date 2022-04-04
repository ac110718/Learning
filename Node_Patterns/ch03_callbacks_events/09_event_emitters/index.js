import { EventEmitter } from 'events'
import { readFile } from 'fs'

function findRegex (files, regex) {
    const emitter = new EventEmitter() 
    for (const file of files) {
        readFile(file, 'utf8', (err, content) => {
            if (err) {
                return emitter.emit('error', err)
            }
            emitter.emit('fileread', file)
            const match = content.match(regex)
            if (match) {
                match.forEach(elem => emitter.emit('found', file, elem))
            }
        })
    }
    return emitter // allow for chaining
}

findRegex(
    ['fileA.txt', 'fileB.json'],
    /hello \w+/g // \w+ matches one or more word characters, /g find all matches not just the first one
)
    .on('fileread', file => console.log(`${file} was read`))
    .on('found', (file, match) => console.log(`Matched "${match}" in ${file}`))
    .on('error', err => console.error(`Error emitted ${err.message}`))