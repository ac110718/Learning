const myModule = (() => {
    const privateFoo = () => {}
    const privateBar = []

    const exported = {
        publicFoo: () => {},
        publicBar: () => {}
    }

    return exported
})() // IIFE Immediately involved function expression

// "exported" will be exposed, but direct access will yield undefined
console.log(myModule)
console.log(myModule.privateFoo, myModule.privateBar)