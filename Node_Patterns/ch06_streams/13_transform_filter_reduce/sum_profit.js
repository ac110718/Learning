import { Transform } from 'stream'

export class SumProfit extends Transform {
    constructor (options = {}) {
        options.objectMode = true
        super(options)
        this.total = 0
    }

    _transform (record, enc, cb) {
        this.total += Number.parseFloat(record.profit)
        cb() // pushes nothing to the read stream.. until the end
    }

    _flush (cb) {
        this.push(this.total.toString())
        cb()
    }
}