const axios = require('axios')
const BN = require('bn.js')
const common = require('./utils/common.js')
const SLEEP_INTERVAL = process.env.SLEEP_INTERVAL || 2000
const PRIVATE_KEY_FILE_NAME = process.env.PRIVATE_KEY_FILE || './oracle/oracle_private_key'
const CHUNK_SIZE = process.env.CHUNK_SIZE || 3
const MAX_RETRIES = process.env.MAX_RETRIES || 5

// build artifacts for the oracle contract so we can access it from here

const OracleJSON = require('./oracle/build/contracts/EthPriceOracle.json')
var pendingRequests = []


// return instance of oracle contract
async function getOracleContract (web3js) {
  //was set to Extdev network under utils/common.js
  const networkId = await web3js.eth.net.getId()
  return new web3js.eth.Contract(OracleJSON.abi, OracleJSON.networks[networkId].address)
}

// interacts with the Binance API
async function retrieveLatestEthPrice () {
  const resp = await axios({
    url: 'https://api.binance.com/api/v3/ticker/price',
    params: {
      symbol: 'ETHUSDT'
    },
    method: 'get'
  })
  return resp.data.price
}

// listens for events emitted from oracle contract
// specify a callback on what to do once you hear one of these events from the oracle contract
// in this case.. fire addRequestToQueue(event) on GetLatestEthPriceEvent
// ..and nothing really to be done on SetLatestEthPriceEvent(more about the caller function)

async function filterEvents (oracleContract, web3js) {
  oracleContract.events.GetLatestEthPriceEvent(async (err, event) => {
    if (err) {
      console.error('Error on event', err)
      return
    }
    await addRequestToQueue(event)
  })

  oracleContract.events.SetLatestEthPriceEvent(async (err, event) => {
    if (err) console.error('Error on event', err)
    // Do something
  })
}

// parse the event, pull the parameters you need for each request under
// "event.returnValues" object and push it into pendingRequests array

async function addRequestToQueue (event) {
  const callerAddress = event.returnValues.callerAddress
  const id = event.returnValues.id
  pendingRequests.push({ callerAddress, id })
}

// schedules processing of requests that are sitting in queue
// since JS is single-threaded, only process at most CHUNK_SIZE requests at a time
// to avoid blocking and not being able to take in more requests
// while 1) there are requests AND 2) processing requests is still below CHUNK_SIZE threshold
// pull out a pendingRequest and process it

async function processQueue (oracleContract, ownerAddress) {
  let processedRequests = 0
  while (pendingRequests.length > 0 && processedRequests < CHUNK_SIZE) {
    const req = pendingRequests.shift()
    await processRequest(oracleContract, ownerAddress, req.id, req.callerAddress)
    processedRequests++ // the while loop will stop once you hit CHUNK_SIZE
  }
}

async function processRequest (oracleContract, ownerAddress, id, callerAddress) {
  let retries = 0
  while (retries < MAX_RETRIES) {
    try {
      // retrieveLatestEthPrice() will talk to Binance API
      const ethPrice = await retrieveLatestEthPrice()
      // function called which in turn forwards to the oracle contract
      await setLatestEthPrice(oracleContract, callerAddress, ownerAddress, ethPrice, id)
      return
    } catch (error) {
      // if last try, try one last time and return out of the while loop
      if (retries === MAX_RETRIES - 1) {
        await setLatestEthPrice(oracleContract, callerAddress, ownerAddress, '0', id)
        return
      }
      // upon error, increment retry and go back to beginning (which will fire as long as retry < MAX_RETRIES)
      retries++
    }
  }
}

// parse the returned ethPrice from Binance API with BN.js library
// Number type in JS supports only 16 decimals vs. one eth is 10 ^ 18 wei
async function setLatestEthPrice (oracleContract, callerAddress, ownerAddress, ethPrice, id) {
  //Binance returns something like 196.87000
  ethPrice = ethPrice.replace('.', '')
  const multiplier = new BN(10**10, 10)
  const ethPriceInt = (new BN(parseInt(ethPrice), 10)).mul(multiplier)
  const idInt = new BN(parseInt(id))
  try {
    //we are the owner of the oracle contract.
    //the caller address came from the original request when we listened for "GetLatestEthPrice" events
    await oracleContract.methods.setLatestEthPrice(ethPriceInt.toString(), callerAddress, idInt.toString()).send({ from: ownerAddress })
  } catch (error) {
    console.log('Error encountered while calling setLatestEthPrice.')
    // Do some error handling
  }
}

//startup functions
async function init () {
  //connect to Extdev Testnet and pull out values needed by other functions
  //client is object the app uses to interact with Extdev testnet
  //instance of oracle contract (from web3js)
  //ownerAddress of the oracle contract (which you instantiated from this service).. 
  //so "this service" is the owner of the oracle contract
  const { ownerAddress, web3js, client } = common.loadAccount(PRIVATE_KEY_FILE_NAME)
  const oracleContract = await getOracleContract(web3js)
  //listen for events on the oracle contract
  filterEvents(oracleContract, web3js)
  return { oracleContract, ownerAddress, client }
}

// execute the service 

(async () => {
  const { oracleContract, ownerAddress, client } = await init()
  // way for user to shut down the oracle
  process.on( 'SIGINT', () => {
    console.log('Calling client.disconnect()')
    client.disconnect()
    process.exit( )
  })
  // process the Queue every SLEEP_INTERVAL seconds
  setInterval(async () => {
    await processQueue(oracleContract, ownerAddress)
  }, SLEEP_INTERVAL)
})()
