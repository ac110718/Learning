pragma solidity ^ 0.4.0;

contract SimpleCoin {
    mapping (address => uint256) public coinBalance;
    
    constructor() public {
        coinBalance[0x14723A09ACff6D2A60DcdF7aA4AFf308FDDC160C] = 10000;
    }

    function transfer(address _to, uint256 _amount) public {
        coinBalance[msg.sender] -= _amount;
        coinBalance[_to] += _amount;
    }

}
/*  Notes:

* web user interface communicates directly with specific node of the network through a client-side Javascript library called Web3.js
* P2P network made of full nodes (read, validate, execute, pass messages stored on blockchain but do not WRITE) and mining nodes ( WRITE new blocks for gas fees and new eth ). All nodes propagate messages and transactions
* nodes are called clients because while they are servers, they are also "clients" of other nodes. Communicate through protocol called Wire.
* each node has (1) Client that executes apps and implements standard interface + Wire protocol. Written in different languages like C++, Go, etc, and (2) copy of the blockchain
* from a "temporal" perspective.. 1. JS web app makes request, 2. web app through web3 library calls method on contract instance sitting at a specific node, 3. transaction is validated and propagated to peers..until 4. it hits a mining node.. 5. new block is created.. 6. block is propagated until it goes back to original node.. 7. node emits new event that is read by the web client.. 8. client callback function executed upon event being read
* useful dapps are yes to these questions: 1. need multiple writing parties, 2. writing parties have no trust in each other, 3. all parties want to modify state of database, 4. writing parties need to all interact with each other
* otherwise.. there are downsides. huge time lags in data processing and "instant" functions
* remix IDE readily available via browser.. compile on virtual EVM with pre-provided accounts (under deploy tab). Once deployed, buttons show up for various methods of the contract

*/