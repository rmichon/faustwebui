{
  "targets": [
    {
      "target_name": "faust",
      "include_dirs": [ "/usr/local/include" ],
      "cflags_cc!": [ "-fno-rtti","-fno-exceptions" ],
      "cflags": [ "-march=native -Ofast" ],     
      "libraries": [ "-L/usr/local/lib `pkg-config --cflags --libs jack sndfile`" ],
      "sources": [ "faust.cpp","DspFaust.cpp","DspFaustNode.cpp" ]
    }
  ]
}