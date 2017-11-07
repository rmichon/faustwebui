if (typeof (WebAssembly) === "undefined") {
    alert("WebAssembly is not supported in this browser, the page will not work !")
}

var isWebKitAudio = (typeof (webkitAudioContext) !== "undefined");
var audio_context = (isWebKitAudio) ? new webkitAudioContext() : new AudioContext();
var faustDSP = null;

function startDSP(){
  // Create the Faust generated node
  faust.createosc(audio_context, 1024,
    function (node) {
      faustDSP = node;
      faustDSP.connect(audio_context.destination);
      var faustUI = FaustUI(faustDSP);
      document.body.appendChild(faustUI);
    });
}

window.addEventListener("load", startDSP);
