pragma solidity ^0.6.6;
import "@chainlink/contracts/src/v0.6/VRFConsumerBase.sol";

contract ZombieFactory is VRFConsumerbase {

    uint dnaDigits = 16;
    uint dnaModulus = 10 ** dnaDigits;

    bytes32 public keyHash;
    uint256 public fee;
    uint256 public randomResult;

    struct Zombie {
        string name;
        uint dna;
    }

    Zombie[] public zombies;

    constructor() VRFConsumerBase(
        0xb3dCcb4Cf7a26f6cf6B120Cf5A73875B7BBc655B,
        0x01BE23585060835E02B77ef475b0Cc51aA1e0709 
    ) public{
        keyHash = 0x2ed0feb3e7fd2022120aa84fab1945545a9f2ffc9076fd6156fa96eaff4c1311;
        fee = 100000000000000000;

    }

    function _createZombie(string memory _name, uint _dna) private {
        zombies.push(Zombie(_name, _dna));
    }

    // requestRandomness
    // This function checks to see that our contract has LINK tokens to pay a Chainlink node
    // Then, it sends some LINK tokens to the Chainlink node
    // Emits an event that the Chainlink node is looking for
    // Assigns a requestId to our request for a random number on-chain

    function getRandomNumber() public returns (bytes32 requestId) {
        return requestRandomness(keyHash, fee);
    }

    // fulfillRandomness
    // The Chainlink node first calls a function on the VRF Coordinator and includes a random number
    // The VRF Coordinator checks to see if the number is random
    // Then, it returns the random number the Chainlink node created, along with the original requestID from our request

    function fulfillRandomness(bytes32 requestId, uint256 randomness) internal override {
        randomResult = randomness;
    }

    // function _generatePseudoRandomDna(string memory _str) private view returns (uint) {
    //     uint rand = uint(keccak256(abi.encodePacked(_str)));
    //     return rand % dnaModulus;
    // }

}
