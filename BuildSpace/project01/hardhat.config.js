require("@nomiclabs/hardhat-waffle");
require('dotenv').config();

// This is a sample Hardhat task. To learn how to create your own go to
// https://hardhat.org/guides/create-task.html
task("accounts", "Prints the list of accounts", async (taskArgs, hre) => {
  const accounts = await hre.ethers.getSigners();

  for (const account of accounts) {
    console.log(account.address);
  }
});

// You need to export an object to set up your config
// Go to https://hardhat.org/config/ to learn more

/**
 * @type import('hardhat/config').HardhatUserConfig
 */
module.exports = {
  solidity: "0.8.4",
  networks: {
    rinkeby: {
      url: "https://eth-rinkeby.alchemyapi.io/v2/kczHIrpF2HS14tORrbELMm8pssvAalHV",
      accounts: [process.env.SECRET_KEY]
    },
  },
};

// Deploying contracts with account:  0xcdC59f691aab231810417BC4088149628A75C87f
// Account balance:  98438939478497818
// WavePortal address:  0xFe09F2Ec2e2Df4D474e1969F12e263b5D80b2045
