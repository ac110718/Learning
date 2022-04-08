export class OnlineState {
    constructor (failsafeSocket) {
        this.failsafeSocket = failsafeSocket
        this.hasDisconnected = false
    }

    send (data) {
        this.failsafeSocket.queue.push(data)
        this._safeWrite(data) // private method to send
    }

    _safeWrite(data) {
        this.failsafeSocket.socket.write(data, (err) => {
            if (!this.hasDisconnected && !err) {
                // processed so take out
                this.failsafeSocket.queue.shift()
            }
        })
    }

    activate () {
        this.hasDisconnected = false
        for (const data of this.failsafeSocket.queue) {
            this._safeWrite(data)
        }

        this.failsafeSocket.socket.once('error', () => {
            this.hasDisconnected = true
            this.failsafeSocket.changeState('offline')
        })
    }
}