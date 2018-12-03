pragma solidity ^0.4.23;

contract HelloWorld {
    string message;

    function HelloWorld() public {
        message = "hello world";
    }

    function setMsg(string _message) public {
        message = _message;
    }

    function getMsg() public view returns(string) {
        return message;        
    }
}