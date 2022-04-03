const originalRequire = require

const fs = originalRequire('fs')

// execute code from filename with references back to module, exports, and require variables
function loadModule (filename, module, require) {
    const wrappedSrc = 
        `(function (module, exports, require) {
            ${fs.readFileSync(filename, 'utf8')}
        })(module, module.exports, require)`
    eval(wrappedSrc)
}

require = function require (moduleName) {

    console.log(`Require involved for module: ${moduleName}`)
    const id = require.resolve(moduleName)

    if (require.cache[id]) {
        // if cached, then immediately return what was evaluated for exports
        return require.cache[id].exports
    }

    const module = {
        exports: {},
        id
    }
    
    require.cache[id] = module
    loadModule(id, module, require) // module file will redefine module.exports
    return module.exports
}

require.cache = {}
require.resolve = (moduleName) => {
    return originalRequire.resolve(moduleName)
    // will look for module in file modules (absolute path), code modules, package modules in that order
    // will also try to match <moduleName>.js, <moduleName>/index.js
}

// this will be entrypoint.. so execute with "node loader.js ./main"
require(process.argv[2])

