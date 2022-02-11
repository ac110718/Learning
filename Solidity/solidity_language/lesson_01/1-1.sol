pragma solidity >=0.5.0 <0.6.0;

contract ZombieFactory {

    //frontend will listen for events to be emitted from contract
    event NewZombie(uint zombieId, string name, uint dna);

    uint dnaDigits = 16;
    uint dnaModulus = 10 ** dnaDigits;

    struct Zombie {
        string name;
        uint dna;
    }

    Zombie[] public zombies;

    //memory keyword for anything passed via reference. mark private otherwise defaults to public
    function _createZombie(string memory _name, uint _dna) private {
        //push returns size of array
        uint id = zombies.push(Zombie(_name, _dna)) - 1;
        emit NewZombie(id, _name, _dna);
    }

    //view keyword means variables in memory accessed but not modified, include return type at end
    function _generateRandomDna(string memory _str) private view returns (uint) {
        //keccak256 hash function but takes in bytes.. based on name provided
        //abi = application binary interface
        //cast hexadecimal as uint
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        //returns 16 digit random number based on hash
        return rand % dnaModulus;
    }

    function createRandomZombie(string memory _name) public {
        uint randDna = _generateRandomDna(_name);
        _createZombie(_name, randDna);
    }

}