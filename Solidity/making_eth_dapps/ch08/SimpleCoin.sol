//pragma solidity ^0.4.0;
pragma solidity ^0.8.11;

contract SimpleCoin {
    mapping (address => uint256) public coinBalance;
    event Transfer(address indexed from, address indexed to, uint256 value);
    
    constructor(uint256 _initialSupply) public {
        coinBalance[msg.sender] = _initialSupply;
    }

    function transfer(address _to, uint256 _amount) public {
        require(coinBalance[msg.sender] > _amount);
        require(coinBalance[_to] + _amount >= coinBalance[_to]);
        coinBalance[msg.sender] -= _amount;
        coinBalance[_to] += _amount;
        emit Transfer(msg.sender, _to, _amount);
    }

}

/* NOTES
* nodeless deployment is possible on remix under injected web3 (connect metamask)
* most EVM operations cost only 3 gas but load from storage is 200, storing to storage is 5000+, contract creation is 32,000
*/