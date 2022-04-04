import { EventEmitter } from 'events'
import { readFile } from 'fs'
import { fileURLToPath } from 'url'

class FindRegex extends EventEmitter {
    constructor (regex) {
        super() // invoke EventEmitter internals
        this.regex = regex
        this.files = []
    }

    addFile(file) {
        this.files.push(file)
        return this
    }

    find () {
        for (const file of this.files) {
            readFile(file, 'utf8', (err, content) => {
                if (err) {
                    return this.emit('error', err)
                }

                this.emit('fileread', file)

                const match = content.match(this.regex)
                if (match) {
                    match.forEach(elem => this.emit('found', file, elem))
                }
            })
        }
        return this
    }
}

const findRegexInstance = new FindRegex(/hello \w+/g)
findRegexInstance
    .addFile('fileA.txt')
    .addFile('fileB.json')
    .find()
    .on('fileread', file => console.log(`Opened file: ${file}`))
    .on('found', (file, match) => console.log(`Matched "${match}" in file ${file}`))
    .on('error', err => console.error(`Error emitted ${err.message}`))