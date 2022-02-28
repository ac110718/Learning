// SPDX-License-Identifier: UNLICENSED

pragma solidity ^0.8.4;

import "hardhat/console.sol";

contract WavePortal {
    // state variable stored permanently in contract storage
    uint256 totalWaves;

    // help generate random number
    uint256 private seed;

    event NewWave(address indexed from, uint256 timestamp, string message, uint amtWon);

    struct Wave {
        address waver;
        string message;
        uint256 timestamp;
        uint256 amtWon;
    }

    Wave[] waves;

    // keep track of who has submitted
    mapping(address => uint256) public lastWavedAt;

    // called by front-end with value parameter so make 'payable'
    constructor() payable {
        console.log("Constructed.");
        seed = (block.timestamp + block.difficulty) % 100;
    }

    // msg.sender is like built-in authentication
    // functions can only be called with valid wallet

    function wave(string memory _message) public {
        //cool off
        require(lastWavedAt[msg.sender] + 30 seconds < block.timestamp, "Wait 15m");
        lastWavedAt[msg.sender] = block.timestamp;

        totalWaves += 1;
        console.log("%s waved w/ message %s", msg.sender, _message);
        

        seed = (block.difficulty + block.timestamp + seed) % 100;
        console.log("Random # generated: %d", seed);
        uint256 winnings = 0;
        if (seed <= 50) {
            console.log("%s won!", msg.sender);
            uint256 prizeAmount = 0.0001 ether;
            require(prizeAmount <= address(this).balance, "Trying to withdraw more money than the contract has.");
            (bool success, ) = (msg.sender).call{value: prizeAmount}("");
            require(success, "Failed to withdraw money from contract.");
            winnings = prizeAmount;
        }
        waves.push(Wave(msg.sender, _message, block.timestamp, winnings));
        emit NewWave(msg.sender, block.timestamp, _message, winnings);
    }

    function getAllWaves() public view returns (Wave[] memory) {
        return waves;
    }

    function getTotalWaves() public view returns (uint256) {
        console.log("We have %d total waves!", totalWaves);
        return totalWaves;
    }
}