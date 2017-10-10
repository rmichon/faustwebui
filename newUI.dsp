import("stdfaust.lib");

// could change poisition parameters, for example make som elements bigger
// than others
declare UI "[
  {'/synth/freq':[{'style':'hslider','width':'50%'}]},
  {'/synth/gate':[{'style':'checkbox'}]},
  {'/synth':[{'style':'hgroup'}]}
]";

// another option: replace the group by an interface ivolving multiple
// parameters
declare UI "[
  {'/synth':[{'style':'xy','x':'freq','y':'gain'}]}
]";

// or a full smartkeyb interface
declare UI "[
  {'/synth':[{'style':'smartkeyboard','Number of Keyboards':'5'}]}
]";

freq = nentry("freq",400,50,2000,0.01);
gain = nentry("gain[style:knob]",0.5,0,1,0.01);
gate = button("gate");

process = group("synth",os.sawtooth(freq)*gain*gate);
