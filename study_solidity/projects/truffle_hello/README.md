mkdir GreetingsTruffle
cd GreetingsTruffle

truffle version

#初始化truffle
truffle init

truffle develop

# open a new terminal
cd GreetingsTruffle
truffle develop --log

#发不到ganache
migrate --compile-all --reset

web3.eth.accounts

Greetings.deployed().then(function(instance){app = instance;})

app

app.getGreetings()

app.setGreetings("Hello ChainSkills!", {from: web3.eth.accounts[0]})

app.getGreetings()

.exit

#修改truffle.js
migrate --compile-all --reset --network ganache

truffle console --network ganache

.exit

Greetings.address

Greetings.deployed().then(function(instance){app = instance;})

app.getGreetings()

app.setGreetings("Hello ChainSkills!", {from: web3.eth.accounts[0]})

app.getGreetings()

.exit