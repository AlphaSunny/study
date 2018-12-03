/* 
	Another very basic contract. It demonstrates that a contract can retrieve and store the 
	balance of its creator address. Note that the creatorbalance value captured in the constructor is a snapshot in time.
	Later on, creator.balance will reflect whatever it is now.
*/
pragma solidity^0.4.17;
contract creatorBalanceChecker {

    address creator;
    uint creatorbalance; 		//=显示的以wei单位

    function creatorBalanceChecker() public 
    {
        creator = msg.sender; 								 // msg 是一个全局变量
        creatorbalance = creator.balance;
    }

	function getContractAddress() public view returns (address) 
	{
		return this;
	}

	function getCreatorBalance() public view returns (uint)     // 返回contract创造时的余额
	{
        return creatorbalance;
    }
    
    function getCreatorDotBalance() public view returns (uint)  // 会返回实时情况下的余额
    {
        return creator.balance;
    }
    
    
    function kill() public
    { 
        if (msg.sender == creator)
            selfdestruct(creator); 
    }
        
}