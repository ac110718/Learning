const main = async () => {
    const domainContractFactory = await hre.ethers.getContractFactory('Domains');
    const domainContract = await domainContractFactory.deploy("sol");
    await domainContract.deployed();
  
    console.log("Contract deployed to:", domainContract.address);
  
    
      let txn = await domainContract.register("achan",  {value: hre.ethers.utils.parseEther('0.1')});
      await txn.wait();
    console.log("Minted domain achan.sol");
  
    txn = await domainContract.setRecord("achan", "Record for achan.sol");
    await txn.wait();
    console.log("Set record for achan.sol");
  
    const address = await domainContract.getAddress("achan");
    console.log("Owner of domain achan", address);
  
    const balance = await hre.ethers.provider.getBalance(domainContract.address);
    console.log("Contract balance:", hre.ethers.utils.formatEther(balance));
  }
  
  const runMain = async () => {
    try {
      await main();
      process.exit(0);
    } catch (error) {
      console.log(error);
      process.exit(1);
    }
  };
  
  runMain();