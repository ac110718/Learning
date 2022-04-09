import { sayHello } from './say_hello.js'

const body = document.getElementsByTagName('body')[0]
body.innerHTML = sayHello('Browser')
