import("stdfaust.lib");

oscs = hgroup("Oscillators",sum(i,2,vgroup("Osc %i",os.osc(freq)*gain)))
with{
  freq = nentry("Frequency",300,100,2000,0.01);
  gain = nentry("Gain",0.5,0,1,0.01);
};

process = oscs*button("gate");
