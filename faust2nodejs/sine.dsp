import("stdfaust.lib");

freq = hslider("freq",400,100,1000,0.01) : si.smoo;
gain = hslider("gain",0.5,0,1,0.01) : si.smoo;
volume = hslider("volume",1,0,1,0.01);
gate = button("gate") : si.smoo;

process = vgroup("sine",os.osc(freq)*gain*gate*volume*volume);