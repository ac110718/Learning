import React, { useEffect, useState } from 'react';
import twitterLogo from './assets/twitter-logo.svg';
import './App.css';
import idl from './idl.json';
import { Connection, PublicKey, clusterApiUrl, Transaction, sendAndConfirmTransaction } from '@solana/web3.js';
import { Program, Provider, web3, BN } from '@project-serum/anchor';
import { Buffer } from 'buffer';
window.Buffer = Buffer;
import kp from './keypair.json'

const { SystemProgram, Keypair } = web3;

// establish permanent KeyPair for base account
const arr = Object.values(kp._keypair.secretKey)
const secret = new Uint8Array(arr)
const baseAccount = web3.Keypair.fromSecretKey(secret)

const programId = new PublicKey(idl.metadata.address);
const network = clusterApiUrl('devnet');
const opts = {
  preflightCommitment: "processed"
}

// Constants
const TWITTER_HANDLE = 'AC1531650';
const TWITTER_LINK = `https://twitter.com/${TWITTER_HANDLE}`;
const TEST_GIFS = [
  'https://media.giphy.com/media/ho0xXatV7b3Fo1ZRXN/giphy.gif',
  'https://media.giphy.com/media/Wmau3iOsVQoKdLgQcJ/giphy.gif',
  'https://media.giphy.com/media/QbtDhYTWo2hzsuS2U1/giphy.gif',
  'https://media.giphy.com/media/jtd6dzbJuEGYnP9QWv/giphy.gif'
]

const App = () => {

  const [walletAddress, setWalletAddress] = useState(null);
  const [inputValue, setInputValue] = useState('');
  const [tip, setTip] = useState('');
  const [gifList, setGifList] = useState([]);
  
  // Check Phantom wallet is connected
   const checkIfWalletIsConnected = async () => {
     try {
       const { solana } = window; // injected part of window object
       if (solana) {
         if (solana.isPhantom) {
           console.log('Phantom wallet found!');
           const response = await solana.connect({ onlyIfTrusted: true })
           console.log('Connected with Public Key: ', response.publicKey.toString());
           setWalletAddress(response.publicKey.toString());
         }
       } else {
         alert('Solana object not found! Get a Phantom Wallet');
       }
     } catch (error) {
       console.error(error);
     }
   };

  const connectWallet = async () => {
    const { solana } = window;
    if (solana) {
      const response = await solana.connect();
      console.log('Connected with Public Key: ', response.publicKey.toString());
      setWalletAddress(response.publicKey.toString());
    }
  };

  const sendGif = async () => {
    if (inputValue.length === 0) {
      console.log("No gif link given!")
      return
    }
    setInputValue('');
    console.log('Gif link:', inputValue);
    try {
      const provider = getProvider();
      const program = new Program(idl, programId, provider);

      await program.rpc.addGif(inputValue, {
        accounts: {
          baseAccount: baseAccount.publicKey,
          user: provider.wallet.publicKey,
        },
      });
      console.log("GIF successfully sent to program", inputValue)
      await getGifList();
    } catch (error) {
      console.log("Error sending GIF:", error)
    }
  };

  const addLike = async(index) => {
    try {
      const provider = getProvider();
      const program = new Program(idl, programId, provider);
      await program.rpc.addLike(new BN(index), {
        accounts: {
          baseAccount: baseAccount.publicKey,
          user: provider.wallet.publicKey,
        }
      });
      await getGifList();
    } catch (error) {
      console.log("Error liking", error);
    }
  }

  const onInputChange = (event) => {
    const {value} = event.target;
    setInputValue(value);
  };

  const onTipChange = (event) => {
    const {value} = event.target;
    setTip(value);
  };

  const getProvider = () => {
    const connection = new Connection(network, opts.preflightCommitment);
    const provider = new Provider(connection, window.solana, opts.preflightCommitment,);
    return provider;
  }

  const sendTip = async (index, amt) => {
    const connection = new Connection(network, opts.preflightCommitment);
    const provider = new Provider(connection, window.solana, opts.preflightCommitment,);
    const instructions = SystemProgram.transfer({
      fromPubkey: provider.wallet.publicKey,
      toPubkey: baseAccount.publicKey,
      lamports: new BN(amt),
    });
    const transaction = new Transaction().add(instructions);
    transaction.feePayer = await provider.wallet.publicKey;
    let blockhashObj = await connection.getRecentBlockhash();
    transaction.recentBlockhash = await blockhashObj.blockhash;

    let signed = await provider.wallet.signTransaction(transaction);
    let signature = await connection.sendRawTransaction(signed.serialize());
    await connection.confirmTransaction(signature);
    let balance = await connection.getBalance(baseAccount.publicKey);

    const program = new Program(idl, programId, provider);
    await program.rpc.addTip(new BN(index), new BN(amt), {
      accounts: {
        baseAccount: baseAccount.publicKey,
        user: provider.wallet.publicKey,
      }
    });
    
    console.log("Signature: ", signature);
    await getGifList();
  }

  // show when not connected
  const renderNotConnectedContainer = () => (
    <button className = "cta-button connect-wallet-button" onClick={connectWallet}>
        Connect to Wallet
    </button>
  );

  const renderConnectedContainer = () => {

    if (gifList === null) {
      return (
        <div className="connected-container">
          <button className="cta-button submit-gif-button" onClick={createGifAccount}>
            Do One-Time Initialization For GIF Program Account
          </button>
        </div>
      )
    } else {
      return (
        <div className="connected-container">
          <form onSubmit={(event) => { 
            event.preventDefault();
            sendGif();
          }}>
            <input type="text" placeholder="Enter gif link!" 
                value={inputValue} onChange={onInputChange} />
            <button type="submit" className="cta-button submit-gif-button">Submit</button>
          </form>
          <div className="gif-grid">
            {gifList.map((item, index) => (
              <div className="gif-item" key={index}>
                <img src={item.gifLink} />
                <div className="username"> By: {item.userAddress.toString()} </div>
                <div className="row">
                  <div className="likes"> 
                     <button type="submit" onClick={() => addLike(index)}         className="likebutton">♡</button>    
                    Favorites: {item.likes.toString()}     
                  </div>
                  <div className="lamports"> Lamports: {item.lamports.toString()} </div>
                </div>
                <div className="row2">
                  <input type="text" placeholder="Tip" value={tip} onChange={onTipChange} className="tipinput"/>
                <button type="submit" onClick={() => sendTip(index, tip)} className="tipbutton">Tip</button>
                </div>
              </div>
            ))}
          </div>
        </div>
    )}
  };
  
  useEffect(() => {
    const onLoad = async () => {
      await checkIfWalletIsConnected();
    };
    // wait for window to finish loading before checking solana object
    window.addEventListener('load', onLoad); 
    return () => window.removeEventListener('load', onLoad);
  }, []); // no dependencies, execute hook once

  const createGifAccount = async () => {
    try {
      const provider = getProvider();
      const program = new Program(idl, programId, provider);
      console.log("ping")
      await program.rpc.startStuffOff({
        accounts: {
          baseAccount: baseAccount.publicKey,
          user: provider.wallet.publicKey,
          systemProgram: SystemProgram.programId,
        },
        signers: [baseAccount]
      });
      console.log("Created a new BaseAccount w/ address:", baseAccount.publicKey.toString())
      await getGifList();
    } catch(error) {
      console.log("Error creating BaseAccount account:", error)
    }
  }

  const getGifList = async() => {
    try {
      const provider = getProvider();
      const program = new Program(idl, programId, provider);
      const account = await program.account.baseAccount.fetch(baseAccount.publicKey);

      console.log("Got the account", account)
      setGifList(account.gifList);
    } catch (error) {
      console.log("Error in getGifList: ", error)
      setGifList(null);
    }
  }
  useEffect(() => {
    if (walletAddress) {
      console.log('Fetching GIF list...');
      getGifList()
    }
  }, [walletAddress]); // run if we have a walletAddress

  
  return (
    <div className="App">
      <div className={walletAddress ? ' authed-container' : 'container'}>
        <div className="header-container">
          <p className="header">🖼 NFT GIF Portal</p>
          <p className="sub-text">
            View your favorite NFTs in the metaverse ✨
          </p>
          {!walletAddress && renderNotConnectedContainer()}
          {walletAddress && renderConnectedContainer()}
        </div>
      </div>
    </div>
  );
};

export default App;
