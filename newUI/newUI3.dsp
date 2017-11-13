import("stdfaust.lib");

// Declaring a "UI" allows to specify UI element metadatas outside of their
// regular declaration (i.e., UI primitive). They're accessed through their
// address as suggested by Albert.
metadata 
  "/synth/freq" 
  "[type: knob][midi: ctrl 1][acc: 0 0 -10 0 10]
  [css: 
    .{
      color: rgb(25,36,98);
      width: 50%;
    }
    . > .tip{
      background-color: red;
    }
  ]";

metadata
  "/synth/gain"
  "[midi: ctrl 2][acc: 1 0 -10 0 10]";

// If the generated Faust object has a web UI, the appearance of its various
// elements can be configured via CSS. Each element in the UI has an ID 
// associated to it which corresponds to the path of the UI element in the
// interface tree. Each user interface element will have a clearly documented
// hierarchy allowing the programmer to override the basic design of any 
// element/sub-element of the UI. 
// In the following example, the color of the text and the
// size of the freq element are changed. Additionally, the color of the 
// handle of the knob is modified to be red. "tip" corresponds to a standard
// class that will be documented which corresponds to the "tip/notch" of the
// knob. The same will be true for any other element or "element of element" of
// a web interface, providing an infinite level of customization of the 
// interface.
metadata
  ""
  ""

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
