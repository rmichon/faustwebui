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

function createHslider(parent,curJSON){
  var sliderDiv = document.createElement("div");
  sliderDiv.setAttribute("class","hsliderContainer")

  var sliderValue = document.createElement("div");
  sliderValue.setAttribute("class","hsliderValue");
  sliderValue.setAttribute("id",curJSON[x].address+"-val");
  sliderValue.innerHTML += curJSON[x].init;
  sliderDiv.appendChild(sliderValue);

  var slider = document.createElement("input");
  slider.setAttribute("type","range");
  slider.setAttribute("class",curJSON[x].type);
  slider.setAttribute("value",curJSON[x].init);
  slider.setAttribute("min",curJSON[x].min);
  slider.setAttribute("max",curJSON[x].max);
  slider.setAttribute("step",curJSON[x].step);
  slider.setAttribute("oninput","rec(\""+curJSON[x].address+"\",event)");
  sliderDiv.appendChild(slider);

  createUIElement(parent,sliderDiv,curJSON[x].label);
}

function createVslider(parent,curJSON){
  var sliderDiv = document.createElement("div");
  sliderDiv.setAttribute("class","vsliderContainer")

  var slider = document.createElement("input");
  slider.setAttribute("type","range");
  slider.setAttribute("class",curJSON[x].type);
  slider.setAttribute("value",curJSON[x].init);
  slider.setAttribute("min",curJSON[x].min);
  slider.setAttribute("max",curJSON[x].max);
  slider.setAttribute("step",curJSON[x].step);
  slider.setAttribute("oninput","rec(\""+curJSON[x].address+"\",event)");
  sliderDiv.appendChild(slider);

  var sliderValue = document.createElement("div");
  sliderValue.setAttribute("class","vsliderValue");
  sliderValue.setAttribute("id",curJSON[x].address+"-val");
  sliderValue.innerHTML += curJSON[x].init;
  sliderDiv.appendChild(sliderValue);

  createUIElement(parent,sliderDiv,curJSON[x].label);
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
      createHslider(curDiv,curJSON);
    }
    else if(curJSON[x].type == "vslider" ||
        curJSON[x].type == "nentry"){ // TODO: "nentry" primitive
      createVslider(curDiv,curJSON);
    }
  }
  gray -= 25;
}

function buildFaustUI(fDSP){
  faustDSP = fDSP;
  var faustJSON = JSON.parse(faustDSP.getJSON());
  parseFaustUI(faustJSON.ui,document.getElementById("faustUI"));
}
