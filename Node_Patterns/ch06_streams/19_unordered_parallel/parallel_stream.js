import { Transform } from 'stream'

export class ParallelStream extends Transform {
    constructor (userTransform, opts) {
        super ({ objectMode: true, ...opts})
        this.userTransform = userTransform
        this.running = 0
        this.terminateCb = null
    }

    _transform (chunk, enc, done) {
        this.running++
        this.userTransform(
            chunk,
            enc,
            this.push.bind(this), // pass along push method
            this._onComplete.bind(this) // pass _onComplete as done function to get notified when this is done
        )
        console.log(`instance ${this.running} fired`)
        done() // invoke done immediately before userTransform completes
    }

    _flush (done) {
        if (this.running > 0) {
            this.terminateCb = done
        } else {
            done() // delay calling done unless you're the very last task
        }
    }

    _onComplete (err) {
        this.running--
        if (err) {
            return this.emit('error', err)
        }
        if (this.running === 0) {
            this.terminateCb && this.terminateCb()
        }
    }
}