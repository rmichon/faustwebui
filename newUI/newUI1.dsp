import("stdfaust.lib");

// Configures the properties of the "synth" group
.synth{
  key0: value;
  key1: value;
}

// Configures the properties of all the potential "freq" elements
.freq{
  key0: value;
  key1: value;
}

// Configures the properties of the freq element in the synth group
.synth .freq{
  type: hslider;
  midi: ctrl 1;
  acc: 0 0 -10 0 10;
  _width: 80%; // CSS key: the underscore allows to specify "raw" CSS keys
  // asscoiated with a specific UI element
}

// Potentially, the various elements declared above could be declared in a 
// separate file whose extension could be "dspui":
import("synthUI.dspui");

// All properties correspond to the "old" metadata system and are integrated
// to the JSON description of the object as well as to the buildUserInterface() 
// method (this system doesn't change, ensuring backward comaptibility).

// UI primitives define the "type" key but are overriden when the "type" key
// is defined in the UI description as above
freq = nentry("freq",400,50,2000,0.01);
// Key/value pairs can still be decclared as metadata
gain = nentry("gain[style:knob]",0.5,0,1,0.01);
gate = button("gate");

process = group("synth",os.sawtooth(freq)*gain*gate);
