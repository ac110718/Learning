function delayError (milliseconds) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            reject(new Error(`Error after ${milliseconds}ms`))
        }, milliseconds)
    })
}

async function playingWithErrors (throwSyncError) {
    try {
        if (throwSyncError) {
            throw new Error('This is a synchronous error')
        }
        await delayError(1000)
    } catch (err) {
        console.error(`We have an error: ${err.message}`) // catches either of the two above errors
    } finally {
        console.log('Done') // always runs
    }
}

playingWithErrors(true)
playingWithErrors(false) // promise will reject