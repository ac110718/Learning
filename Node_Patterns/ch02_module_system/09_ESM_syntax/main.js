// explicitly declare type as module in package.json
// import all the members of the modules

// import * as loggerModule from './logger.js'
// console.log(loggerModule)

// import just single member of module

// import { log } from './logger.js'
// log('Hello World')

// import multiple members of the module

// import { log, Logger } from './logger.js'
// log('Hello World')
// const logger = new Logger('DEFAULT')
// logger.log('Hello World')

// avoid a name clash

import { log as log2 } from './logger.js'
const log = console.log

log('message from log')
log2('message from log2')
