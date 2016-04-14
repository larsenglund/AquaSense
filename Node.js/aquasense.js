var moment = require('moment');
var net = require('net');
var log4js = require('log4js'); 
var http = require('http');
fs = require('fs');

var latest_aquasense_version = 'aquasense_1.0.1';

const LOG_SERVER_PORT     = 5416; 
const UPDATE_SERVER_PORT  = 5417; 
const WEB_SERVER_PORT     = 5418; 

log4js.loadAppender('file');
log4js.addAppender(log4js.appenders.file('logs/aquasense.log'), 'aquasense');
var logger = log4js.getLogger('aquasense');

logger.info("AquaSense server");
logger.info('Node version: ' + process.version);


/*
Example update headers sent by ESP
{ host: 'englund.asuscomm.com',
  'user-agent': 'ESP8266-http-Update',
  connection: 'close',
  'x-esp8266-sta-mac': '5C:CF:7F:81:C7:6D',
  'x-esp8266-ap-mac': '5E:CF:7F:81:C7:6D',
  'x-esp8266-free-space': '741376',
  'x-esp8266-sketch-size': '303492',
  'x-esp8266-chip-size': '4194304',
  'x-esp8266-sdk-version': '1.5.1(e67da894)',
  'x-esp8266-mode': 'sketch',
  'x-esp8266-version': '1.0.0' }
*/

//var clients = {
//  '5C:CF:7F:81:C7:6D': '1.0.0'
//};

function handleUpdateRequest(req, res){
  logger.info("Update new request from %s", req.connection.remoteAddress)
  logger.info(req.headers);
  logger.info(req.headers['user-agent']);
  if (req.headers['user-agent'] != 'ESP8266-http-Update') {
    res.writeHead(403, {"Content-Type": "text/plain"});
    res.write("403 Forbidden\n");
    res.end("only for ESP8266 updater!\n");
  }
  else {
    if (req.headers['x-esp8266-version'] != latest_aquasense_version) {
      fs.readFile(latest_aquasense_version + '.bin', 'binary', function(err, file) {
        if(err) {        
          res.writeHead(500, {"Content-Type": "text/plain"});
          res.end(err + "\n");
          return;
        }
        /*  
        From PHP OTA example
        header($_SERVER["SERVER_PROTOCOL"].' 200 OK', true, 200);
        header('Content-Type: application/octet-stream', true);
        header('Content-Disposition: attachment; filename='.basename($path));
        header('Content-Length: '.filesize($path), true);
        header('x-MD5: '.md5_file($path), true);
        readfile($path);
        */
        var stats = fs.statSync(latest_aquasense_version + '.bin');
        var fileSizeInBytes = stats['size'];
        res.writeHead(200, {'Content-Type': 'application/octet-stream', 'Content-Length': fileSizeInBytes});
        res.write(file, 'binary');
        res.end();
      });
    }
    else {
      res.writeHead(304, {"Content-Type": "text/plain"});
      res.end('304 Not Modified');
    }
  }
  // header($_SERVER["SERVER_PROTOCOL"].' 500 no version for ESP MAC', true, 500);
}

var updateserver = http.createServer(handleUpdateRequest);

//Lets start our server
updateserver.listen(UPDATE_SERVER_PORT, function(){
  logger.info('Update server listening to %j', updateserver.address());
});



var logserver = net.createServer();  
logserver.on('connection', handleLogConnection);

logserver.listen(LOG_SERVER_PORT, function() {  
  logger.info('Log server listening to %j', logserver.address());
});

var start = new Date();
function handleLogConnection(conn) {  
  var remoteAddress = conn.remoteAddress + ':' + conn.remotePort;
  logger.info('Log new client from %s', remoteAddress);

  conn.on('data', onConnData);
  conn.once('close', onConnClose);
  conn.on('error', onConnError);

  function onConnData(d) {
    // Using Comviq kontant we can send about 2700 bytes every 5 minutes for 100kr/yr
    logger.info('Connection data to log server from %s: %s', remoteAddress, d);
    var end = new Date() - start;
    logger.info("Time since last log server data: %d minutes", end/(1000*60));
    start = new Date();
  }

  function onConnClose() {
    logger.info('Log connection %s closed', remoteAddress);
  }

  function onConnError(err) {
    logger.info('Log connection %s error: %s', remoteAddress, err.message);
  }
}
