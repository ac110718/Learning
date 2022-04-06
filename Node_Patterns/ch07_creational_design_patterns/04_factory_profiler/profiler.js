class Profiler {
    constructor (label) {
        this.label = label
        this.lastTime = null
    }

    start () {
        this.lastTime = process.hrtime()
    }

    end () {
        const diff = process.hrtime(this.lastTime)
        console.log(`Timer "${this.label}" took ${diff[0]} seconds ` +
            `and ${diff[1]} nanoseconds.`)
    }
}

// run empty profiler when working in production
const noopProfiler = {
    start () {},
    end () {}
}

// factory function to choose
export function createProfiler (label) {
    if (process.env.NODE_ENV === 'production') {
        return noopProfiler
    }
    return new Profiler(label)
}