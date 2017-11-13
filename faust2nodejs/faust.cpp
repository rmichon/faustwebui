#include <node.h>
#include "DspFaustNode.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  DspFaustNode::Init(exports);
}

NODE_MODULE(faust, InitAll)