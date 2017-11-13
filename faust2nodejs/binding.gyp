{
  "targets": [
    {
      "target_name": "faust",
      "include_dirs": [ "/usr/local/include" ],
      "cflags_cc!": [ "-fno-rtti","-fno-exceptions" ],
      "cflags": [ "-march=native -Ofast" ],
      "ldflags": [ "-ljack","-lsndfile" ],
      "libraries": [ "-ljack","-lsndfile" ],
      "sources": [ "faust.cpp","DspFaust.cpp","FaustNode.cpp" ]
    }
  ]
}