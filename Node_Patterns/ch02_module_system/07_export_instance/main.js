const logger = require('./logger')

logger.log('This is an informational message')
logger.log('This is a second message')

const customLogger = new logger.constructor('CUSTOM') // constructor still accessible despite exporting instance
customLogger.log('This is an informational message')
customLogger.log('This is a second message')