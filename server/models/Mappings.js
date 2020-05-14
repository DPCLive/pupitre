var moogoose = require('mongoose');

var mappingsSchema = new moogoose.Schema({
    me:Number,
    barAtem:Number,
    input: Number,
    groupe: Number,
    ipArduino: String,
    tmp: Number,
    address: Number,
    color: Number,
    touche: Number

});

var Mappings = moogoose.model('mappings', mappingsSchema);

module.exports = Mappings;