// Client interacts with the oracle.. mainly through the caller contract

const common = require('./utils/common.js')
const SLEEP_INTERVAL = process.env.SLEEP_INTERVAL || 2000
const PRIVATE_KEY_FILE_NAME = process.env.PRIVATE_KEY_FILE || './caller/caller_private_key'
const CallerJSON = require('./caller/build/contracts/CallerContract.json')
const OracleJSON = require('./oracle/build/contracts/EthPriceOracle.json')


// instantiate caller contract instance to interact with
async function getCallerContract (web3js) {
  const networkId = await web3js.eth.net.getId()
  return new web3js.eth.Contract(CallerJSON.abi, CallerJSON.networks[networkId].address)
}

// listen for price update and received new request events
async function filterEvents (callerContract) {
  callerContract.events.PriceUpdatedEvent({ filter: { } }, async (err, event) => {
    if (err) console.error('Error on event', err)
    console.log('* New PriceUpdated event. ethPrice: ' + event.returnValues.ethPrice)
  })
  callerContract.events.ReceivedNewRequestIdEvent({ filter: { } }, async (err, event) => {
    if (err) console.error('Error on event', err)
  })
}

async function init () {
  const { ownerAddress, web3js, client } = common.loadAccount(PRIVATE_KEY_FILE_NAME)
  //instantiate the caller contract
  const callerContract = await getCallerContract(web3js)
  //listen to events on the contract
  filterEvents(callerContract)
  // pull values needed elsewhere
  return { callerContract, ownerAddress, client, web3js }
}

(async () => {
  const { callerContract, ownerAddress, client, web3js } = await init()
  // gracefully exit
  process.on( 'SIGINT', () => {
    console.log('Calling client.disconnect()')
    client.disconnect();
    process.exit( );
  })
  const networkId = await web3js.eth.net.getId()

  //set the oracle instance address from us, the owner
  const oracleAddress =  OracleJSON.networks[networkId].address
  await callerContract.methods.setOracleInstanceAddress(oracleAddress).send({ from: ownerAddress })

  //update ethereum price every SLEEP_INTERVAL seconds
  setInterval( async () => {
    await callerContract.methods.updateEthPrice().send({ from: ownerAddress })
  }, SLEEP_INTERVAL);
})()
