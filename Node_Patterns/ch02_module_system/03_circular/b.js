exports.loaded = false
const a = require('./a')

module.exports = {
    a, // if a is traversed FIRST.. then loaded variable will be a cached version, which is FALSE
    loaded: true
}