// translate filesystem functions to database function.. 
// why? code reuse potentially.. code operation used for filesystem could be adapted to use database based in browser
// more code sharing

import { resolve } from 'path'

export function createFSAdapter (db) {
    return ({ // return an object with two major functions that serve as interface (readFile, writeFile)
        readFile (filename, options, callback) {
            // ensure correct order of parameters
            if (typeof options === 'function') {
                callback = options
                options = {}
            } else if (typeof options === 'string') {
                options = { encoding: options }
            }

            db.get(resolve(filename), {
                valueEncoding: options.encoding
            },
            (err, value) => {
                if (err) {
                    if (err.type === 'NotFoundError') {
                        err = new Error(`ENOENT, open "${filename}"`)
                        err.code = 'ENOENT'
                        err.errno = 34
                        err.path = filename
                    }
                    return callback && callback(err)
                }
                callback && callback(null, value) // successfully retrived value
            })
        },

        writeFile (filename, contents, options, callback) {
            if (typeof options === 'function') {
                callback = options
                options = {}
            } else if (typeof options === 'string') {
                options = { encoding: options }
            }

            db.put(resolve(filename), contents, {
                valueEncoding: options.encoding
            }, callback)
        }
    })
}