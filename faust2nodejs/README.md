# faust2nodejs

## Getting Ready

For this to work, you'll probably have to:

* `sudo apt install node-gyp`
* `sudo npm install node-gyp -g`

This list is not exhaustive and will be completed later.

## Compiling the Native Faust Addon 

* `node-gyp --target=1.7.9 configure --dist-url=https://atom.io/download/electron`
It is likely you'll have to adapt the value of `target` to your current 
electron version.
* cd build
* make

`binding.gyp` is currently extremely primitive and will likely only work on 
Linux for now... 

## Some Notes

The version of the `DspFaust` object present in this folder was generated
by running:

* `faust2api -jack -nvoices 12 -nodoc sine.dsp` (and then unzip the generated
file in the current folder).