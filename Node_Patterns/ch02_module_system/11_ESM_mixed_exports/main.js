// with export default, the naming and export process happens at the same time
import mylog, { info } from './logger.js'

mylog('Hello')
info('World')