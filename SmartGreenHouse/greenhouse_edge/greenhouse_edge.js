function sendData(content) {
  var options = {
    host: '', //da modificare ogni volta
    port: '80',
    path:'/api/data',
    method:'POST',
    headers: {
      "Content-Type":"application/json",
      "Content-Length":content.length
    }
  };
  console.log("sending " + content + "...");
  require("http").request(options, function(res)  {
    res.on('close', function(data) {
      console.log("OK.");
    });
    /*
    res.on('data', function(data) { 
      console.log("data: "+data);
    });*/
  }).end(content);
};

function doJob(){
  setInterval(function(){
    var value = (analogRead(A0)/1023.0)*100;
    sendData('{ "value": ' + value + ' }');
  },3000);
}

var wifi = require("Wifi");

wifi.connect("Telecom-30726981", {password:"XSP7roSDrIOHLSo57BbV1w7K"}, function(err){
  if (err==null){
    console.log("connected: ",wifi.getIP());
    doJob();
  } else {
    console.log("error - not connected.");
  }
});

