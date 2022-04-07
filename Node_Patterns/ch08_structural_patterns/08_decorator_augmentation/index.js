class StackCalculator {
    constructor () {
      this.stack = []
    }
  
    putValue (value) {
      this.stack.push(value)
    }
  
    getValue () {
      return this.stack.pop()
    }
  
    peekValue () {
      return this.stack[this.stack.length - 1]
    }
  
    clear () {
      this.stack = []
    }
  
    divide () {
      const divisor = this.getValue()
      const dividend = this.getValue()
      const result = dividend / divisor
      this.putValue(result)
      return result
    }
  
    multiply () {
      const multiplicand = this.getValue()
      const multiplier = this.getValue()
      const result = multiplier * multiplicand
      this.putValue(result)
      return result
    }
  }

function patchCalculator (calculator) {
    // new method added directly to target
    calculator.add = function () {
        const addend2 = calculator.getValue()
        const addend1 = calculator.getValue()
        const result = addend1 + addend2
        calculator.putValue(result)
        return result
    }

    const divideOrig = calculator.divide
    calculator.divide = () => {
        const divisor = calculator.peekValue()
        if (divisor === 0) {
            throw Error('Division by 0')
        }
        return divideOrig.apply(calculator)
    }

    return calculator
}

const calculator = new StackCalculator()
const enhancedCalculator = patchCalculator(calculator)

enhancedCalculator.putValue(4)
enhancedCalculator.putValue(3)
console.log(enhancedCalculator.add()) // 4+3 = 7
enhancedCalculator.putValue(2)
console.log(enhancedCalculator.multiply()) // 7*2 = 14