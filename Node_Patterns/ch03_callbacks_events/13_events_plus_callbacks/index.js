import glob from 'glob'

glob('data/*.txt',
    (err, files) => {
        if (err) {
            return console.error(err)
        }
        // callback when process is complete
        console.log(`All files found: ${JSON.stringify(files)}`)
    })
    // more fine grained reporting using events
    .on('match', match => console.log(`Match found: ${match}`))