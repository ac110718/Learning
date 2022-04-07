import { create } from 'domain'
import { createWriteStream } from 'fs'
import { createLoggingWritable } from './logging_writable.js'

const writable = createWriteStream('test.txt')
const writableProxy = createLoggingWritable(writable)

writableProxy.write('First chunk')
writableProxy.write('Second chunk')
writable.write('This is not logged')
writableProxy.end()