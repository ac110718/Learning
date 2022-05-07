import "@nomiclabs/hardhat-ethers";
import { expect } from "chai";
import { ethers } from "hardhat";

describe("Hero", function() {
    async function createHero() {
        const Hero = await ethers.getContractFactory("TestHero");
        const hero = await Hero.deploy();
        await hero.deployed();
        return hero;
    }
    let hero;
    before(async function() {
        hero = await createHero()
    });
    it("should get a zero hero array.", async function() {
        expect(await hero.getHeroes()).to.deep.equal([]);
    })

    it("should fail at creating hero cause of payment", async function() {
        let e;
        try {
            await hero.createHero(0, {
                value: ethers.utils.parseEther("0.04999999")
            })
        } catch (err) {
            e = err;
        }

        expect(e.message.includes("Please send maor money")).to.equal(true);
    });
    it("should fail at creating hero cause of payment", async function() {
        const hero = await createHero();
        await hero.createHero(0, {
            value: ethers.utils.parseEther("0.05")
        });
        await hero.setRandom(69);
        await hero.createHero(0, {
            value: ethers.utils.parseEther("0.05")
        });
        const h = (await hero.getHeroes())[0];
        expect(await hero.getMagic(h)).to.equal(16);
    })
})