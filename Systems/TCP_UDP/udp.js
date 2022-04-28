const dgram = require('dgram');
const socket = dgram.createSocket('udp4');

socket.on('message', (msg, rinfo) => {
    console.log(`server got: ${msg} from ${rinfo.address}:${rinfo.port}`);
});

// no connection needed.. just receive packets. client port could change as well
socket.bind(8081);

// -w1 : timeout 1 second, -u udp
// echo "hi" | nc -w1 -u 127.0.0.1 8081