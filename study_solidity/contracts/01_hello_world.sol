/* 
    Hello world项目
*/
pragma solidity^0.4.17;

contract Greeter {  
    address creator;     
    string greeting;   

    function Greeter(string _greeting) public  
    {
        creator = msg.sender;
        greeting = _greeting;
    }

    function greet() public view returns (string)    //view代表的函数不能修改contract的参数，而且只能引用view和pure的函数，view用来取代constant      
    {
        return greeting;
    }
    
    function getBlockNumber() public view returns (uint) // 这个和greeting没有任何联系，只是来返回全局变量
    {												
        return block.number;
    }
    
    function setGreeting(string _newgreeting) public
    {
        greeting = _newgreeting;
    }
    
     /**********
     标准的自毁函数来重分配资金
     **********/
    
    function kill() public                   //这个函数只允许在发起者的情况下调用
    { 
        if (msg.sender == creator)  
            selfdestruct(creator);      
    }

}
