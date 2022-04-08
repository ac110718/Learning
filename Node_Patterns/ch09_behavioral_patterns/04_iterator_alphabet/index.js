const A_CHAR_CODE = 65
const Z_CHAR_CODE = 90

function createAlphanetIterator () {
    let currCode = A_CHAR_CODE

    return { // return object with next function
        next () {
            const currChar = String.fromCodePoint(currCode)
            if (currCode > Z_CHAR_CODE) {
                return { done: true }
            }
            // iterator objects typically stateful to know positioning
            currCode++
            return { value: currChar, done: false }
        }
    }
}

const iterator = createAlphanetIterator()
let iterationResult = iterator.next()
while (!iterationResult.done) {
    console.log(iterationResult.value)
    iterationResult = iterator.next()
}