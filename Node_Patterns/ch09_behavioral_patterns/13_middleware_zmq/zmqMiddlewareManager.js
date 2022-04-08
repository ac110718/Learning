export class ZmqMiddlewareManager {
    constructor (socket) {
        this.socket = socket
        // pipeline processing tasks on way in and out
        this.inboundMiddleware = []
        this.outboundMiddleware = []

        this.handleIncomingMessage().catch(err => console.error(err))
    }

    async handleIncomingMessage () {
        for await (const [message] of this.socket) { // pull out message
            await this
                .executeMiddleware(this.inboundMiddleware, message)
                .catch(err => {
                    console.error('Error while processing the mssage', err)
                })
        }
    }

    async send (message) {
        const finalMessage = await this
            .executeMiddleware(this.outboundMiddleware, message)
        return this.socket.send(finalMessage)
    }

    // add middleware pairs to processing pipeline for inbound and outbound
    use (middleware) {
        if (middleware.inbound) {
            this.inboundMiddleware.push(middleware.inbound)
        }
        if (middleware.outbound) {
            // add to the FRONT because want to process in reverse order
            this.outboundMiddleware.unshift(middleware.outbound)
        }
    }

    async executeMiddleware(middlewares, initialMessage) {
        let message = initialMessage
        for await (const middlewareFunc of middlewares) {
            message = await middlewareFunc.call(this, message)
        }
        return message
    }
}