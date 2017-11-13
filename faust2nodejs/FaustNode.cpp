#include "FaustNode.h"

using namespace v8;

Persistent<Function> FaustNode::constructor;

bool isInteger(const std::string & s) {
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
  char * p ;
  strtol(s.c_str(), &p, 10) ;
  return (*p == 0) ;
}

FaustNode::FaustNode() {
  dspFaust = new DspFaust();
}

FaustNode::FaustNode(int sample_rate, int buffer_size) {
  dspFaust = new DspFaust(sample_rate, buffer_size);
}

FaustNode::~FaustNode() {
  delete dspFaust;
}

void FaustNode::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "FaustNode"));
  tpl->InstanceTemplate()->SetInternalFieldCount(2);

  // Prototypes
  NODE_SET_PROTOTYPE_METHOD(tpl, "start", start);
  NODE_SET_PROTOTYPE_METHOD(tpl, "stop", stop);
  NODE_SET_PROTOTYPE_METHOD(tpl, "isRunning", isRunning);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyOn", keyOn);
  NODE_SET_PROTOTYPE_METHOD(tpl, "keyOff", keyOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "newVoice", newVoice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "deleteVoice", deleteVoice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "allNotesOff", allNotesOff);
  NODE_SET_PROTOTYPE_METHOD(tpl, "propagateMidi", propagateMidi);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getJSONUI", getJSONUI);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getJSONMeta", getJSONMeta);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamsCount", getParamsCount);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setParamValue", setParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamValue", getParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setVoiceParamValue", setVoiceParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getVoiceParamValue", getVoiceParamValue);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamAddress", getParamAddress);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getVoiceParamAddress", getVoiceParamAddress);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamMin", getParamMin);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamMax", getParamMax);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getParamInit", getParamInit);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "FaustNode"),
               tpl->GetFunction());
}

void FaustNode::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new FaustNode(...)`
    FaustNode* faustNode;
    if(args[0]->IsUndefined()){ // if arg 0 is undefined then should be same for arg1
      faustNode = new FaustNode();
    }
    else{
      faustNode = new FaustNode((int)args[0]->NumberValue(), 
        (int)args[1]->NumberValue());
    }
    faustNode->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } 
  else {
    // Invoked as plain function `FaustNode(...)`, turn into construct call.
    // TODO
    // const int argc = 1;
    // Local<Value> argv[argc] = { args[0] };
    // Local<Function> cons = Local<Function>::New(isolate, constructor);
    // args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void FaustNode::start(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(Boolean::New(isolate, fNode->dspFaust->start()));
}

void FaustNode::stop(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  fNode->dspFaust->stop();
}

void FaustNode::isRunning(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(Boolean::New(isolate, fNode->dspFaust->isRunning()));
}

void FaustNode::keyOn(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int pitch = (int) args[0]->NumberValue();
    int velocity = (int) args[1]->NumberValue();
    args.GetReturnValue().Set(
      Number::New(isolate, fNode->dspFaust->keyOn(pitch,velocity)));
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::keyOff(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    int pitch = (int) args[0]->NumberValue();
    args.GetReturnValue().Set(
      Integer::New(isolate, fNode->dspFaust->keyOff(pitch)));
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::newVoice(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(Number::New(isolate,fNode->dspFaust->newVoice()));
}

void FaustNode::deleteVoice(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    unsigned long voice = (unsigned long) args[0]->NumberValue();
    args.GetReturnValue().Set(
      Integer::New(isolate, fNode->dspFaust->deleteVoice(voice)));
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::allNotesOff(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  fNode->dspFaust->allNotesOff();
}

void FaustNode::propagateMidi(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && 
      !args[1]->IsUndefined() &&
      !args[2]->IsUndefined() &&
      !args[3]->IsUndefined() &&
      !args[4]->IsUndefined() &&
      !args[5]->IsUndefined()) {
    int count = (int) args[0]->NumberValue();
    double time = (int) args[1]->NumberValue();
    int type = (int) args[2]->NumberValue();
    int channel = (int) args[3]->NumberValue();
    int data1 = (int) args[4]->NumberValue();
    int data2 = (int) args[5]->NumberValue();
    fNode->dspFaust->propagateMidi(count,time,type,channel,data1,data2);
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getJSONUI(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate,fNode->dspFaust->getJSONUI()));
}

void FaustNode::getJSONMeta(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate,fNode->dspFaust->getJSONMeta()));
}

void FaustNode::getParamsCount(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  args.GetReturnValue().Set(Integer::New(isolate,fNode->dspFaust->getParamsCount()));
}

void FaustNode::setParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    float paramValue = (float) args[1]->NumberValue();
    if(isInteger(paramAddress)) {
      fNode->dspFaust->setParamValue(std::stoi(paramAddress),paramValue);
    }
    else {
      fNode->dspFaust->setParamValue(paramAddress.c_str(),paramValue);
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamValue(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamValue(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::setVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined() && !args[2]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    float paramValue = (float) args[2]->NumberValue();
    if(isInteger(paramAddress)) {
      fNode->dspFaust->setVoiceParamValue(std::stoi(paramAddress),voice,paramValue);
    }
    else {
      fNode->dspFaust->setVoiceParamValue(paramAddress.c_str(),voice,paramValue);
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getVoiceParamValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getVoiceParamValue(std::stoi(paramAddress),voice)));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getVoiceParamValue(paramAddress.c_str(),voice)));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    int paramID = (int) args[0]->NumberValue();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,
      fNode->dspFaust->getParamAddress(paramID)));
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getVoiceParamAddress(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined() && !args[1]->IsUndefined()) {
    int paramID = (int) args[0]->NumberValue();
    unsigned long voice = (unsigned long) args[1]->NumberValue();
    const char* address = fNode->dspFaust->getVoiceParamAddress(paramID,voice);
    // TODO: smothing's not working here but don't really know what. probably
    // some typing issue
    printf("Toto: %s\n",address);
    //args.GetReturnValue().Set(String::NewFromUtf8(isolate,
    //  fNode->dspFaust->getVoiceParamAddress(paramID,voice)));
      args.GetReturnValue().Set(String::NewFromUtf8(isolate,(char*)address));
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getParamMin(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamMin(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamMin(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getParamMax(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamMax(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamMax(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}

void FaustNode::getParamInit(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  FaustNode* fNode = ObjectWrap::Unwrap<FaustNode>(args.Holder());
  if(!args[0]->IsUndefined()) {
    std::string paramAddress(*v8::String::Utf8Value(args[0]->ToString()));
    if(isInteger(paramAddress)) {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamInit(std::stoi(paramAddress))));
    }
    else {
      args.GetReturnValue().Set(Number::New(isolate,
        fNode->dspFaust->getParamInit(paramAddress.c_str())));
    }
  }
  else {
    printf("Missing argument\n");
  }
}
  
