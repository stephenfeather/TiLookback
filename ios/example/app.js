// This is a test harness for your module
// You should do something interesting in this harness 
// to test out the module and to provide instructions 
// to users on how to use it by example.
Ti.App.Properties.setString('LookbackAppToken',"your_app_token");

var Lookback = require('com.featherdirect.lookback');
Ti.API.info("module is => " + Lookback);

console.log(Lookback.shakeToRecord);

// open a single window
var win = Ti.UI.createWindow({
	backgroundColor:'white', layout: "vertical"
});
var enabled = 0, paused = 0, shakeToRecord = 0;

var label = Ti.UI.createLabel({height: 50, width: 300, top: 60, borderWidth: 1, borderColor: "#ababab"});
var isEnabledButton = Ti.UI.createButton({title: "isEnabled", borderWidth: 1, borderColor: "#ababab", top: 10, height: 45, width: 300});
isEnabledButton.addEventListener('click', function(e){
	label.text = 'isEnabled: '+Lookback.enabled;

});

var enableShakeToRecordButton = Ti.UI.createButton({title: "enable shakeToRecord", borderWidth: 1, borderColor: "#ababab", top: 10, height: 45, width: 300});
enableShakeToRecordButton.addEventListener('click', function(e){
	
	label.text = 'shakeToRecord: '+Lookback.enableShakeToRecord();

});

var disableShakeToRecordButton = Ti.UI.createButton({title: "disable shakeToRecord", borderWidth: 1, borderColor: "#ababab", top: 10, height: 45, width: 300});
disableShakeToRecordButton.addEventListener('click', function(e){
	
	label.text = 'shakeToRecord: '+Lookback.disableShakeToRecord();

});

var userIdentifierButton = Ti.UI.createButton({title: "set userIdentifier", borderWidth: 1, borderColor: "#ababab", top: 10, height: 45, width: 300});
userIdentifierButton.addEventListener('click', function(e){
	label.text = 'userIdentifier: '+Lookback.setUserIdentifier('Stephen');

});

win.add(label);
win.add(isEnabledButton);
win.add(enableShakeToRecordButton);
win.add(disableShakeToRecordButton);
win.add(userIdentifierButton);
win.open();

// TODO: write your module tests here

