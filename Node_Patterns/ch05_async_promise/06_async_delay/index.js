function delay (milliseconds) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve(new Date())
        }, milliseconds)
    })
}

async function playingWithDelays () {
    console.log('Delaying...', new Date())

    const dateAfterOneSecond = await delay(1000) // stores resolution of promise
    console.log(dateAfterOneSecond) // will run synchronously after await

    const dateAfterThreeSeconds = await delay(3000)
    console.log(dateAfterThreeSeconds)

    return 'donzo'
}

playingWithDelays()
    .then(result => {
        console.log(`After 4 seconds: ${result}`) // passed in with 'done'
    })