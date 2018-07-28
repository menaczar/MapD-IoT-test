const express = require('express')
const app = express()
const fs = require('fs')
var timestamp = require('time-stamp');
var port=3000

app.post('/log',function(request,response){
  var room=request.query.room;
  var temperature=request.query.temp;
  var humidity = request.query.humidity;
  var log = "at time: "+timestamp('YYYY-MM-DD HH:mm:ss')+ " room:" + room +", temperature was "+temperature+" and humidity was " +humidity;
  if(!isNaN(temperature) && !isNaN(humidity)){ //make sure valid reading recieved 
  console.log(log); 
  var csvLine = timestamp('YYYY-MM-DD HH:mm:ss') + ',' + room + ',' + temperature + ',' + humidity + '\n';
  fs.appendFile('log.csv', csvLine, function (err) {
    if (err) throw err;
  })}
  response.end("Logged: " + log);
});

app.listen(port, () => console.log('Server is listening on port ' + port))