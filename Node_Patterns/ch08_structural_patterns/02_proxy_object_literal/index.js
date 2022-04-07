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

  function createSafeCalculator (calculator) {
      // return an entire proxied object rather than wrapped object

      return {
          // re-define divide
          divide () {
              const divisor = calculator.peekValue()
              if (divisor === 0) {
                  throw Error('Division by 0')
              }
              return calculator.divide() 
          },
          putValue (value) { return calculator.putValue(value) },
          getValue () { return calculator.getValue() },
          peekValue () { return calculator.peekValue() },
          clear () { return calculator.clear() },
          multiply () { return calculator.multiply() }
      }
  }

const calculator = new StackCalculator()
const safeCalculator = createSafeCalculator(calculator)
calculator.putValue(3)
calculator.putValue(2)
console.log(calculator.multiply()) // 6

safeCalculator.putValue(2)
console.log(safeCalculator.multiply()) // 12

calculator.putValue(0)
console.log(calculator.divide()) // infinity

safeCalculator.clear()
safeCalculator.putValue(4)
safeCalculator.putValue(0)
console.log(safeCalculator.divide()) // Error