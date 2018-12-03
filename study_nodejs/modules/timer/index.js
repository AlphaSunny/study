const util = require('util');
const setImmediatePromise = util.promisify(setImmediate);

/**
 * Created by Administrator on 2016/3/11.
 */
function myfunc(Interval){
    console.log("myfunc "+Interval);
   }
y = "yang";
setInterval(()=> {
    console.log(y)
},1000);
/*
function stopInterval(){
    clearTimeout(myInterval);
    //myInterval.unref();
}
   setTimeout(stopInterval,5000);
   */