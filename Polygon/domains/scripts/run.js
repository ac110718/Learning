const main = async () => {
  
  const [owner, otherPerson] = await hre.ethers.getSigners();
  const domainContractFactory = await hre.ethers.getContractFactory('Domains');
  const domainContract = await domainContractFactory.deploy("sol");
  await domainContract.deployed();
  console.log("Contract deployed to:", domainContract.address);
  console.log("Contract deployed by:", owner.address);

  let txn = await domainContract.register("achan", {value: hre.ethers.utils.parseEther('0.1')});
  await txn.wait();

  const domainOwner = await domainContract.getAddress("achan");
  console.log("Owner of domain achan:", domainOwner);

  const balance = await hre.ethers.provider.getBalance(domainContract.address);
  console.log("Contract balance:", hre.ethers.utils.formatEther(balance));

  txn = await domainContract.connect(owner).setRecord("achan", "this is my bio");
  await txn.wait(); 
  const record = await domainContract.getRecord("achan");
  console.log("Record output:", record);
};

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