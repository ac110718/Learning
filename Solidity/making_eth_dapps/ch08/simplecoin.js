var web3 = new Web3 ( new Web3.providers.HttpProvider("http://localhost:8545"));

var abi = [
    {
        "inputs": [
            {
                "internalType": "uint256",
                "name": "_initialSupply",
                "type": "uint256"
            }
        ],
        "stateMutability": "nonpayable",
        "type": "constructor"
    },
    {
        "anonymous": false,
        "inputs": [
            {
                "indexed": true,
                "internalType": "address",
                "name": "from",
                "type": "address"
            },
            {
                "indexed": true,
                "internalType": "address",
                "name": "to",
                "type": "address"
            },
            {
                "indexed": false,
                "internalType": "uint256",
                "name": "value",
                "type": "uint256"
            }
        ],
        "name": "Transfer",
        "type": "event"
    },
    {
        "inputs": [
            {
                "internalType": "address",
                "name": "",
                "type": "address"
            }
        ],
        "name": "coinBalance",
        "outputs": [
            {
                "internalType": "uint256",
                "name": "",
                "type": "uint256"
            }
        ],
        "stateMutability": "view",
        "type": "function"
    },
    {
        "inputs": [
            {
                "internalType": "address",
                "name": "_to",
                "type": "address"
            },
            {
                "internalType": "uint256",
                "name": "_amount",
                "type": "uint256"
            }
        ],
        "name": "transfer",
        "outputs": [],
        "stateMutability": "nonpayable",
        "type": "function"
    }
];

var SimpleCoinContractInstance = new web3.eth.Contract(abi, '0x5552130f2445063Bce5A6b8D98E7DfFFf6905a9C');

async function refreshAccountsTable() {
    let accounts = await web3.eth.getAccounts();
    var innerHtml = "<tr><td>Account</td><td>Balance</td>";
    for (let i = 0; i < accounts.length; i++) {
        let account = accounts[i];
        let balance = await SimpleCoinContractInstance.methods.coinBalance(account).call();
        innerHtml = innerHtml + "<tr><td>" + account + "</td><td>" + balance + "</td></tr>";
    }
    $("#accountsBalanceTable").html(innerHtml);
}

async function transferCoins() {
    var sender = $("#from").val();
    console.log(sender);
    var recipient = $("#to").val();
    console.log(recipient);
    var tokensToTransfer = $("#amount").val();
    await SimpleCoinContractInstance.methods
        .transfer(recipient, tokensToTransfer)
        .send({from: sender, gas: 200000})
        .then(function(receipt) {
            console.log(receipt);
            refreshAccountsTable();
        })
}

$(document).ready(function() {
    refreshAccountsTable();
});
