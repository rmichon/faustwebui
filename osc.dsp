import("stdfaust.lib");

oscs = hgroup("Oscillators",sum(i,2,hgroup("Osc %i",os.osc(freq)*gain)))
with{
  freq = vslider("Frequency",300,100,2000,0.01);
  gain = vslider("Gain",0.5,0,1,0.01);
};

process = oscs;
