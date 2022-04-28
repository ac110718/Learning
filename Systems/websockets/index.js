const http = require("http");
const WebSocketServer = require("websocket").server;
let connection = null;

const httpserver = http.createServer((req, res) => console.log("we have received request"))
// pass the httpserver object into websocket (which will be wrapped after the first get request from client)
const websocket = new WebSocketServer({ "httpServer": httpserver })

httpserver.listen(8080, () => console.log("Server is listening on port 8080"))

websocket.on("request", request => {
    connection = request.accept(null, request.origin) // first parameter customer protocol
    connection.on("open", () => console.log("Opened WS"))
    connection.on("close", () => console.log("Closed WS"))
    connection.on("message", message => {
        console.log(`Received message ${message.utf8Data}`)
        connection.send(`Got your message: ${message.utf8Data}`)
    })
    sendFiveSeconds();
})

function sendFiveSeconds() {
    connection.send(`Message ${Math.random()}`);
    setTimeout(sendFiveSeconds, 5000);
}

// client
// let ws = new WebSocket("ws://localhost:8080");
// ws.onmessage = message => console.log(`Received: ${message.data}`);
// ws.send("Hello! I am client");