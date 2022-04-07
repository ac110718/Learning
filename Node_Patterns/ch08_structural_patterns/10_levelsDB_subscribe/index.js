import { dirname, join } from 'path'
import { fileURLToPath } from 'url'
import level from 'level'
import { levelSubscribe } from './level_subscribe.js'

const __dirname = dirname(fileURLToPath(import.meta.url))

const dbPath = join(__dirname, 'db')
const db = level(dbPath, { valueEncoding: 'json' })
levelSubscribe(db)

// subscribe written via levelSubscribe
db.subscribe(
    { doctype: 'tweet', language: 'en' }, // pattern
    (k, val) => console.log(val) // listener callback on what you put into db (key, value)
)

// logged
db.put('1', { // ④
    doctype: 'tweet',
    text: 'Hi',
    language: 'en'
})

// not logged
db.put('2', {
    doctype: 'company',
    name: 'ACME Co.'
})