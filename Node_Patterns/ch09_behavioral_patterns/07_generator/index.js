function * fruitGenerator () {
    yield 'peach'
    yield 'watermelon'
    return 'summer'
}

const fruitGeneratorObj = fruitGenerator()
console.log(fruitGeneratorObj.next())
console.log(fruitGeneratorObj.next())
console.log(fruitGeneratorObj.next())

console.log('Using for...of:')

for (const fruit of fruitGenerator()) {
    console.log(fruit) 
    // does not print summer because it is RETURNED.. 
    // iteration is complete with summer as a return value, not as an element
}