// This contract demonstrates a simple non-constant (transactional) function you can call from geth.
// increment() takes no parameters and merely increments the "iteration" value. 

pragma solidity^0.4.17;
contract Incrementer {

    address creator;
    uint iteration;

    function Incrementer() public 
    {
        creator = msg.sender; 
        iteration = 0;
    }

    function increment() public
    {
        iteration = iteration + 1;
    }
    
    function getIteration() public view returns (uint) 
    {
        return iteration;
    }
    
    /**********
     Standard kill() function to recover funds 
    **********/
    
    function kill() public
    { 
        if (msg.sender == creator)
            selfdestruct(creator);  // kills this contract and sends remaining funds back to creator
    }
    
}