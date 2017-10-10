var faustDSP = null;
var gray = 50;

function rec(address,event){
  var val = parseFloat(event.target.value);
  faustDSP.setParamValue(address,val);
  var valueBox = document.getElementById(address+"-val");
  valueBox.innerHTML = val;
}

function createUIElement(parent,child,label){
  var elementDiv = document.createElement("div");
  elementDiv.setAttribute("class","uiElement");
  elementDiv.style.backgroundColor = "rgb("+gray+","+gray+","+gray+")";
  elementDiv.appendChild(child);
  var labelDiv = document.createElement("div");
  labelDiv.setAttribute("class","label");
  labelDiv.innerHTML = label;
  elementDiv.appendChild(labelDiv);
  parent.appendChild(elementDiv);
  return elementDiv;
}

function createVgroup(parent,label){
  var group = document.createElement("div");
  group.setAttribute("class","vgroup");
  createUIElement(parent,group,label);
  return group;
}

function createHgroup(parent,label){
  var group = document.createElement("div");
  group.setAttribute("class","hgroup");
  createUIElement(parent,group,label);
  return group;
}

// function essentially behaving like a class
function Hslider(curJSON){
  var hslider = document.createElement("div");
  hslider.setAttribute("class","hslider")
  hslider.value = Number(curJSON[x].init);
  hslider.min = Number(curJSON[x].min);
  hslider.max = Number(curJSON[x].max);
  hslider.range = hslider.max-hslider.min;
  hslider.step = Number(curJSON[x].step);
  hslider.address = Number(curJSON[x].address);
  hslider.clicked = 0;

  var sliderValue = document.createElement("div");
  hslider.appendChild(sliderValue);
  sliderValue.setAttribute("class","value");
  sliderValue.setAttribute("id",curJSON[x].address+"-val");
  sliderValue.innerHTML += curJSON[x].init;

  var sliderBar = document.createElement("div");
  hslider.appendChild(sliderBar);
  sliderBar.setAttribute("class","bar");
  sliderBar.addEventListener("mousedown",sliderClickDown,false);
  sliderBar.addEventListener("mouseup",sliderClickUp,false);
  sliderBar.addEventListener("mouseleave",sliderClickUp,false);
  sliderBar.addEventListener("mousemove",sliderMove,false);

  var sliderCursor = document.createElement("div");
  sliderBar.appendChild(sliderCursor);
  sliderCursor.setAttribute("class","cursor");

  hslider.setNormValue = function(v){
    if(v>=0 && v<=1){
      var cursorXPos = v*100 + "%";
      sliderCursor.style.left = cursorXPos;
      var paramValue = v*hslider.range + hslider.min;
      sliderValue.innerHTML = paramValue.toFixed(2);
      faustDSP.setParamValue(hslider.address,paramValue);
    }
  }

  var cursorNormXPos = hslider.value/hslider.range - hslider.min/hslider.range;
  hslider.setNormValue(cursorNormXPos);

  function sliderClickDown(e){
    var cursorPos = (e.clientX - this.offsetLeft)/this.offsetWidth;
    hslider.clicked = 1;
    hslider.setNormValue(cursorPos);
  }

  function sliderClickUp(e){
    if(hslider.clicked == 1){
      hslider.clicked = 0;
    }
  }

  function sliderMove(e){
    if(hslider.clicked == 1){
      var cursorPos = (e.clientX - this.offsetLeft)/this.offsetWidth;
      hslider.setNormValue(cursorPos);
    }
  }

  return hslider;
}

// function essentially behaving like a class
function Vslider(curJSON){
  var vslider = document.createElement("div");
  vslider.setAttribute("class","vslider")
  vslider.value = Number(curJSON[x].init);
  vslider.min = Number(curJSON[x].min);
  vslider.max = Number(curJSON[x].max);
  vslider.range = vslider.max-vslider.min;
  vslider.step = Number(curJSON[x].step);
  vslider.address = curJSON[x].address;
  vslider.clicked = 0;

  var sliderValue = document.createElement("div");
  sliderValue.setAttribute("class","value");
  sliderValue.setAttribute("id",curJSON[x].address+"-val");
  sliderValue.innerHTML += curJSON[x].init;

  var sliderBar = document.createElement("div");
  vslider.appendChild(sliderBar);
  sliderBar.setAttribute("class","bar");
  sliderBar.addEventListener("mousedown",sliderClickDown,false);
  sliderBar.addEventListener("mouseup",sliderClickUp,false);
  sliderBar.addEventListener("mouseleave",sliderClickUp,false);
  sliderBar.addEventListener("mousemove",sliderMove,false);

  vslider.appendChild(sliderValue);

  var sliderCursor = document.createElement("div");
  sliderBar.appendChild(sliderCursor);
  sliderCursor.setAttribute("class","cursor");

  vslider.setNormValue = function(v){
    if(v>=0 && v<=1){
      var cursorYPos = (1-v)*100 + "%";
      sliderCursor.style.top = cursorYPos;
      var paramValue = v*vslider.range + vslider.min;
      sliderValue.innerHTML = paramValue.toFixed(2);
      faustDSP.setParamValue(vslider.address,paramValue);
    }
  }

  var cursorNormYPos = vslider.value/vslider.range - vslider.min/vslider.range;
  vslider.setNormValue(cursorNormYPos);

  function sliderClickDown(e){
    var cursorPos = 1 - (e.clientY - this.offsetTop)/this.offsetHeight;
    vslider.clicked = 1;
    vslider.setNormValue(cursorPos);
  }

  function sliderClickUp(e){
    if(vslider.clicked == 1){
      vslider.clicked = 0;
    }
  }

  function sliderMove(e){
    if(vslider.clicked == 1){
      var cursorPos = 1 - (e.clientY - this.offsetTop)/this.offsetHeight;
      vslider.setNormValue(cursorPos);
    }
  }

  return vslider;
}

function parseFaustUI(curJSON,curDiv){
  gray += 25;
  for(x in curJSON){
    if(curJSON[x].type == "hgroup"){ // TODO: "group" primitive
      var group = createHgroup(curDiv,curJSON[x].label);
      //gray += 25;
      parseFaustUI(curJSON[x].items,group);
    }
    else if(curJSON[x].type == "vgroup"){ // TODO: "group" primitive
      var group = createVgroup(curDiv,curJSON[x].label);
      //gray += 25;
      parseFaustUI(curJSON[x].items,group);
    }
    else if(curJSON[x].type == "hslider"){ // TODO: "nentry" primitive
      var hslider = new Hslider(curJSON);
      createUIElement(curDiv,hslider,curJSON[x].label);
    }
    else if(curJSON[x].type == "vslider" ||
        curJSON[x].type == "nentry"){ // TODO: "nentry" primitive
      var vslider = new Vslider(curJSON);
      createUIElement(curDiv,vslider,curJSON[x].label);
    }
  }
  gray -= 25;
}

function buildFaustUI(fDSP){
  faustDSP = fDSP;
  var faustJSON = JSON.parse(faustDSP.getJSON());
  parseFaustUI(faustJSON.ui,document.getElementById("faustUI"));
}
