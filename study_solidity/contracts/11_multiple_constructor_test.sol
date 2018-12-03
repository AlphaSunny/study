// Just testing to see if you can have multiple constructors. Nope!

pragma solidity^0.4.17;

contract MultipleConstructorTest {

    address creator;
    bool first = false;
    bool second = false;

    function MultipleConstructorTest() public 
    {
        creator = msg.sender; 								
        first = true;
    }
  
// Having two constructors with same number of arguments (zero, in this case) doesn't work. Won't compile.    
//    function MultipleConstructorTest() private 
//    {
//        second = true; 								
//    }  
  
// Merely setting the second to private doesn't work. Won't compile.    
//    function MultipleConstructorTest() private 
//    {
//        second = true; 								
//    }
	
// Returning a value won't do it, either. Won't compile.	
//    function MultipleConstructorTest() returns (bool) 
//    {
//        second = true;
//    }	

// Adding a parameter doesn't work. Won't compile.
//    function MultipleConstructorTest(bool irrelevantvalue) 
//    {
//        second = true;
//    }
	
	function getFirst() public view returns (bool) 
	{
		return first;
	}
	
	function getSecond() public view returns (bool)
	{
		return second;
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
