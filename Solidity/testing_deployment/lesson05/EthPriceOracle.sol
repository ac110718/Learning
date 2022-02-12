pragma solidity 0.5.0;
import "openzeppelin-solidity/contracts/access/Roles.sol";
import "openzeppelin-solidity/contracts/math/SafeMath.sol";
import "./CallerContractInterface.sol";

// no longer an "Ownable" contract but will be accessed by multiple oracle services
// specified by the owner (which in turn is specified in the contructor)
// and there can be multiple owners, or can go from zero to one under
// add.. has.. remove methods of Role

// ultimately allows oracle to "average" from multiple services who can execute methods
// from this contract.

contract EthPriceOracle {
  // allow separate roles for different levels of access
  // namely multiple oracles to feed into the service.. separate from that of
  // ownership role
  using Roles for Roles.Role;
  Roles.Role private owners;
  Roles.Role private oracles;

  using SafeMath for uint256;
  uint private randNonce = 0;
  uint private modulus = 1000;
  uint private numOracles = 0;
  uint private THRESHOLD = 0;

  mapping(uint256=>bool) pendingRequests;

  struct Response {
    address oracleAddress;
    address callerAddress;
    uint256 ethPrice;
  }

  event GetLatestEthPriceEvent(address callerAddress, uint id);
  event SetLatestEthPriceEvent(uint256 ethPrice, address callerAddress);

  event AddOracleEvent(address oracleAddress);
  event RemoveOracleEvent(address oracleAddress);
  event SetThresholdEvent (uint threshold);

  // add an owner to the owners "role" or list
  constructor (address _owner) public {
    owners.add(_owner);
  }
  // add multiple oracles.. constrain to only owner calling this function
  function addOracle (address _oracle) public {
    require(owners.has(msg.sender), "Not an owner!");
    //disallow duplicates
    require(!oracles.has(_oracle), "Already an oracle!");
    oracles.add(_oracle);
    numOracles++;
    emit AddOracleEvent(_oracle);
  }

  //constrain to only owners and disallow double deletes and removal of last oracle
  function removeOracle (address _oracle) public {
    require(owners.has(msg.sender), "Not an owner!");
    require(oracles.has(_oracle), "Not an oracle!");
    require (numOracles > 1, "Do not remove the last oracle!");
    oracles.remove(_oracle);
    numOracles--;
    emit RemoveOracleEvent(_oracle);
  }

  //threshold for averaging Eth price
  function setThreshold (uint _threshold) public {
    require(owners.has(msg.sender), "Not an owner!");
    THRESHOLD = _threshold;
    emit SetThresholdEvent(THRESHOLD);
  }

  function getLatestEthPrice() public returns (uint256) {
    randNonce++;
    uint id = uint(keccak256(abi.encodePacked(now, msg.sender, randNonce))) % modulus;
    pendingRequests[id] = true;
    emit GetLatestEthPriceEvent(msg.sender, id);
    return id;
  }

  //can be called only from an oracle in the list.. and for a pending request id
  function setLatestEthPrice(uint256 _ethPrice, address _callerAddress, uint256 _id) public {
    require(oracles.has(msg.sender), "Not an oracle!");
    require(pendingRequests[_id], "This request is not in my pending list.");

    //response struct to store the oracle, caller of request, ethPrice
    Response memory resp;
    resp = Response(msg.sender, _callerAddress, _ethPrice);

    //mapping of all responses associated with requestID (an array of responses)
    requestIdToResponse[_id].push(resp);
    uint numResponses = requestIdToResponse[_id].length;

    //process the responses ONLY once you hit threshold for averaging
    if (numResponses == THRESHOLD) {
      //safeMath
      uint computedEthPrice = 0;
        for (uint f=0; f < requestIdToResponse[_id].length; f++) {
        computedEthPrice = computedEthPrice.add(requestIdToResponse[_id][f].ethPrice);
      }
      computedEthPrice = computedEthPrice.div(numResponses);

      //remove pending requests only after you collect enough responses
      delete pendingRequests[_id];
      delete requestIdToResponse[_id];

      // instantiate caller contract instance to execute the callback
      // passing through the average ethprice and requestId
      CallerContractInterface callerContractInstance;
      callerContractInstance = CallerContractInterface(_callerAddress);
      callerContractInstance.callback(computedEthPrice, _id);

      //emit event
      emit SetLatestEthPriceEvent(computedEthPrice, _callerAddress);
    }
  }
}
