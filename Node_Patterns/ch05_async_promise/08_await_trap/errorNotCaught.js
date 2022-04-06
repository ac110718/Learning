function delayError (milliseconds) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            reject(new Error(`Error after ${milliseconds}ms`))
        }, milliseconds)
    })
}

async function errorNotCaught () {
    try {
        return delayError(1000) // no return "await" will return immediately back to the caller who will have to handle it
    } catch (err) {
        console.error('Error caught by the async function: ' + err.message)
    }
}

errorNotCaught()
    .catch(err => console.error('Error caught by the caller: ' + err.message))