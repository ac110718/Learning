function delay (milliseconds) {
    return new Promise ((resolve, reject) => {
        setTimeout(() => {
            resolve(new Date())
        }, milliseconds)
    })
}

console.log(`Delaying...${new Date().getSeconds()}s`)

delay(1000) // resolve returns date object after 1000ms.. after which you can manipulate in then function callback
    .then(newDate => {
        console.log(`Done ${newDate.getSeconds()}s`)
    })