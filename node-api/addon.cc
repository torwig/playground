#include <iostream>
#include <napi.h>
#include "integer-compression/vint.h"

Napi::Value Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);

  return num;
}

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

Napi::Value VbzEncode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of an argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  for (size_t i = 0; i < src.ElementLength(); ++i) {
    std::cout << src[i] << std::endl;
  }

  /*const size_t n = 400000;
  uint64_t in[n];
  for (size_t i = 0; i < n; ++i) {
    in[i] = i;
  }

  unsigned char out[n];

  unsigned char *op = vbzenc64(in, n, out, 0);

  ptrdiff_t l = op - out;

  std::cout << l << std::endl;

  uint64_t cpy[n];

  vbzdec64(out, n, cpy, 0);

  Napi::Uint8Array arr = Napi::Uint8Array::New(env, n);
  for (size_t i = 0; i < n; ++i) {
    arr[i] = cpy[i];
  }*/

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
  exports.Set(Napi::String::New(env, "StrConcat"), Napi::Function::New(env, StrConcat));
  exports.Set(Napi::String::New(env, "VbzEncode"), Napi::Function::New(env, VbzEncode));
  return exports;
}

NODE_API_MODULE(addon, Init)
