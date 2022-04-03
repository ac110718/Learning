const moduleB = require('./moduleB')

module.exports = {
    run: () => {
        moduleB.log() // moduleB must implement a log() function
    }
}