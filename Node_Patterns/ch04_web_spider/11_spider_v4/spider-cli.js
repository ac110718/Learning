import { spider } from './spider.js'
import { TaskQueue } from './TaskQueue.js'

const url = process.argv[2]
const nesting = Number.parseInt(process.argv[3], 10) || 1
const concurrency = Number.parseInt(process.argv[4], 10) || 2

const spiderQueue = new TaskQueue(concurrency) // this instance gets passed in throughout
spiderQueue.on('error', err => console.error(err.message))
spiderQueue.on('empty', () => console.log('Download complete'))

spider(url, nesting, spiderQueue)