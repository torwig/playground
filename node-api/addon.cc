#include <iostream>
#include <napi.h>
#include "integer-compression/vint.h"

Napi::Value StrConcat(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong type of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  auto s1 = info[0].As<Napi::String>().ToString();
  auto s2 = info[1].As<Napi::String>().ToString();

  Napi::String res = Napi::String::New(env, std::string(s1) + std::string(s2));

  return res;
}

Napi::Value VbZEncode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint32Array src = info[0].As<Napi::Uint32Array>();
  Napi::Uint8Array dst = info[1].As<Napi::Uint8Array>();

  unsigned char *op = vbzenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value VbEncode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint32Array src = info[0].As<Napi::Uint32Array>();
  Napi::Uint8Array dst = info[1].As<Napi::Uint8Array>();

  unsigned char *op = vbenc32(src.Data(), src.ElementLength(), dst.Data());
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "StrConcat"), Napi::Function::New(env, StrConcat));
  exports.Set(Napi::String::New(env, "VbZEncode32"), Napi::Function::New(env, VbZEncode32));
  exports.Set(Napi::String::New(env, "VbEncode32"), Napi::Function::New(env, VbEncode32));
  return exports;
}

NODE_API_MODULE(addon, Init)
