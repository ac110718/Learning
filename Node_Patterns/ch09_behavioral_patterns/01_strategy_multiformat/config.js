import { promises as fs } from 'fs'
import objectPath from 'object-path'

export class Config {
    constructor (formatStrategy) {
        this.data = {}
        this.formatStrategy = formatStrategy
    }

    // configPath is dot notation for objects, or nested key-values in JSON
    get (configPath) {
        return objectPath.get(this.data, configPath) // get property.subProperty
    }

    set (configPath, value) {
        return objectPath.set(this.data, configPath, value)
    }

    async load (filePath) {
        console.log(`Deserializing from ${filePath}`)
        this.data = this.formatStrategy.deserialize(
            await fs.readFile(filePath, 'utf-8')
        )
    }

    async save (filePath) {
        console.log(`Serializing to ${filePath}`)
        await fs.writeFile(filePath, this.formatStrategy.serialize(this.data))
    }
}