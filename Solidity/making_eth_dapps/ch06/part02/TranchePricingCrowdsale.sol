pragma solidity ^0.4.24;

import "./SimpleCrowdSale.sol";

contract TranchePricingCrowdsale is SimpleCrowdSale {
    
    struct Tranche {
        uint256 weiHighLimit; // up to certain amount invested already...
        uint256 weiTokenPrice; //... determiane the price
    }

    mapping(uint256 => Tranche) public trancheStructure;
    uint256 public currentTrancheLevel;

    constructor(uint256 _startTime, uint256 _endTime, uint256 _etherInvestmentObjective) 
        SimpleCrowdSale (_startTime, _endTime, 1, _etherInvestmentObjective) payable public {
            {
                trancheStructure[0] = Tranche(3000 ether, 0.002 ether); // under 3K 0.002 conversion price
                trancheStructure[1] = Tranche(10000 ether, 0.003 ether);
                trancheStructure[2] = Tranche(15000 ether, 0.004 ether);
                trancheStructure[3] = Tranche(100000 ether, 0.005 ether);

                currentTrancheLevel = 0;
            }
    }

    //override
    function calculateNumberOfTokens(uint256 investment) internal returns (uint256) {
        updateCurrentTrancheAndPrice();
        return investment / weiTokenPrice;
    }

    function updateCurrentTrancheAndPrice() internal {
        uint256 i = currentTrancheLevel;
        while (trancheStructure[i].weiHighLimit < investmentReceived)
            ++i; // increment tranche to current investment levels
        currentTrancheLevel = i;
        weiTokenPrice = trancheStructure[currentTrancheLevel].weiTokenPrice; // set conversion level
    }
}