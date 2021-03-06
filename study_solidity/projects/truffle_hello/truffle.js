/*
 * NB: since truffle-hdwallet-provider 0.0.5 you must wrap HDWallet providers in a 
 * function when declaring them. Failure to do so will cause commands to hang. ex:
 * ```
 * mainnet: {
 *     provider: function() { 
 *       return new HDWalletProvider(mnemonic, 'https://mainnet.infura.io/<infura-key>') 
 *     },
 *     network_id: '1',
 *     gas: 4500000,
 *     gasPrice: 10000000000,
 *   },
 */

 require('dotenv').config();
 const HDWalletProvider = require('truffle-hdwallet-provider');

 

module.exports = {
  // See <http://truffleframework.com/docs/advanced/configuration>
  // to customize your Truffle configuration!
  networks: {
    rinkeby: {
      provider: function() {
        return new HDWalletProvider(
          process.env.MNEMONIC,
          `https://rinkeby.infura.io/${process.env.INFURA_API_KEY}`
        )
      },
      gasPrice:25000000000,
      network_id:4
    },
    ganache: {
      host: "localhost",
      port: "7545",
      network_id:"*"
    }
  },

  solc: {
    optimizer: {
      enabled: true,
      runs: 200
    }
  }

};
