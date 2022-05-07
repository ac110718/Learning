// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Hero {
    enum Class { Mage, Healer, Barbarian }

    mapping(address => uint[]) addressToHeroes;

    function generateRandom() public virtual view returns (uint) {
        return uint(keccak256(abi.encodePacked(block.difficulty, block.timestamp)));
    }

    function getHeroes() public view returns (uint[] memory) {
        return addressToHeroes[msg.sender];
    }

    function getStrength(uint hero) public pure returns (uint32) {
        return uint32((hero >> 2) & 0x1F); // five 1s in a row
    }

    function getHealth(uint hero) public pure returns (uint32) {
        return uint32((hero >> 7) & 0x1F); // five 1s in a row
    }

    function getDex(uint hero) public pure returns (uint32) {
        return uint32((hero >> 12) & 0x1F); // five 1s in a row
    }

    function getIntellect(uint hero) public pure returns (uint32) {
        return uint32((hero >> 17) & 0x1F); // five 1s in a row
    }

    function getMagic(uint hero) public pure returns (uint32) {
        return uint32((hero >> 22) & 0x1F); // five 1s in a row
    }

    function createHero(Class class) public payable {
        require(msg.value >= 0.05 ether, "Please send maor money");
        uint[] memory stats = new uint[](5);
        stats[0] = 2; // hero is first two bits
        stats[1] = 7;
        stats[2] = 12;
        stats[3] = 17;
        stats[4] = 22;

        uint len = 5;
        uint hero = uint(class);

        do {
            uint pos = generateRandom() % len;
            uint value = generateRandom() % (13 + len) + 1; // value from 1-18, 1-17, 1-16, etc
            hero |= value << stats[pos]; // store the value into hero int, shifted over by the offset specified by position array
            len--;
            stats[pos] = stats[len]; // randomize the offset
        } while (len > 0);
        addressToHeroes[msg.sender].push(hero);
        
    }
}