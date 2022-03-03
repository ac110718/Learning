const main = async () => {
  
  const [owner, otherPerson] = await hre.ethers.getSigners();
  const domainContractFactory = await hre.ethers.getContractFactory('Domains');
  const domainContract = await domainContractFactory.deploy("sol");
  await domainContract.deployed();
  console.log("Contract deployed to:", domainContract.address);
  console.log("Contract deployed by:", owner.address);

  let txn = await domainContract.register("achan", {value: hre.ethers.utils.parseEther('0.01234')});
  await txn.wait();

  const balance = await hre.ethers.provider.getBalance(domainContract.address);
  console.log("Contract balance:", hre.ethers.utils.formatEther(balance));

  try {
      txn = await domainContract.connect(otherPerson).withdraw();
      await txn.wait();
  } catch (error) {
      console.log(error)
  }

  let ownerBalance = await hre.ethers.provider.getBalance(owner.address);
  console.log("Balance of owner before withdrawal:", hre.ethers.utils.formatEther(ownerBalance));

  txn = await domainContract.connect(owner).withdraw();
  await txn.wait();

  const contractBalance = await hre.ethers.provider.getBalance(domainContract.address);
  ownerBalance = await hre.ethers.provider.getBalance(owner.address);

  console.log("Contract balance after withdrawal:", hre.ethers.utils.formatEther(contractBalance));
  console.log("Balance of owner after withdrawal:", hre.ethers.utils.formatEther(ownerBalance));

  try {
      txn = await domainContract.register("achan", {value: hre.ethers.utils.parseEther('0.01234')});
      await txn.wait();
  } catch (error) {
      console.log("Double registration", error);
  }

  try {
    txn = await domainContract.register("ac", {value: hre.ethers.utils.parseEther('0.01234')});
    await txn.wait();
} catch (error) {
    console.log("Invalid name", error.name);
}

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