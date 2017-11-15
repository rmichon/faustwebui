import("stdfaust.lib");

/*
oscs = hgroup("Oscillators",sum(i,2,vgroup("Osc %i",os.osc(freq)*gain)))
with{
  freq = nentry("Frequency",300,100,2000,0.01);
  gain = nentry("Gain",0.5,0,1,0.01);
};
*/

sawtooth = vgroup("Sawtooth",os.sawtooth(freq)*gain)
with{
  freq = hslider("Frequency[_width: 100][style:knob]",300,100,2000,0.01);
  gain = hslider("Gain[_width: 200][style:knob]",0.5,0,1,0.01);
};

sine = hgroup("Sine",os.osc(freq)*gain : visual)
with{
  freq = vslider("[0]Frequency",300,100,2000,0.01);
  gain = vslider("[1]Gain",0.5,0,1,0.01);
  visual = _ <: attach(_,an.amp_follower_ar(0.01,0.01) : vbargraph("[2]Output Gain",0,1));
};

triangle = vgroup("Triangle",os.triangle(freq)*gain)
with{
  freq = nentry("Frequency",300,100,2000,0.01);
  gain = nentry("Gain",0.5,0,1,0.01);
};

square = vgroup("Square",os.square(freq)*gain)
with{
  freq = hslider("Frequency",300,100,2000,0.01);
  gain = hslider("Gain",0.5,0,1,0.01);
};

oscillators = hgroup("[0]Oscillators",(sawtooth+sine+triangle+square))*(hgroup("[2]",gate)) <: attach(_,an.amp_follower_ar(0.01,0.01) : hbargraph("[1]Output Gain",0,1)) 
with{
  click = button("Button");
  hold = checkbox("Checkbox");
  gate = click+hold : min(1);
};

process = oscillators;
