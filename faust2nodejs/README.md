# faust2nodejs

## Getting Ready

* `sudo apt install node-gyp`
* `sudo npm install node-gyp -g`

## To Compile Addons 

* Regular config: `node-gyp configure`
* Config to run in electron: `node-gyp --target=1.7.9 configure --dist-url=https://atom.io/download/electron` This ensures that we're compiling
for the right version of electron.
* cd build
* make