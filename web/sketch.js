"use strict";

const ABS_MAX = 4; // Maximum number of to-dos that you can create.
let button, nameInput, timeInput; // button and input are used as pointers to the text field and submit button 
let upper; // upper keeps track of the number of todos in the array.
let medArr = [], todoDisp = []; // medArr stores the strings of todos, todoDisp stores the html <li> objects created

function setup() {
	// serialInit(); // Serial connection setup
	
	// Create Name Input Field
	nameInput = createInput().id("textfield").parent("form"); // create <input> HTML element
	nameInput.attribute("placeholder", "New medicine"); // set placeholder text for button
	nameInput.attribute("onfocus", "this.placeholder = ''"); // set onfocus attr for button
	nameInput.attribute("onblur", "this.placeholder = 'New medicine'"); // set onblur attr for button

	// Create Time Input Field
	timeInput = createInput("","time").id("timefield").parent("form"); // create <input> HTML element

	// Create Button
	button = createButton("+").id("addbutton").parent("form"); // create <button> HTML element
	button.mousePressed(createNewItem); // set an event listener for the button
	
	upper = 0; // set the initial number of todos to 0.
}

// Creates a new todo item based on the input field only if:
// item is not an empty string and the maximum amount of todos hasn't been reached
function createNewItem() {
	let name = nameInput.value();
	let time = timeInput.value();
  if ((name != "") && (name != " ") && (medArr.length <= ABS_MAX)) { 
		medArr[upper] = {name, time}; // append new item into array
		// serial.write(stringifyArray()); // send the new array to TM4C
		medArr.sort((a,b) => (a.time > b.time) ? 1 : -1);
		upper++; // increment the number of items.
		displayToDos(); // display the new array of items.
	}
	// refresh input field and char count on webpage
	nameInput.value(""); timeInput.value("");
	document.getElementById("char-count").innerHTML = "16 characters remaining.";
}

function deleteItem() {
	let index = parseInt(event.path[1].id.charAt(10)); // figure out which button is pressed
	medArr.splice(index, 1); // remove item from array.
	(upper > 0) ? upper-- : upper = 0; // decrement upper.
	displayToDos(); // display the new todos
}

// Removes all of the <li> DOM elements created previously and 
// recreates new <li> DOM elements based on updated array.
function displayToDos() {
	todoDisp.forEach(obj => obj.remove()); // remove all <li> elements on display.
	for (let i = 0; i < upper; i++) {
		todoDisp[i] = createDiv().addClass("listitem").id("item"+i).parent("divlist"); // create list item div
		createDiv().addClass("name_element").id("name_element"+i).parent("item"+i); // create div box for name
		createElement("p", " " + (i + 1) + ". " + medArr[i].name).addClass("p_name").parent("name_element"+i); // create p for name
		createDiv().addClass("time_element").id("time_element"+i).parent("item"+i); // create div box for time
		createElement("p", timeConvert(medArr[i].time)).addClass("p_time").parent("time_element"+i); // create p for time
		createDiv().addClass("del_element").id("del_element"+i).parent("item"+i); // create div box for delete btn
		let delButton = createButton("").addClass("del_button").id("del_button"+i).parent("del_element"+i); // create delete button
		delButton.mousePressed(deleteItem); // set an event listener for delete btn
		createElement("span", "×").addClass("del_content").parent("del_button"+i); // create span text for del btn
	}
	console.log("mapped: " + todoDisp);
}

// Function to convert 
function timeConvert(time) {
	time = time.split(":");
	let timeOut = parseInt(time[0]);
	let pmFlag = timeOut >= 12;
	if (pmFlag && timeOut != 12) timeOut -= 12;	
	if (timeOut > 0 && timeOut < 10) {
		timeOut = "0" + timeOut + ":" + time[1];
	} else {
		if (timeOut == 0) timeOut += 12;
		timeOut += ":" + time[1];
	}
	timeOut += (pmFlag) ? " PM" : " AM"; 
	return timeOut;
}

// Sets Enter key as an input method.
function keyPressed() {
	if (keyCode == 13) createNewItem(); // 13 is the Enter key.
}

// Updates the char count above the text field and restrict the user from inputting more than 16 chars.
function keyReleased() {
	let count = 16 - nameInput.value().length; // set count to be the remaining number of chars available.
	if (count < 0) { // if there are no more available chars
		nameInput.value(input.value().substring(0,16)); // restrict the string in the text field to 16.
		count = 0; // keep count at 0.
	}
	// update char count on webpage
	document.getElementById("char-count").innerHTML = count + " characters remaining.";
}

// Creates a string of all of the medicine items from the array.
function stringifyArray() {
	let output = "@"; // create a string with a start byte "@"".
	if (medArr.length > 0) { // if there's sth in the array
		medArr.forEach((item) => { // always 37 bytes per item
			output += item.name.padEnd(16, " "); // append name of medicine (always 16 bytes)
			output += timeConvert(item.time); // add time input for medicines (always 8 bytes)
			output += timeRemaining(item.time).padStart(13, "0"); // add counter for TM4C (always 13 bytes)
		});
	}
	output += "@"; //
	return output; // return the string
}

// Function determines how much longer the TM4C needs to count to before the user has to take a medicine.
// Max value: 1382400000000 (= 60 * 60 * 24 * 16,000,000)
function timeRemaining(time) { 
	let today = new Date(), hr = parseInt(time[0]), output;
	time = time.split(":"); // split between hours (index 0) and minutes (index 1)
	hr = (today.getHours() > hr) ? today.getHours() - hr : 24 + (hr - today.getHours()); // calc no. of hrs remaining (in hr).
	output = (60 - today.getSeconds()); // calculate no. of sec remaining.
	output += 60 * (59 - parseInt(time[1])); // add no. of mins remaining (in sec).
	output += hr * 60 * 60; // add the no. of hours remaining (in sec).
	return output;
}