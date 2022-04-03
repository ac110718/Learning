const counter = require('./counter.cjs')

console.log(counter.count)
counter.increment()
console.log(counter.count)
counter.count++ // direct access allowed
console.log(counter.count)
counter.increment()
console.log(counter.count)