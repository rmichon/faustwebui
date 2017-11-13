// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

const {ipcRenderer} = require('electron');

//var mainDiv = document.createElement("div");
//mainDiv.setAttribute("id","faustUI");
//mainDiv.innerHTML = ipcRenderer.sendSync('getJSON', 'd');
//mainDiv.innerHTML = tst; 

var faustUI = FaustUI();

document.body.appendChild(faustUI);
