//creates a contract ABSTRACTION from the binary artifact.. 
//not exactly an instance, but something to interact with from truffle to construct the contract instance
const CryptoZombies = artifacts.require("CryptoZombies");

const utils = require("./helpers/utils");
const time = require("./helpers/time");
var expect = require('chai').expect;
const zombieNames = ["Zombie 1", "Zombie 2"];

contract("CryptoZombies", (accounts) => {
    let [alice, bob] = accounts;
    let contractInstance;

    //set up testing "hooks" that are needed before each unit test to avoid redundancy
    beforeEach(async () => {
        // INSTANCE.. is created from the ABSTRACTION.new() method
        //Call the method from the contract instance, not the abstraction (which was itself created by artifacts.require("Contract")
        contractInstance = await CryptoZombies.new();
    });

    it("should be able to create a new zombie", async () => {

        //Don't forget to call with await keyword
        //and to call with {from:Alice} to set msg.sender as there's no actual FUNCTION parameter for owner in the contract function
        const result = await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
        //chai test expressions rather than assert.equal()
        expect(result.receipt.status).to.equal(true);

        //recall that createRandomZombie ultimately emits the NewZombie event containing zombieId, name and dna
        //so therefore from results, you can call logs[0].args.name
        expect(result.logs[0].args.name).to.equal(zombieNames[0]);
    })

    it("should not allow two zombies", async () => {
        //don't need to store the result anywhere.. just call the function so that the second one fails
        await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
        // import utils.shouldThrow so you don't need to do a try / catch / assert fail.. 
        await utils.shouldThrow(contractInstance.createRandomZombie(zombieNames[1], {from: alice}));
    })

    //use context to group one or more semantically related multi-step tests.. like approve, transfer methods

    context("with the single-step transfer scenario", async () => {
        it("should transfer a zombie", async () => {
            const result = await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
            //remember id is "zombieId" in the event emitted.
            const zombieId = result.logs[0].args.zombieId.toNumber();
            //remember to call transferFrom specifically {from: alice} during the test
            await contractInstance.transferFrom(alice, bob, zombieId, {from: alice});
            //remember that all contract function calls are async and need await
            const newOwner = await contractInstance.ownerOf(zombieId);
            expect(newOwner).to.equal(bob);
        })
    })

    context("with the two-step transfer scenario", async () => {
        it("should approve and then transfer a zombie when the approved address calls transferFrom", async () => {
            const result = await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
            const zombieId = result.logs[0].args.zombieId.toNumber();
            await contractInstance.approve(bob, zombieId, {from: alice});
            //note {from: bob}
            await contractInstance.transferFrom(alice, bob, zombieId, {from: bob});
            const newOwner = await contractInstance.ownerOf(zombieId);
            expect(newOwner).to.equal(bob);
        })
        it("should approve and then transfer a zombie when the owner calls transferFrom", async () => {
            const result = await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
            const zombieId = result.logs[0].args.zombieId.toNumber();
            await contractInstance.approve(bob, zombieId, {from: alice});
            await contractInstance.transferFrom(alice, bob, zombieId, {from: alice});
            const newOwner = await contractInstance.ownerOf(zombieId);
            expect(newOwner).to.equal(bob);
         })
    })

    it("zombies should be able to attack another zombie", async () => {
        let result;
        result = await contractInstance.createRandomZombie(zombieNames[0], {from: alice});
        const firstZombieId = result.logs[0].args.zombieId.toNumber();
        result = await contractInstance.createRandomZombie(zombieNames[1], {from: bob});
        const secondZombieId = result.logs[0].args.zombieId.toNumber();

        //from the time.js file, which provides two functions from ganache
        //evm_increaseTime and evmMine (so that the updated time is mined to a block and subsequently read)
        //stored in the "increase" function under "time"
        //implemented by calling web3.currentProvider.sendAsync/send calling methods "evn_increaseTime" and "evm_mine"
        //duration helper function to convert days to seconds.. days function turns val * this.hours(24).. which in turn calls val * this.minutes(60).. down to seconds to be fed in

        await time.increase(time.duration.days(1));
        await contractInstance.attack(firstZombieId, secondZombieId, {from: alice});
        expect(result.receipt.status).to.equal(true);
    })
})
