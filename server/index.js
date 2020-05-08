var Atem = require('dpclive-atem') // Load the atem module
var Config = require("./config");
var http = require('http');
var express = require('express');
var app = express();
const atem = new Atem();
var dgram = require('dgram');
var s = dgram.createSocket('udp4');
var programM2 = [8,8];

////////////////////////////////
// Début - Appel des classes
////////////////////////////////

var AtemClass = require('./class/Atem');
var ToolsClass = require('./class/Tools');
////////////////////////////////
// Fin - Appel des classes
////////////////////////////////


/////////////////////////
// Variable global
///////////////////
var precedent = [];

// EJS
app.set('views', './views')
app.set('view engine', 'ejs')
app.use(express.static(__dirname + '/public'));


var server = http.createServer(app);
// Pass a http.Server instance to the listen method
var io = require('socket.io').listen(server);



// Register the index route of your app that returns the HTML file
app.get('/', (req, res) => {
    res.render('index')
   })

// Expose the node_modules folder as static resources (to access socket.io.js in the browser)
app.use('/static', express.static('node_modules'));

// Handle connection
io.on('connection', function (socket) {
    console.log("Client connecter");
    // Send news on the socket
    //socket.emit('news', news);

    /*socket.on('my other event', function (data) {
        console.log(data);
    });*/
});

////////////////////////////////////////
///
////////////////////////////////////////

atem.on('connectionStateChange', function(state) {
    
    var AtemObj = new AtemClass(state.id, Config.getConfigAtem().ip, state.description);
    io.emit('statusAtem', AtemObj.getJsonAtem());

	if(state.id == 2){
		timerConnect = setTimeout(function () { 
			Config.chargerConfigAtem();
			atem.ip = Config.getConfigAtem().ip;
            }, 5000);
            
            
	}else if(state.id==1){
		
	}else if(state.id=4){
        clearTimeout(timerConnect);
	}else{
	}
	 
}); 

atem.on('programBus', function(mE, source, Transition) {
	const arr = new Uint8Array(2 * 8 + 1);
	console.log('program bus changed to', mE, 'source : ', source, 'Transition : ',Transition);
    
    var configs = Config.getConfigSonyOneColor(mE, source);
    var ip = '192.168.1.178';//.concat('.', configs[0]);

        arr[0] = 1;
       console.log("1 :" +configs[1]);
        arr[configs[1]] = dec2hexString(configs[2]); // valeur
		arr[2] = "0xFF"; 
		console.log(arr[1]);
		/*if(source ==0){
            	// Ligne 1
		arr[1] = 0x01; // valeur
		//arr[2] = 0xFF; // couleur
        }/*else if(source == 1){
            arr[1] = 0x02; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 2){
            arr[1] = 0x04; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 3){
            arr[1] = 0x08; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 4){
            arr[1] = 0x10; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 5){
            arr[1] = 0x20; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 6){
            arr[1] = 0x40; // valeur
            arr[2] = 0xFF; // couleur
        }else if(source == 7){
            arr[1] = 0x80; // valeur
            arr[2] = 0xFF; // couleur
        }*/
	
		
		// Ligne 2
		/*arr[3] = 0x00;
		arr[4] = 0x00;*/
		
		/*arr[5] = 0x0;
		arr[6] = 0xAA;
		
		arr[7] = 0x0;
		arr[8] = 0xFF;
		
		arr[9] = 0x0;
		arr[10] = 0xFF;
		
		arr[11] = 0x0;
		arr[12] = 0xFF;
		
		arr[13] = 0x0;
		arr[14] = 0xFF;
		
		arr[15] = 0x0;
		arr[16] = 0xFF;*/
		
		const buf1 = Buffer.from(arr, "hex");
		s.send(buf1, 8888, ip);	
});
////////////////////////////////////////
///
////////////////////////////////////////

////////////////////////////////////////
///
////////////////////////////////////////
s.on('message', function(msg, rinfo) {
    moment = new ToolsClass();
    var command = [];
    // récupération des informations de communication (ip, port)
    command[0] = rinfo;
    // Selection du TMP (1 ou 2)
    command[1] = msg.slice(0, 1).toString();
    // Selection du groupe de bouton
    command[2] =  msg.slice(1, 2).toString();
    // numero de la touche de 0 à 7
    command[3] =  msg.slice(2, 3).toString();


        console.log(moment.getMoment() + 
        ' : TMP ' + command[1] +
        ' : groupe ' + command[2] +
        ' : touche numéro ' + command[3] +
        ', ip :' + command[0].address);

        var val = Config.getConfigSonyOneBtn(command[0].address.substr(-3), 
        command[1], 
        command[2],
        command[3])
        
    if(myObject.hasOwnProperty(val[0])){
        switch (val[0]) {
            case 0:
                atem.setPreview(val[2],val[1]);
                break;
            case 1:
                atem.setProgram(val[2],val[1]);
                break;
            default:
                break;
        }
    }

     
  });
s.bind(8080);
////////////////////////////////////////
///
////////////////////////////////////////
Config.chargerConfigAtem();
Config.chargerConfigSony();
atem.ip = Config.getConfigAtem().ip;
atem.connect();

function dec2hexString(dec) {
    return '0x' + (dec+0x10000).toString(16).substr(-4).toUpperCase();
 }

// The server should start listening
server.listen(8000);