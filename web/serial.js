"use strict";

let serial; // variable to hold an instance of the serialport library.
let portName = '/dev/tty.usbmodem0E2163341'; // rename to the name of your port.
let options = { baudrate: 9600 , parity: "N", stopbits: 1};
let str = "";

function serialInit() {
	// let serialserver = require('./js/p5.serialserver');
	// serialserver.start(8081);
	serial = new p5.SerialPort();       // make a new instance of the serialport library
	console.log(serial.list());
	serial.on('list', printList);       // set a callback function for the serialport list event
	serial.on('connected', serverConnected); // callback for connecting to the server
	serial.on('open', portOpen);        // callback for the port opening
	serial.on('data', serialEvent);     // callback for when new data arrives
	serial.on('error', serialError);    // callback for errors
	serial.on('close', portClose);      // callback for the port closing
	
	serial.list();                      // list the serial ports
	serial.open(portName, options);              // open a serial port
	// Serial(parent, portName, baudRate, parity, dataBits, stopBits)
}

// Checks the serial for data from the TM4C.
function serialEvent() {
	if (serial.available()) { // if the info is being sent through the serial.
		let value = parseInt(serial.read()); // retrieve data from seriald as an int.
		if (value != 10 || value != 13) str += String.fromCharCode(value);
		if (value == 0) {
			console.log(str);
			str = "";
		}

		// if (value == 1 || value >= upper + 2) { // if the value is 1 or greater than the no. of todos in the webpage 
		// 	serial.write(stringifyArray()); // write array to arduino
		// } else if (value > 1) { // if value is greater than 1 (a todo item is completed)
		// 	value -= 2; // change the value back to an index
		// 	if (value < upper - 1) { // if index is not at the end of the array
		// 		for (let i = value; i < upper; i++) { // shift each element to the left.
		// 			medArr[i] = medArr[i+1]; 
		// 		}
		// 	}
		// 	medArr.pop(); // pop out the last element (which is undefined).
		// 	(upper > 0) ? upper-- : upper = 0; // decrement upper.
		// 	displayToDos(); // display the new todos
		// }
  }
}

// console logging functions for serial protocols 
const printList = (portList) => portList.forEach((element, index) => print("["+index+"] "+element));
const serverConnected = () => print('connected to server.');
const portOpen = () => print('the serial port opened.');
const serialError = (err) => print('Something went wrong with the serial port. ' + err);
const portClose = () => print('The serial port closed.');