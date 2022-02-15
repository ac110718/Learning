pragma solidity ^0.4.24;

//abstract contract
contract FundingLimitStrategy {
    function isFullInvestmentWithinLimit(uint256 _investment, uint256 _fullInvestmentReceived) public view returns (bool);
}

//concrete instance with methods implemented
contract CappedFundingStrategy is FundingLimitStrategy {
    uint256 fundingCap;
    constructor(uint256 _fundingCap) public {
        require (_fundingCap > 0);
        fundingCap = _fundingCap;
    }
    function isFullInvestmentWithinLimit(uint256 _investment, uint256 _fullInvestmentReceived) public view returns (bool) {
        bool check = _fullInvestmentReceived + _investment < fundingCap;
        return check;
    }
}

//just return true given unlimited
contract UnlimitedFundingStrategy is FundingLimitStrategy {
    function isFullInvestmentWithinLimit(uint256 _investment, uint256 _fullInvestmentReceived) public view returns (bool) {
        return true;
    }
}