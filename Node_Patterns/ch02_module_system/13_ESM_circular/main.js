import * as a from './a.js'
import * as b from './b.js'

// will see the entire "picture" rather than incomplete cached version like cjs
// ESM will parse and link everything first, and then execute as a final step
// cjs will execute as you're traversing so you may get "old" cached versions or incomplete pictures

console.log('a -> ', a)
console.log('b ->', b)