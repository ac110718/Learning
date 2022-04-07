export function createObservable (target, observer) {
    const observable = new Proxy(target, { // handler
        set (obj, prop, value) {
            if (value !== obj[prop]) { // value is different from original
                const prev = obj[prop]
                obj[prop] = value
                observer({ prop, prev, curr: value }) // callback observer with this object input
            }
            return true
        }
    })

    return observable // return target proxied
}