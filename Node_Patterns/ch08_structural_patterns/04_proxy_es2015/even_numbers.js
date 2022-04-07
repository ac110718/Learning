
// proxy object takes a target, handler parameter. Target is object on which proxy is applied.. 
// handler is special object that defines behavior

const evenNumbers = new Proxy([], {
    get: (target, index) => index * 2,
    has: (target, number) => number % 2 === 0
}) 

// metaprogramming possible because you've proxied the get and has methods
// data never gets stored.. methods just get intercepted, created a virual object
console.log(2 in evenNumbers) // true
console.log(5 in evenNumbers) // false
console.log(evenNumbers[7]) // 14