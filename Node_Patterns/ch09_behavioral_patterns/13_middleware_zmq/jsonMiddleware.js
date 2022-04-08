export const jsonMiddleware = function () {
    // return object that has inbound and outbound interface (one for each direction)
    return {
        inbound (message) {
            return JSON.parse(message.toString())
        },
        outbound (message) {
            return Buffer.from(JSON.stringify(message))
        }
    }
}