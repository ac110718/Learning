import nunjucks from 'nunjucks'

const template = '<h1>Hello <i>{{ name }}</i></h1>'

export function sayHello (name) {
    // browser format
    if (typeof window !== 'undefined' && window.document) {
        return nunjucks.renderString(template, { name })
    }

    // command terminal format
    return `Hello \u001b[1m${name}\u001b[0m`
}