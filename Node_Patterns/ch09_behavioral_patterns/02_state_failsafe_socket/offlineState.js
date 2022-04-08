import jsonOverTcp from 'json-over-tcp-2'

export class OfflineState {

    // take in failsafeSocket from parent itself so you can retry from this state
    constructor(failsafeSocket) {
        this.failsafeSocket = failsafeSocket
    }

    send (data) {
        // offline queue sits with parent so it can be pushed over internet when re-connected
        this.failsafeSocket.queue.push(data)
    }

    activate () {
        const retry = () => {
            setTimeout(() => this.activate(), 1000)
        }

        console.log('Trying to connect...')
        // ESTABLISH SOCKET here... does it once on initiation and whenever disconnected
        this.failsafeSocket.socket = jsonOverTcp.connect(
            this.failsafeSocket.options,
            () => {
                console.log('Connection established')
                this.failsafeSocket.socket.removeListener('error', retry)
                // parent call changeState to 'online'
                this.failsafeSocket.changeState('online')
            }
        )
        // re-call retry (i.e. activate) method every 1 second post error
        this.failsafeSocket.socket.once('error', retry) 
    }
}