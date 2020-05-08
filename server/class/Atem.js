
//  This is a Constructor function taking age and passport 
//  as the paramaters
function Atem(status, ip, message) {
    this.status = status;
    this.ip = ip;
    this.message = message;
  }
  // Sets the status
  // 
  Atem.prototype.setStatus = function(status) {
      this.status = status;
  };
  // get status
  // 
  Atem.prototype.getStatus = function() {
      return this.status;
  };

    // Sets the Ip
  // 
  Atem.prototype.setIp = function(ip) {
    this.ip = ip;
};
// get Ip
// 
Atem.prototype.getIp= function() {
    return this.ip;
};

   // Sets the status
  // 
  Atem.prototype.setMessage = function(message) {
    this.message = message;
};
// get status
// 
Atem.prototype.getMessage = function() {
    return this.message;
};


Atem.prototype.getJsonAtem = function() {

    let json = {};
            json.status = this.status;
            json.ip = this.ip;
            json.message = this.message;
            
    return JSON.stringify(json);
};
  module.exports = Atem;