var Atem = require('dpclive-atem') // Load the atem module
var Config = require("./config");
var http = require('http');
var express = require('express');
var mongoose = require('mongoose');

var app = express();
const atem = new Atem();
var dgram = require('dgram');
var s = dgram.createSocket('udp4');


var len = 16;

var Prv1Me = new Array(len).fill(0);
var Prg1Me = [8];
var Prv2Me = [8];
var Prg2Me = []; // TMP1 - Arduino 2 - IP 178
var key2Me = []; // TMP1 - Arduino 2 - IP 178
var Prv3Me = [8];
var Prg3Me = [8];
var Prv4Me = [8];
var Prg4Me = [8];

var tmp1 = new Array(len).fill(0); 
var tmp2 = new Array(len).fill(0); 
var tmp3 = new Array(len).fill(0); 
var touchePrecedent = new Array(3).fill(0); 

const dbpath = "mongodb://localhost:27017/apps";
const mongo = mongoose.connect(dbpath,  {
    useUnifiedTopology: true,
    useNewUrlParser: true,
    });
mongo.then(() => { 
console.log('connected');
}).catch((err) => {
console.log('err', err);
});


////////////////////////////////
// Début - Appel des classes
////////////////////////////////
var Mappings = require('./models/Mappings');

var AtemClass = require('./class/Atem');
var ToolsClass = require('./class/Tools');
////////////////////////////////
// Fin - Appel des classes
////////////////////////////////


/////////////////////////
// Variable global
///////////////////
//var precedent = [];

// EJS
app.set('views', './views')
app.set('view engine', 'ejs')
app.use(express.static(__dirname + '/public'));


var server = http.createServer(app);
// Pass a http.Server instance to the listen method
var io = require('socket.io').listen(server);



// Register the index route of your app that returns the HTML file
   app.use('/',require('./routes/dashboard'));
   
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
	}
	 
}); 

atem.on('programBus', function(mE, source, Transition) {
	//const arr = new Uint8Array(2 * 8 + 1);
	console.log('program bus changed to', mE, 'source : ', source, 'Transition : ',Transition);
 
    //var configs = Config.getConfigSonyOneColor(mE, source);
    //var ip = '192.168.1.178';//.concat('.', configs[0]);
    var params = { me: mE, input: source }
    Mappings.findOne(params).then(mapping =>{
        if(mapping){
            if(mapping.tmp == 3){
                tmp3.fill(0,0,7);
                tmp3[(mapping.groupe*2)]=mapping.address;
                tmp3[(mapping.groupe*2)+1]=mapping.color;
                //console.log(mapping.ipArduino);
                console.table(tmp3);
                const buf1 = Buffer.from(tmp3, "hex");
                s.send(buf1, 8888, mapping.ipArduino); 
                //console.table(buf1);
            }            	
        }
    });

  





        /*arr[0] = 1;
       console.log("1 :" +configs[1]);
        arr[configs[1]] = dec2hexString(configs[2]); // valeur
		arr[2] = "0xFF"; 
		console.log(arr[1]);*/
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
		
		//const buf1 = Buffer.from(arr, "hex");
		//s.send(buf1, 8888, ip);	
});
////////////////////////////////////////
///
////////////////////////////////////////

////////////////////////////////////////
///
////////////////////////////////////////
s.on('message', function(msg, rinfo) {

    // Selection du TMP
    var selectTmp = parseInt(msg.slice(0, 1).toString());
    // Sélection de la bar
    var selectGroupe  = parseInt(msg.slice(1, 2).toString());
    // sélection de l'adresse
    var selectTouche = parseInt(msg.slice(2, 3).toString());
   
    if(selectTmp !== parseInt(touchePrecedent[0]) || selectGroupe !== parseInt(touchePrecedent[1]) || selectTouche !== parseInt(touchePrecedent[2])){
        console.log("tmp : " + selectTmp + " " + selectGroupe  + " " + selectTouche);
        var params = { tmp: selectTmp, groupe: selectGroupe, touche: selectTouche };
        Mappings.findOne(params).then(mapping =>{
           
            if(mapping){
                switch (mapping.barAtem) {
                    case 1:
                        atem.setProgram(mapping.input,mapping.me);
                        break;
                
                    default:
                        break;
                }
                //console.log("me : " +mapping.me +  "inputs : " + mapping.input)
            }
        });

        touchePrecedent[0] = parseInt(selectTmp);
        touchePrecedent[1] = parseInt(selectGroupe);
        touchePrecedent[2] = parseInt(selectTouche);
        //console.table(touchePrecedent);

    }
    
    /*moment = new ToolsClass();
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
    }*/

     
  });
s.bind(8080);
////////////////////////////////////////
///
////////////////////////////////////////
Config.chargerConfigAtem();
Config.chargerConfigSony();
atem.ip = Config.getConfigAtem().ip;
atem.connect();

// The server should start listening
server.listen(8000);