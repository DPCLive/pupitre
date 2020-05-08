const moment = require('moment');

function Tools() {
  }

  Tools.prototype.getMoment = function() {
    moment.locale('FR');
    let now = moment();

      return now.get('date') + " " + this.setMonthLetter(now.get('month')) + " " + now.get('year') + " " +
      now.get('hour') + ":" + now.get('minute') + ":" + now.get('second') + "." + now.get('millisecond');
  };

    // Sets the Ip
  // 
  Tools.prototype.setMonthLetter = function(month) {
    var months = ['Janvier', 'Février','Mars', 'Avril', 'Mai', 'Juin', 'Juillet', 'Août', 'Septembre', 'Octobre', 'Novembre', 'Décembre'];  
    return months[month];
};


// get Ip
// 

  module.exports = Tools;