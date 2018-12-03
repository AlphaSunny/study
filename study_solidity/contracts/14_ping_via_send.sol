/***
 *     _    _  ___  ______ _   _ _____ _   _ _____ 
 *    | |  | |/ _ \ | ___ \ \ | |_   _| \ | |  __ \
 *    | |  | / /_\ \| |_/ /  \| | | | |  \| | |  \/
 *    | |/\| |  _  ||    /| . ` | | | | . ` | | __ 
 *    \  /\  / | | || |\ \| |\  |_| |_| |\  | |_\ \
 *     \/  \/\_| |_/\_| \_\_| \_/\___/\_| \_/\____/
 *                                                 
 *   This contract DOES NOT WORK at the moment. 9/22/2015                                     
 */

// 1. Deploy Pong .
// 2. Deploy Ping, giving it the address of Pong.
// 3. Call Ping.touchPong() using a <pongaddress>.send()
// 4. ... which does... something ...
pragma solidity^0.4.17;
contract Ping {

	address pvr;
    address creator;
    int8 sendval = -2; // -2 == initialized, -1 == error, 0 == pong returned false. 1 == pong returned true 

	/*********
 	 Step 2: Deploy Ping, giving it the address of Pong.
 	 *********/
    function Ping(address _pongAddress) public 
    {
        creator = msg.sender; 	
        pvr = _pongAddress;
    }

	/*********
     Step 3: Touch pong with a 3,000,000 wei "send" call and see what happens. 
     *********/

	function send3MilWeiToPong() public payable
	{
		sendval = -1;  // at least we reached this function
		bool retval = false;
		retval = pvr.send(3000000); // send 3,000,000 wei to pong // trying to determine what exactly happens here.
		if(retval)
			sendval = 1; // success!
		else 
			sendval = 0; // failure!
	}	
  
// -----------------------------------------------------------------------------------------------------------------	
	
	function getBalance() public view returns (uint)
	{
		return this.balance;
	}
	

	function getSendVal() public view returns (int8)
	{
		return sendval;
	}
	
	/*********
     Functions to get and set pongAddress just in case
     *********/
    
    function setPongAddress(address _pongAddress) public
	{
		pvr = _pongAddress;
	}
	
	function getPongAddress() public view returns (address) 
	{
		return pvr;
	}
    
    /****
	 For double-checking this contract's address
	 ****/
	function getAddress() public view returns (address)
	{
		return this;
	}
    
    /*********
     Standard kill() function to recover funds 
     *********/
    
    function kill() public 
    { 
        if (msg.sender == creator)
            selfdestruct(creator);  // kills this contract and sends remaining funds back to creator
    }
}
