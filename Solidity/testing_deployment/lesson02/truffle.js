// truffle.js stores network settings for deployment
// truffle-config.js is also created and used instead for Windows system
// where truffle.js and truffle.exe will create a conflict and truffle.js will need to get deleted

// Initialize HDWalletProvider
// Needed because we're using Infura, which allows us to deploy code to Ethereum without acutally running an ethereum node
// But infura won't handle private keys so we need separate HDWalletProvider

// CryptoZombies contract is the first header file for naming purposes.. it just inherits from ZombieOwnership.sol to create a more reasonable name
// binaries are compiled into .build/contracts directory

const HDWalletProvider = require("truffle-hdwallet-provider");

const LoomTruffleProvider = require('loom-truffle-provider');

//keys for the hardware wallet. Put in a file listed with .gitignore
const mnemonic = "YOUR_MNEMONIC";

//exports to make this configuration available to truffle
module.exports = {
  //networks object with configurations for each network
  networks: {
   
    mainnet: {
      //returns provider function to call upon deployment
      provider: function () {
        //wrap with HDWalletProvider.. mainnet address and token
        return new HDWalletProvider(mnemonic, "https://mainnet.infura.io/v3/YOUR_TOKEN")
      },
      network_id: "1"
    },
   
    rinkeby: {
     
      provider: function () {
       
        return new HDWalletProvider(mnemonic, "https://rinkeby.infura.io/v3/YOUR_TOKEN")
      },
     
      network_id: 4
    },
   
    loom_testnet: {
      provider: function() {
          const privateKey = 'YOUR_PRIVATE_KEY'
          const chainId = 'extdev-plasma-us1';
          const writeUrl = 'http://extdev-plasma-us1.dappchains.com:80/rpc';
          const readUrl = 'http://extdev-plasma-us1.dappchains.com:80/query';
          return new LoomTruffleProvider(chainId, writeUrl, readUrl, privateKey);
      },
      network_id: '9545242630824'
    }
  }
};