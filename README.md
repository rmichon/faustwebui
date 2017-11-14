# Faust Web UI

This repository contains an experimental UI system for web based applications.

## faust2nodejs and Electron

The current model is based on `faust2api`. `faust2api` generates a `DspFaust`
object (which can be a Jack, Alsa, CoreAudio, etc. audio engine). This object
is wrapped as a `DspFaustNode` (see `/faust2nodejs`) allowing it to be compiled
as a nodesjs native addon. Once the nodejs native addon is compiled (see the 
instructions in `/faust2nodejs/README.md`), it is called by the template
electron app (which can be found in `/electron`) which also takes of linking
it to the `faustwebui` object. Thus, the final application has a native audio
engine and an html interface.

There's currently no system automating all these steps but we'll add that soon...
