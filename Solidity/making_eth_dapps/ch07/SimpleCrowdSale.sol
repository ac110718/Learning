pragma solidity ^0.4.24;

import "./ReleasableSimpleCoin.sol";
import "./Ownable.sol";
import "./Pausable.sol";
import "./Destructible.sol";
import "./FundingLimitStrategy.sol";

//allow token substitution
interface ReleasableToken {
    function mint(address _beneficiary, uint256 _numberOfTokens) external;
    function release() external;
    function transfer(address _to, uint256 _amount) external;
}

//inherit onlyOwner modifier
contract SimpleCrowdSale is Pausable, Destructible {
    uint256 public startTime;
    uint256 public endTime;
    uint256 public weiTokenPrice;
    uint256 public weiInvestmentObjective;

    mapping (address => uint256) public investmentAmountOf;
    uint256 public investmentReceived;
    uint256 public investmentRefunded;

    bool public isFinalized;
    bool public isRefundingAllowed;

    ReleasableToken public crowdsaleToken;
    FundingLimitStrategy internal fundingLimitStrategy;

    constructor(uint256 _startTime, uint _endTime, uint256 _weiTokenPrice, uint256 _weiInvestmentObjective) payable public {
        require(_startTime >= now);
        require(_endTime >= _startTime);
        require(_weiTokenPrice != 0);
        require(_weiInvestmentObjective !=0);

        startTime = _startTime;
        endTime = _endTime;
        weiTokenPrice = _weiTokenPrice;
        weiInvestmentObjective = _weiInvestmentObjective;

        crowdsaleToken = createToken(); // indirection to allow override
        isFinalized = false;
        fundingLimitStrategy = createFundingLimitStrategy();

    }

    event LogInvestment(address indexed investor, uint256 value);
    event LogTokenAssignment(address indexed investor, uint256 numTokens);
    event Refund(address investor, uint256 value);

    // this function can be overriden to replace SimpleCoin with any other Token that implements ReleasableToken interface
    function createToken() internal returns (ReleasableToken) {
        return new ReleasableSimpleCoin(0);
    }

    function invest() public payable {
        require(isValidInvestment(msg.value));
        address investor = msg.sender;
        uint256 investment = msg.value;
        investmentAmountOf[investor] += investment;
        investmentReceived += investment;
        assignTokens(investor, investment);
        emit LogInvestment(investor, investment);
    }

    function isValidInvestment(uint256 _investment) internal view returns (bool) {
        bool nonZeroInvestment = _investment != 0;
        bool withinCrowdsalePeriod = now >= startTime && now <= endTime;
        return nonZeroInvestment && withinCrowdsalePeriod && fundingLimitStrategy.isFullInvestmentWithinLimit(_investment, investmentReceived);
    }

    function assignTokens(address _beneficiary, uint256 _investment) internal {
        uint256 _numberOfTokens = calculateNumberOfTokens(_investment);
        crowdsaleToken.mint(_beneficiary, _numberOfTokens);
    }

    //abstract method to be implemented via pricing strategy
    function calculateNumberOfTokens(uint256 _investment) internal returns (uint256) {
    }

    //abstract method to be implemented via funding limit strategy
    function createFundingLimitStrategy() internal returns (FundingLimitStrategy);

    function finalize() onlyOwner public {
        if (isFinalized) revert();

        bool isCrowdsaleComplete = now > endTime;
        bool investmentObjectiveMet = investmentReceived >= weiInvestmentObjective;

        if (isCrowdsaleComplete)
            if (investmentObjectiveMet)
                //don't allow token use until fundraising is over
                crowdsaleToken.release();
            else
                isRefundingAllowed = true;
            
            isFinalized = true;
    }

    function refund() public {
        if (!isRefundingAllowed) revert();
        
        address investor = msg.sender;
        uint256 investment = investmentAmountOf[investor];
        if (investment == 0) revert();
        investmentAmountOf[investor] = 0; // set to zero first to avoid double dipping
        investmentRefunded += investment;
        emit Refund(msg.sender, investment);
        if (!investor.send(investment)) revert(); // will be sent within the if statement
    }
}