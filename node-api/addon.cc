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

Napi::Value VbDEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = vbdenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value VbD1Encode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = vbd1enc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value VbXEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = vbxenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value VbDdEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = vbddenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8Encode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = v8enc32(src.Data(), src.ElementLength(), dst.Data());
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8DEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = v8denc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8D1Encode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = v8d1enc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8ZEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = v8zenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8XEncode32(const Napi::CallbackInfo& info) {
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

  unsigned char *op = v8xenc32(src.Data(), src.ElementLength(), dst.Data(), 0);
  ptrdiff_t len = op - dst.Data();

  return Napi::Number::New(env, len);
}

Napi::Value V8NEncode32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nenc32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NDEncode32(const Napi::CallbackInfo& info) {
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

  size_t len = v8ndenc32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8ND1Encode32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nd1enc32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NZEncode32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nzenc32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NEncode128v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nenc128v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NDEncode128v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8ndenc128v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8ND1Encode128v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nd1enc128v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NZEncode128v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nzenc128v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NEncode256v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nenc256v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NDEncode256v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8ndenc256v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8ND1Encode256v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nd1enc256v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Value V8NZEncode256v32(const Napi::CallbackInfo& info) {
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

  size_t len = v8nzenc256v32(src.Data(), src.ElementLength(), dst.Data());

  return Napi::Number::New(env, len);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "StrConcat"), Napi::Function::New(env, StrConcat));
  exports.Set(Napi::String::New(env, "VbEncode32"), Napi::Function::New(env, VbEncode32));
  exports.Set(Napi::String::New(env, "VbDEncode32"), Napi::Function::New(env, VbDEncode32));
  exports.Set(Napi::String::New(env, "VbD1Encode32"), Napi::Function::New(env, VbD1Encode32));
  exports.Set(Napi::String::New(env, "VbZEncode32"), Napi::Function::New(env, VbZEncode32));
  exports.Set(Napi::String::New(env, "VbXEncode32"), Napi::Function::New(env, VbXEncode32));
  exports.Set(Napi::String::New(env, "VbDdEncode32"), Napi::Function::New(env, VbDdEncode32));
  exports.Set(Napi::String::New(env, "V8Encode32"), Napi::Function::New(env, V8Encode32));
  exports.Set(Napi::String::New(env, "V8DEncode32"), Napi::Function::New(env, V8DEncode32));
  exports.Set(Napi::String::New(env, "V8D1Encode32"), Napi::Function::New(env, V8D1Encode32));
  exports.Set(Napi::String::New(env, "V8ZEncode32"), Napi::Function::New(env, V8ZEncode32));
  exports.Set(Napi::String::New(env, "VX8Encode32"), Napi::Function::New(env, V8XEncode32));

  exports.Set(Napi::String::New(env, "V8NEncode32"), Napi::Function::New(env, V8NEncode32));
  exports.Set(Napi::String::New(env, "V8NDEncode32"), Napi::Function::New(env, V8NDEncode32));
  exports.Set(Napi::String::New(env, "V8ND1Encode32"), Napi::Function::New(env, V8ND1Encode32));
  exports.Set(Napi::String::New(env, "V8NZEncode32"), Napi::Function::New(env, V8NZEncode32));

  exports.Set(Napi::String::New(env, "V8NEncode128v32"), Napi::Function::New(env, V8NEncode128v32));
  exports.Set(Napi::String::New(env, "V8NDEncode128v32"), Napi::Function::New(env, V8NDEncode128v32));
  exports.Set(Napi::String::New(env, "V8ND1Encode128v32"), Napi::Function::New(env, V8ND1Encode128v32));
  exports.Set(Napi::String::New(env, "V8NZEncode128v32"), Napi::Function::New(env, V8NZEncode128v32));

  exports.Set(Napi::String::New(env, "V8NEncode256v32"), Napi::Function::New(env, V8NEncode256v32));
  exports.Set(Napi::String::New(env, "V8NDEncode256v32"), Napi::Function::New(env, V8NDEncode256v32));
  exports.Set(Napi::String::New(env, "V8ND1Encode256v32"), Napi::Function::New(env, V8ND1Encode256v32));
  exports.Set(Napi::String::New(env, "V8NZEncode256v32"), Napi::Function::New(env, V8NZEncode256v32));

  return exports;
}

NODE_API_MODULE(addon, Init)
