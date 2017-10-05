var faustDSP = null;

function rec(address,event){
  var val = parseFloat(event.target.value);
  faustDSP.setParamValue(address,val);
}

function parseFaustUI(curJSON,curDiv){
  for(x in curJSON){
    if(curJSON[x].type == "vgroup" ||
        curJSON[x].type == "hgroup"){ // TODO: "group" primitive
      var group = document.createElement("div");
      var groupID = "group" + curJSON[x].label;
      group.setAttribute("id",groupID);
      group.setAttribute("class",curJSON[x].type);
      curDiv.appendChild(group);
      parseFaustUI(curJSON[x].items,group);
    }
    else if(curJSON[x].type == "hslider" ||
        curJSON[x].type == "vslider" ||
        curJSON[x].type == "nentry"){ // TODO: "nentry" primitive
      var slider = document.createElement("input");
      slider.setAttribute("type","range");
      slider.setAttribute("class",curJSON[x].type);
      slider.setAttribute("value",curJSON[x].init);
      slider.setAttribute("min",curJSON[x].min);
      slider.setAttribute("max",curJSON[x].max);
      slider.setAttribute("step",curJSON[x].step);
      slider.setAttribute("oninput","rec(\""+curJSON[x].address+"\",event)");
      curDiv.appendChild(slider);
    }
  }
}

function buildFaustUI(fDSP){
  faustDSP = fDSP;
  var faustJSON = JSON.parse(faustDSP.getJSON());
  parseFaustUI(faustJSON.ui,document.getElementById("faustUI"));
}
