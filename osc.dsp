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
  freq = hslider("Frequency",300,100,2000,0.01);
  gain = hslider("Gain",0.5,0,1,0.01);
};

sine = hgroup("Sine",os.osc(freq)*gain)
with{
  freq = vslider("Frequency",300,100,2000,0.01);
  gain = vslider("Gain",0.5,0,1,0.01);
};

triangle = vgroup("Triangle",os.triangle(freq)*gain)
with{
  freq = nentry("Frequency",300,100,2000,0.01);
  gain = nentry("Gain",0.5,0,1,0.01);
};

square = vgroup("Square",os.square(freq)*gain)
with{
  freq = hslider("Frequency[test:toto]",300,100,2000,0.01);
  gain = hslider("Gain",0.5,0,1,0.01);
};

oscillators = hgroup("[0]Oscillators",(sawtooth+sine+triangle+square))*(hgroup("[1]",gate))
with{
  click = button("Button");
  hold = checkbox("Checkbox");
  gate = click+hold : min(1);
};

process = oscillators;
