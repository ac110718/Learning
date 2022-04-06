const MODIFIER_NAMES = ['swap', 'write', 'fill']

// Protective wrapper or revealing constructor
// Buffer that allows mutability only through the properties found in the executor object
export class ImmutableBuffer {
    constructor (size, executor) {
        const buffer = Buffer.alloc(size)
        const modifiers = {}
        for (const prop in buffer) {
            if (typeof buffer[prop] != 'function') {
                continue // don't adjust anything that's not a function
            }
            if(MODIFIER_NAMES.some(m => prop.startsWith(m))) {
                // put in modifiers object if mutable function
                modifiers[prop] = buffer[prop].bind(buffer)
            } else {
                // add anything else back directly
                this[prop] = buffer[prop].bind(buffer) 
            }
        }
        executor(modifiers)
    }
}