class Logger {
    constructor (name) {
        this.count = 0
        this.name = name
    }

    log (message) {
        this.count++
        console.log('[' + this.name + ' ' + this.count + ']' + message)
    }
}

module.exports = new Logger('DEFAULT')