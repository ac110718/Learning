//getting data from oracle is a multi-step process
//the client calls the "caller smart contract"
//the caller contract in turn calls the "oracle contract" 
//and forwards the response back to the client

// the "oracle CONTRACT" in turn generates a requestId, sends the request
// to the actual oracle SERVICE (and this service in turn pings the API).
// the requestId also gets sent to the caller in meantime

// oracle CONTRACT validates what it got from the service
// and returns the response it got, along with ID back to the caller
// caller then updates the ethPrice and returns to the client.

pragma solidity 0.5.0;

import "./EthPriceOracleInterface.sol";
import "openzeppelin-solidity/contracts/ownership/Ownable.sol";

contract CallerContract is Ownable {
  
  uint256 private ethPrice;
  // Oracle Interface is necessary to instantiate an instance so you can call all of its (external) methods
  // in this case.. getLatestEthPrice()
  // ultimately gets instantiated with address provided for the oracle
  EthPriceOracleInterface private oracleInstance;
  address private oracleAddress;
  mapping(uint256=>bool) myRequests;
  event newOracleAddressEvent(address oracleAddress);
  event ReceivedNewRequestIdEvent(uint256 id);
  event PriceUpdatedEvent(uint256 ethPrice, uint256 id);

  //set up oracle instance
  //remember to set the onlyOwner constraint so calls can be limited to owner
  function setOracleInstanceAddress (address _oracleInstanceAddress) public onlyOwner {
    oracleAddress = _oracleInstanceAddress;
    oracleInstance = EthPriceOracleInterface(oracleAddress);
    //allow the client to realize a new oracle address has been commited
    emit newOracleAddressEvent(oracleAddress);
  }

  // to actually update the price is a two-step process..
  // calls the oracle's getLatestEthPrice() function
  // this just returns a receipt id
  // AFTER the oracle gets the eth price.. it will execute a callback function
  // exposed by the caller contract.. but this is a separate function defined elsewhere
  // at this stage, you just get the id to mark as pending under myRequests mapping
  function updateEthPrice() public {
    uint256 id = oracleInstance.getLatestEthPrice();
    myRequests[id] = true;
    emit ReceivedNewRequestIdEvent(id);
  }

  // the ORACLE will call this function ONLY after it received the eth price has been fetched
  // must be contrained to only the Oracle calling this function and the id == original 
  // request id associated with updateEthPrice() request
  // then you set the eth price and delete from pending requests
  // emit priceupdate event to client
  function callback(uint256 _ethPrice, uint256 _id) public onlyOracle {
    require(myRequests[_id], "This request is not in my pending list.");
    ethPrice = _ethPrice;
    delete myRequests[_id];
    emit PriceUpdatedEvent(_ethPrice, _id);
  }
  
  modifier onlyOracle() {
    require(msg.sender == oracleAddress, "You are not authorized to call this function.");
    _;
  }
}
