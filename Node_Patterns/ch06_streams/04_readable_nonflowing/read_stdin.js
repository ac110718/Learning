process.stdin
    .on('readable', () => { // on "readable" rather than on "data".. need to take in read()
        let chunk
        console.log('New data available')
        while ((chunk = process.stdin.read()) !== null) {
            console.log(
                `Chunk read (${chunk.length} bytes): "${chunk.toString()}"`
            )
        }
    })
    .on('end', () => console.log('End of stream'))