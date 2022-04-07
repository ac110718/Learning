export function levelSubscribe (db) {
    // add a subscribe method directly to db
    db.subscribe = (pattern, listener) => {
        db.on('put', (key, val) => { // callback for any put operation
            const match = Object.keys(pattern).every(
                // for all keys in pattern object...
                // pattern[key] is equal to valObj[key] that was written to database
                // val is what is written to DB
                k => (pattern[k] === val[k]) 
            )
            if (match) {
                listener(key, val) // callback to parent
            }
        })
        return db // wrapper, return original db
    }
}