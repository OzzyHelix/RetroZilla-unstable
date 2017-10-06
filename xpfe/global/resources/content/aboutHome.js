/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// about:home JS

// XPCOM preferences integration
var prefs = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);

var aboutHomeAutofocus = prefs.getBoolPref("rzHome.autofocus");
var searchEngineURL = prefs.getCharPref("keyword.URL");

//check to see if custom search pref url exists
var prefServiceBranch = Components.classes["@mozilla.org/preferences-service;1"]
	.getService(Components.interfaces.nsIPrefService).getBranch("");
if(prefServiceBranch.getPrefType('rzHome.customsearch')){
	//key exist!
	var searchEngineURL = prefs.getCharPref("rzHome.customsearch");
} else {
	// use Google
	var searchEngineURL = "http://www.google.com/search?q=";
}

// autofocus function
function autoFocus() {
	document.getElementById("rzSearch").focus();
}

// onload function (used to allow for autofocus)
window.onload = function() {
	if (aboutHomeAutofocus == true) {
		autoFocus();
	}
	// set current year
	var d = new Date();
	var cYear = d.getFullYear();
	document.getElementById("currentYear").innerHTML = cYear;
};

// function that runs when the "Search" button is clicked
function rzSearch() {
	var searchQuery = document.getElementById("rzSearch").value;
	var searchURL = searchEngineURL + searchQuery;
	//alert("Location: " + searchURL); // for debug purposes
	window.location.replace(searchURL);
}