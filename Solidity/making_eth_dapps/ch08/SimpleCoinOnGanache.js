const fs = require('fs');
const solc = require('solc');
const Web3 = require('web3');
const web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));

const initialSupply = 10000;

const source = fs.readFileSync('./SimpleCoin.sol', 'utf8');

// per web3 docs
const input = {
    language: "Solidity",
    sources: {
        "SimpleCoin.sol": {
            content: source,
        },
    },
    settings: {
        outputSelection: {
            "*": {
                "*": ["*"],
            },
        },
    },
};

const compiledContract = JSON.parse(solc.compile(JSON.stringify(input)));
const abi = compiledContract.contracts["SimpleCoin.sol"].SimpleCoin.abi;
const bytecode = '0x' + compiledContract.contracts["SimpleCoin.sol"].SimpleCoin.evm.bytecode.object;

const SimpleCoinContractFactory = new web3.eth.Contract(abi);

async function ganacheAccounts() {
    let accounts = await web3.eth.getAccounts();
    return accounts[1];
};

async function deploy() {
    let sender = await ganacheAccounts();
    const gasEstimate = await SimpleCoinContractFactory
        .deploy({data: bytecode, arguments: [initialSupply]})
        .estimateGas(function(err, gas) {return gas});
    const simpleCoinInstance = await SimpleCoinContractFactory
        .deploy({data: bytecode, arguments: [initialSupply]})
        .send({ from: sender, gas: gasEstimate + 10000 })
        .then((contractInstance) => console.log('Mined! address: ' + contractInstance.options.address));
};

deploy();
console.log(abi);