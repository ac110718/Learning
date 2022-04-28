const net = require("net")

const server = net.createServer(socket => {
    socket.write("Hello.") // respond immediately on local establishment
    socket.on("data", data => {
        console.log(data.toString()) // console log anything sent over from client
    })
})

// if connection is lost, client needs to start all over again because TCP reliability guarantee

server.listen(8080)

// run command below. If connection is lost, must re-establish (not case with UDP)
// telnet 127.0.0.1 8080