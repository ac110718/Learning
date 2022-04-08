function * twoWayGenerator () {
    try {
        const what = yield null
        yield 'Hello ' + what
    } catch (err) {
        yield 'Hello error: ' + err.message
    }
}

console.log('Passing a value back to the generator:')
const twoWay = twoWayGenerator()
console.log(twoWay.next()) // pauses at first yield statement, yielding null
console.log(twoWay.next('world')) // assigns to what variable and yields 'Hello world'

console.log('Using throw():')
const twoWayException = twoWayGenerator()
twoWayException.next()
console.log(twoWayException.throw(new Error('Boom!')))

 console.log('Using return():')
 const twoWayReturn = twoWayGenerator()
 console.log(twoWayReturn.return('myReturnValue')) // done: true
