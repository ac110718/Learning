// SPDX-License-Identifier: UNLICENSED

pragma solidity ^0.8.4;

import "hardhat/console.sol";

contract WavePortal {
    // state variable stored permanently in contract storage
    uint256 totalWaves;

    constructor() {
        console.log("I am a smart contract.");
    }

    // msg.sender is like built-in authentication
    // functions can only be called with valid wallet

    function wave() public {
        totalWaves += 1;
        console.log("%s has waved!", msg.sender);
    }

    function getTotalWaves() public view returns (uint256) {
        console.log("We have %d total waves!", totalWaves);
        return totalWaves;
    }
}