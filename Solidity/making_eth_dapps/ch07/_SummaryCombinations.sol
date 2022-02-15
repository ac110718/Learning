pragma solidity ^0.4.24;
import "./PricingStrategies.sol";
import "./FundingLimitStrategy.sol";

//FIXED PRICING VARIATIONS

contract UnlimitedFixedPricingCrowdsale is FixedPricingCrowdSale {
    constructor(uint256 _startTime, uint256 _endTime, uint256 _weiTokenPrice, uint256 _etherInvestmentObjective)
        FixedPricingCrowdSale(_startTime, _endTime, _weiTokenPrice, _etherInvestmentObjective) payable public {
        
        //concrete implementation
        function createFundingLimitStrategy() internal returns (FundingLimitStrategy) {
            return new UnlimitedFundingStrategy();
        }

    }
}

contract CappexFixedPricingCrowdsale is FixedPricingCrowdSale {
    constructor(uint256 _startTime, uint256 _endTime, uint256 _weiTokenPrice, uint256 _etherInvestmentObjective)
        FixedPricingCrowdSale(_startTime, _endTime, _weiTokenPrice, _etherInvestmentObjective) payable public {
        
        //concrete implementation
        function createFundingLimitStrategy() internal returns (FundingLimitStrategy) {
            return new CappedFundingStrategy(10000);
        }

    }
}

//TRANCHE PRICING VARIATIONS

contract UnlimitedTranchePricingCrowdsale is TranchePricingCrowdSale {
    constructor(uint256 _startTime, uint256 _endTime, uint256 _etherInvestmentObjective)
        TranchePricingCrowdSale(_startTime, _endTime, _etherInvestmentObjective) payable public {
        
        //concrete implementation
        function createFundingLimitStrategy() internal returns (FundingLimitStrategy) {
            return new UnlimitedFundingStrategy();
        }

    }
}

contract UnlimitedTranchePricingCrowdsale is TranchePricingCrowdSale {
    constructor(uint256 _startTime, uint256 _endTime, uint256 _etherInvestmentObjective)
        TranchePricingCrowdSale(_startTime, _endTime, _etherInvestmentObjective) payable public {
        
        //concrete implementation
        function createFundingLimitStrategy() internal returns (FundingLimitStrategy) {
            return new CappedFundingStrategy(10000);
        }

    }
}

//WITH COMPLEX COIN


contract UnlimitedFixedPricingCrowdsaleWithComplexCoin is UnlimitedFixedPricingCrowdSale {
    constructor(uint256 _startTime, uint256 _endTime, uint256 _weiTokenPrice, uint256 _etherInvestmentObjective)
        UnlimitedFixedPricingCrowdSale(_startTime, _endTime, _weiTokenPrice, _etherInvestmentObjective) payable public {
        
        //override implementation with complex coin
        function createToken() internal returns (ReleasableToken) {
            return new ReleasableComplexCoin(); // DEFINED ELSEWHERE
        }

    }
}