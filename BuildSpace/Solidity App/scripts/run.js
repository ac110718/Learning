const main = async () => {
    const [owner, otherPerson] = await hre.ethers.getSigners();

    // compile contract and generate necessary files to work with contract
    // creates under artifacts directory
    // hre (hardhat runtime environment).. whenever you run npx hardhat, you get an hre object using the hardhat.config.js. No import necessary
    const waveContractFactory = await hre.ethers.getContractFactory("WavePortal");

    // create instance of the contract on local blockchain ethereum network
    // when this gets deployed, smartcontract functions become available to be called on the blockchain if they have public keyword
    const waveContract = await waveContractFactory.deploy({value: hre.ethers.utils.parseEther("0.1"),});

    // resolve promise first (i.e. execute contract constructor first) before moving on
    await waveContract.deployed();
    console.log("Contract deployed to:", waveContract.address);
    console.log("Contract deployed by:", owner.address);
    
    let contractBalance = await hre.ethers.provider.getBalance(waveContract.address);
    console.log("Contract balance:", hre.ethers.utils.formatEther(contractBalance));

    let waveCount;
    waveCount = await waveContract.getTotalWaves();
    console.log(waveCount.toNumber());

    let waveTxn = await waveContract.wave("Message #1");
    await waveTxn.wait();
    waveCount = await waveContract.getTotalWaves();
    console.log(waveCount.toNumber());
    contractBalance = await hre.ethers.provider.getBalance(waveContract.address);
    console.log("Contract balance:", hre.ethers.utils.formatEther(contractBalance));


    waveTxn = await waveContract.connect(otherPerson).wave("Message #2");
    await waveTxn.wait();
    waveCount = await waveContract.getTotalWaves();
    console.log(waveCount.toNumber());
    contractBalance = await hre.ethers.provider.getBalance(waveContract.address);
    console.log("Contract balance:", hre.ethers.utils.formatEther(contractBalance));

    waveTxn = await waveContract.connect(otherPerson).wave("Message #3 Too Soon");
    await waveTxn.wait();
    waveCount = await waveContract.getTotalWaves();
    console.log(waveCount.toNumber());
    contractBalance = await hre.ethers.provider.getBalance(waveContract.address);
    console.log("Contract balance:", hre.ethers.utils.formatEther(contractBalance));


    let allWaves = await waveContract.getAllWaves();
    console.log(allWaves);
};

const runMain = async () => {
    try {
        await main();
        process.exit(0); // successful run
    } catch (error) {
        console.log(error);
        process.exit(1);
    }
};

runMain();