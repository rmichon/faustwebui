#include <node.h>
#include "FaustNode.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  FaustNode::Init(exports);
}

NODE_MODULE(faust, InitAll)