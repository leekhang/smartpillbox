"use strict";

let serial; // variable to hold an instance of the serialport library.
let portName = '/dev/tty.usbmodem0E2163341'; // rename to the name of your port.
let portName1 = '/dev/tty.usbmodem0E22C91C1'; // rename to the name of your port.
let str = "";

function serialInit() {
	serial = new p5.SerialPort();       // make a new instance of the serialport library
	console.log(serial.list());
	serial.on('list', printList);       // set a callback function for the serialport list event
	serial.on('connected', serverConnected); // callback for connecting to the server
	serial.on('open', portOpen);        // callback for the port opening
	serial.on('data', serialEvent);     // callback for when new data arrives
	serial.on('error', serialError);    // callback for errors
	serial.on('close', portClose);      // callback for the port closing
	
	serial.list();                      // list the serial ports
	serial.open(portName);              // open a serial port
}

// Checks the serial for data from the TM4C, use for debugging only.
function serialEvent() {
	if (serial.available()) { // if the info is being sent through the serial.
		let value = parseInt(serial.read()); // retrieve data from seriald as an int.
		if (value != 10 || value != 13) str += String.fromCharCode(value);
		if (value == 0) {
			console.log(str);
			str = "";
		}
  }
}

// console logging functions for serial protocols 
const printList = (portList) => portList.forEach((element, index) => print("["+index+"] "+element));
const serverConnected = () => print('connected to server.');
const portOpen = () => print('the serial port opened.');
const serialError = (err) => print('Something went wrong with the serial port. ' + err);
const portClose = () => print('The serial port closed.');