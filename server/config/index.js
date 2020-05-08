var fs = require('fs');
// These variables will stay in the local scope of this module (in this case, person.js)
var ip;
var dataSony;

var cheminFichierAtem = "config/atem.json";
var cheminFichierSony = "config/sony.json";


// Make sure your argument name doesn't conflict with variables set above
exports.setIp = function (fip) {
    this.ip = fip;
};


// You're returning an object with property values set above
exports.getConfigAtem = function () {
    return {
        ip: this.ip  
    };
};

exports.getConfigSony = function () {
    return {
        dataSony: this.dataSony  
    };
};

exports.getConfigSonyOneBtn = function (ip,  tmp, group, bouton) {
    var btn = group.concat('', bouton);
   return this.dataSony.commands.btn1[ip][tmp][btn];
};

exports.getConfigSonyOneColor = function (me, bouton) {
    var btn = me.concat('', bouton);
   return this.dataSony.commands["color"][btn];
};


exports.chargerConfigAtem = function () {
	var datas = readFichierJson(cheminFichierAtem);
	this.setIp(("ip" in datas & datas.ip !== undefined)?datas.ip:'0.0.0.0');
};

exports.chargerConfigSony = function () {
	this.dataSony = readFichierJson(cheminFichierSony);
};





var readFichierJson = function(fichier){
	let dataFichier = fs.readFileSync(fichier);
    return JSON.parse(dataFichier);

}