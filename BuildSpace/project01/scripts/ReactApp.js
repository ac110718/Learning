// https://waveportal-starter-project.allenchan3.repl.co/

import React, { useEffect, useState } from "react";
import './App.css';
import {ethers} from "ethers"; // library to talk to contract
import abi from "./utils/WavePortal.json";

const App = () => {
  
  // store user public wallet
  const [currentAccount, setCurrentAccount] = useState("");
  const [allWaves, setAllWaves] = useState([]);
  const [waveMessage, setWaveMessage] = useState("");
  const [statusText, setStatusText] = useState("");
  // artifacts and address generated from compilation and deployment to testnet
  const contractAddress = "0x9DD11c8feffCF468E62cF468bb845689a704c90F";
  const contractABI = abi.abi;
  
  const checkIfWalletIsConnected = async () => {
    try {
      // check access to window.ethereum
      const { ethereum } = window;
      if (!ethereum) {
        setStatusText("Make sure you have metamask!");
        return;
      } else {
        console.log("We have the ethereum object", ethereum);
      }
      // check authorization to use wallet
      const accounts = await ethereum.request({method: "eth_accounts"});
      if (accounts.length !== 0) {
        const account = accounts[0];
        console.log("Found an authorized account:", account);
        setCurrentAccount(account);
        setStatusText("Connected To "+account.toString());
        getAllWaves();
      } else {
        setStatusText("Connect MetaMask account (Rinkeby) first!");
      }
    } catch (error) {
      console.log(error);
    }
  }

  const connectWallet = async() => {
    try {
      const {ethereum} = window;
      if (!ethereum) {
        alert("Get MetaMask!");
        return;
      }
      const accounts = await ethereum.request({method: "eth_requestAccounts"});
      console.log("Connected", accounts[0]);
      setCurrentAccount(accounts[0]);
      setStatusText("Connected To "+accounts[0].toString());
      getAllWaves();
    } catch (error) {
      console.log(error)
    }
  }

  const getAllWaves = async () => {
    try {
      const { ethereum } = window;
      if (ethereum) {
        const provider = new ethers.providers.Web3Provider(ethereum);
        const signer = provider.getSigner();
        const wavePortalContract = new ethers.Contract(contractAddress, contractABI, signer);
        const waves = await wavePortalContract.getAllWaves();
        let wavesCleaned = [];
        waves.forEach(wave => {
          wavesCleaned.push({
            address: wave.waver,
            timestamp: new Date(wave.timestamp * 1000),
            message: wave.message,
            earned: wave.amtWon
          });
        });
        setAllWaves(wavesCleaned);
      } else {
        console.log("Ethereum object doesn't exist!")
      }
    } catch (error) {
      console.log(error);
    }
  }

  const wave = async () => {
    try {
      const {ethereum} = window;
      if (ethereum) {
        // providers to talk to ethereum nodes, specifically the ones provided by Metamask
        const provider = new ethers.providers.Web3Provider(ethereum);
        const signer = provider.getSigner();
        const wavePortalContract = new ethers.Contract(contractAddress, contractABI, signer);
        // free read from public function getTotalWaves
        let count = await wavePortalContract.getTotalWaves();
        console.log("Retrieved total wave count...", count.toNumber());
        // execute actual write to blockchain
        const waveTxn = await wavePortalContract.wave(waveMessage, { gasLimit: 300000});
        setStatusText("Mining... txHash: " + waveTxn.hash);
        await waveTxn.wait();
        setStatusText("Mined! txHash: " + waveTxn.hash);
        // update read
        count = await wavePortalContract.getTotalWaves();
        console.log("Retrieved total wave count...", count.toNumber());
      } else {
        console.log("Ethereum object doesn't exist!");
      }
    } catch (error) {
      console.log(error);
    }
  }

  // run function when page loads
  useEffect(() => {
    checkIfWalletIsConnected();
  }, [])

  // listen for emitted events
  useEffect(() => {
    let wavePortalContract;

    // called when new "NewWave" event emitted, taking in parameters
    const onNewWave = (from, timestamp, message, amtWon) => {
      setAllWaves(prevState => [...prevState, {
        address: from,
        timestamp: new Date(timestamp * 1000),
        message: message,
        earned: amtWon,
      }]);
    };

    if (window.ethereum) {
      const provider = new ethers.providers.Web3Provider(window.ethereum);
      const signer = provider.getSigner();
      wavePortalContract = new ethers.Contract(contractAddress, contractABI, signer);
      wavePortalContract.on("NewWave", onNewWave);
    }

    return () => {
      if (wavePortalContract) {
        wavePortalContract.off("NewWave", onNewWave);
      }
    };
  }, []);

  return (
    <div className="mainContainer">
      <div className="dataContainer">
          <div className="header"> Wave Portal <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/01/Ethereum_logo_translucent.svg/800px-Ethereum_logo_translucent.svg.png" width="25"/></div>
        <div className="bio">
        Post a message with 50% chance of winning (rinkeby) eth
        </div>
        <div className = "status">{statusText}</div>
        <input type = "text" value = {waveMessage} placeholder = "Type Message Here..." onChange = {(e) => setWaveMessage(e.target.value)} />
        <button className="waveButton" onClick={wave}>
          Post Message To Blockchain
        </button>
        {!currentAccount && (
          <button className="waveButton" onClick={connectWallet}>
            Connect Wallet
          </button>
        )}
        {allWaves.map((wave, index) => {
      console.log(wave.timestamp.toLocaleDateString());
          return (
            <div key={index} className="messageTile">
              <div className="message"> {wave.message} </div>
              <div>
                <div className="earn"> Earned: {(wave.earned/(10**18)).toString()+" eth"} </div>
                <div className="date"> {wave.timestamp.toLocaleDateString("en-US", {year: "numeric", month: "long", day: "numeric", hour12: true, hour: "2-digit", minute: "2-digit"})} </div>
              </div>
              <div className="address"> Address: {wave.address} </div>
            </div>
          )
        }).reverse()}
      </div>
    </div>
  );
}

export default App