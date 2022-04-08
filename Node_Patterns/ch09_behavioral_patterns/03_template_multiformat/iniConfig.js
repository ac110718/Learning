import { ConfigTemplate } from './configTemplate.js'
import ini from 'ini'

export class IniConfig extends ConfigTemplate {

    // overwrite and implement these methods
    _deserialize (data) {
        return ini.parse(data)
    }

    _serialize (data) {
        return ini.stringify(data)
    }
}