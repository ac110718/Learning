export function createLoggingWritable (writable) {
    return new Proxy(writable, { // handler
        get (target, propKey, receiver) {
            if (propKey === 'write') {
                return function (...args) { // return a function taking in all the args
                    const [chunk] = args // pull out chunk from list of arguments passed into original function
                    console.log('Writing', chunk)
                    return writable.write(...args) // proceed as otherwise normal
                }
            }
            return target[propKey] // return original methods untouched
        }
    })
}