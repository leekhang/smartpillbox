"use strict";

const ABS_MAX = 3; // Maximum number of Meds that you can create.
let button, nameInput, timeInput; // button and input are used as pointers to the text field and submit button 
let upper; // upper keeps track of the number of todos in the array.
let avail = [], medArr = [], medDisp = []; // medArr stores the strings of todos, medDisp stores the html <li> objects created

function setup() {
	serialInit(); // Serial connection setup
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
	avail.push(0, 1, 2);
	upper = 0; // set the initial number of todos to 0.
}

// Creates a new todo item based on the input field only if:
// item is not an empty string and the maximum amount of todos hasn't been reached
function createNewItem() {
	let name = nameInput.value(); // get the name from the input field
	let time = timeInput.value(); // get the time from the input field
  if ((name != "") && (name != " ") && (medArr.length <= ABS_MAX)) { 
		let index = avail[0]; // get the first available index
		avail.shift(); // remove the first available index by shifting leftwards.
		medArr[index] = {name, time}; // append new item into array
		serial.write(stringifyMed(index)); // send the new array to TM4C
		upper++; // increment the number of items.
		displayToDos(); // display the new array of items.
	}
	// refresh input field and char count on webpage
	nameInput.value(""); timeInput.value("");
	document.getElementById("char-count").innerHTML = "14 characters remaining.";
}

function deleteItem() {
	let index = parseInt(event.path[1].id.charAt(10)); // figure out which button is pressed
	console.log("deleting item at index: " + index);
	medArr[index] = undefined; // remove the item at the array
	avail.push(index); avail.sort(); // add index as available an sort the availability array
	(upper > 0) ? upper-- : upper = 0; // decrement upper.
	serial.write("^" + index); // tell the microcontroller to delete at index
	console.log(medArr);
	displayToDos(); // display the new todos
}

// Removes all of the <li> DOM elements created previously and 
// recreates new <li> DOM elements based on updated array.
function displayToDos() {
	medDisp.forEach(obj => obj.remove()); // remove all <li> elements on display.
	for (let i = 0; i < 3; i++) {
		if (medArr[i] != undefined) {
			medDisp[i] = createDiv().addClass("listitem").id("item"+i).parent("divlist"); // create list item div
			createDiv().addClass("name_element").id("name_element"+i).parent("item"+i); // create div box for name
			createElement("p", " " + (i + 1) + ". " + medArr[i].name).addClass("p_name").parent("name_element"+i); // create p for name
			createDiv().addClass("time_element").id("time_element"+i).parent("item"+i); // create div box for time
			createElement("p", timeConvert(medArr[i].time)).addClass("p_time").parent("time_element"+i); // create p for time
			createDiv().addClass("del_element").id("del_element"+i).parent("item"+i); // create div box for delete btn
			let delButton = createButton("").addClass("del_button").id("del_button"+i).parent("del_element"+i); // create delete button
			delButton.mousePressed(deleteItem); // set an event listener for delete btn
			createElement("span", "×").addClass("del_content").parent("del_button"+i); // create span text for del btn
		}
	}
	console.log("mapped: " + medDisp);
}

// Sets Enter key as an input method.
function keyPressed() {
if (keyCode == 13) createNewItem(); // 13 is the Enter key.
}

// Updates the char count above the text field and restrict the user from inputting more than 16 chars.
function keyReleased() {
	let count = 14 - nameInput.value().length; // set count to be the remaining number of chars available.
	if (count < 0) { // if there are no more available chars
		nameInput.value(input.value().substring(0,14)); // restrict the string in the text field to 14.
		count = 0; // keep count at 0.
	}
	// update char count on webpage
	document.getElementById("char-count").innerHTML = count + " characters remaining.";
}

// Creates a string of all of the medicine items from the array.
function stringifyMed(index) {
	let output = "%" + index; // add start byte + index
	output += medArr[index].name.padEnd(14, " "); // append name of medicine (always 14 bytes)
	output += timeConvert(medArr[index].time); // add time input for medicines (always 8 bytes)
	output += timeRemaining(medArr[index].time).padStart(13, "0"); // add counter for TM4C (always 13 bytes)
	console.log(output);
	return output; // return the string
}

// Function to convert a given time to a "00:00 PM" format.
function timeConvert(time) {
	time = time.split(":"); // split the hours and minutes
	let timeOut = parseInt(time[0]);  // get the hours
	let pmFlag = timeOut >= 12; // determine whether hr is am or pm
	if (pmFlag && timeOut != 12) timeOut -= 12; // if during the PM and not 12, minus by 12
	if (timeOut > 0 && timeOut < 10) { // if hr is between 0 and 10 (exclusive)
		timeOut = "0" + timeOut + ":" + time[1]; // add a zero at the front
	} else { // if in the am 
		if (timeOut == 0) timeOut += 12; // if 00:00 change to 12:00am
		timeOut += ":" + time[1]; // add colon and mins
	}
	timeOut += (pmFlag) ? " PM" : " AM"; // add am or pm
	return timeOut;
}

// Function determines how much longer the TM4C needs to count to before the user has to take a medicine.
// Max value: 1382400000000 (= 60 * 60 * 24 * 16,000,000)
function timeRemaining(time) { 
	let today = new Date(), hr = parseInt(time[0]), output;
	console.log(today);
	time = time.split(":"); // split between hours (index 0) and minutes (index 1)
	hr = (today.getHours() > hr) ? today.getHours() - hr : 24 + (hr - today.getHours()); // calc no. of hrs remaining (in hr).
	output = (60 - today.getSeconds()); // calculate no. of sec remaining.
	console.log("sec remaining: " + output);
	output += 60 * (60 - parseInt(time[1])); // add no. of mins remaining (in sec).
	console.log("+ mins remaining: " + output);
	output += hr * 60 * 60; // add the no. of hours remaining (in sec).
	console.log("+ hrs remaining: " + output);
	output *= 16000000; // change output to string
	console.log("output: " + output);
	return output + ""; 
}