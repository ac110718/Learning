import react from 'react'
import ReactDOM from 'react-dom'

const h = react.createElement

class Hello extends react.Component {
    render () {
        // takes in tag name, props (null here), children elements
        return h('h1', null, [
            'Hello ',
            this.props.name || 'World'
        ])
    }
}

ReactDOM.render(
    // pass in element, props
    h(Hello, { name: 'React' }),
    document.getElementsByTagName('body')[0]
)