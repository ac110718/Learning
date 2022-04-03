const a = require('./a')
const b = require('./b')

console.log('a -> ', JSON.stringify(a, null, 2)) // value, replacer (behavior of stringification), space (for indentation)
console.log('b -> ', JSON.stringify(b, null, 2))