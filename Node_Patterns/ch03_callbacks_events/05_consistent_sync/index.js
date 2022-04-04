import { readFileSync } from 'fs'

const cache = new Map()

function consistentReadSync (filename) {
    if (cache.has(filename)) {
        console.log('reading from cache!')
        return cache.get(filename)
    } else {
        const data = readFileSync(filename, 'utf8')
        cache.set(filename, data)
        return data
    }
}

console.log(consistentReadSync('data.txt'))
// will read from cache
// downside is that readFileSync will block operation
console.log(consistentReadSync('data.txt'))