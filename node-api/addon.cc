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

Napi::Value VbZDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbzdec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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
  ptrdiff_t encoded = op - dst.Data();

  return Napi::Number::New(env, encoded);
}

Napi::Value VbDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbdec32(src.Data(), len, dst.Data());
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value VbDDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbddec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value VbD1Decode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbd1dec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value VbXDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbxdec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value VbDdDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = vbdddec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8Decode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = v8dec32(src.Data(), len, dst.Data());
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8DDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = v8ddec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8D1Decode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = v8d1dec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8ZDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = v8zdec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8XDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned char *op = v8xdec32(src.Data(), len, dst.Data(), 0);
  ptrdiff_t decoded = op - src.Data();

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8ndec32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nddec32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8ND1Decode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nd1dec32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NZDecode32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nzdec32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDecode128v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8ndec128v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDDecode128v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nddec128v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8ND1Decode128v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nd1dec128v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NZDecode128v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nzdec128v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDecode256v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8ndec256v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NDDecode256v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nddec256v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8ND1Decode256v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nd1dec256v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
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

Napi::Value V8NZDecode256v32(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the first argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong type of the second argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsTypedArray()) {
    Napi::TypeError::New(env, "Wrong type of the third argument").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Uint8Array src = info[0].As<Napi::Uint8Array>();
  Napi::Number len = info[1].ToNumber();
  Napi::Uint32Array dst = info[2].As<Napi::Uint32Array>();

  if (len.Uint32Value() < dst.ElementLength()) {
    Napi::TypeError::New(env, "Output array length is less than number of elements").ThrowAsJavaScriptException();
    return env.Null();
  }

  size_t decoded = v8nzdec256v32(src.Data(), len.Uint32Value(), dst.Data());

  return Napi::Number::New(env, decoded);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "StrConcat"), Napi::Function::New(env, StrConcat));

  exports.Set(Napi::String::New(env, "VbEncode32"), Napi::Function::New(env, VbEncode32));
  exports.Set(Napi::String::New(env, "VbDecode32"), Napi::Function::New(env, VbDecode32));

  exports.Set(Napi::String::New(env, "VbDEncode32"), Napi::Function::New(env, VbDEncode32));
  exports.Set(Napi::String::New(env, "VbDDecode32"), Napi::Function::New(env, VbDDecode32));

  exports.Set(Napi::String::New(env, "VbD1Encode32"), Napi::Function::New(env, VbD1Encode32));
  exports.Set(Napi::String::New(env, "VbD1Decode32"), Napi::Function::New(env, VbD1Decode32));

  exports.Set(Napi::String::New(env, "VbZEncode32"), Napi::Function::New(env, VbZEncode32));
  exports.Set(Napi::String::New(env, "VbZDecode32"), Napi::Function::New(env, VbZDecode32));

  exports.Set(Napi::String::New(env, "VbXEncode32"), Napi::Function::New(env, VbXEncode32));
  exports.Set(Napi::String::New(env, "VbXDecode32"), Napi::Function::New(env, VbXDecode32));

  exports.Set(Napi::String::New(env, "VbDdEncode32"), Napi::Function::New(env, VbDdEncode32));
  exports.Set(Napi::String::New(env, "VbDdDecode32"), Napi::Function::New(env, VbDdDecode32));

  exports.Set(Napi::String::New(env, "V8Encode32"), Napi::Function::New(env, V8Encode32));
  exports.Set(Napi::String::New(env, "V8Decode32"), Napi::Function::New(env, V8Decode32));

  exports.Set(Napi::String::New(env, "V8DEncode32"), Napi::Function::New(env, V8DEncode32));
  exports.Set(Napi::String::New(env, "V8DDecode32"), Napi::Function::New(env, V8DDecode32));

  exports.Set(Napi::String::New(env, "V8D1Encode32"), Napi::Function::New(env, V8D1Encode32));
  exports.Set(Napi::String::New(env, "V8D1Decode32"), Napi::Function::New(env, V8D1Decode32));

  exports.Set(Napi::String::New(env, "V8ZEncode32"), Napi::Function::New(env, V8ZEncode32));
  exports.Set(Napi::String::New(env, "V8ZDecode32"), Napi::Function::New(env, V8ZDecode32));

  exports.Set(Napi::String::New(env, "V8XEncode32"), Napi::Function::New(env, V8XEncode32));
  exports.Set(Napi::String::New(env, "V8XDecode32"), Napi::Function::New(env, V8XDecode32));

  exports.Set(Napi::String::New(env, "V8NEncode32"), Napi::Function::New(env, V8NEncode32));
  exports.Set(Napi::String::New(env, "V8NDecode32"), Napi::Function::New(env, V8NDecode32));

  exports.Set(Napi::String::New(env, "V8NDEncode32"), Napi::Function::New(env, V8NDEncode32));
  exports.Set(Napi::String::New(env, "V8NDDecode32"), Napi::Function::New(env, V8NDDecode32));

  exports.Set(Napi::String::New(env, "V8ND1Encode32"), Napi::Function::New(env, V8ND1Encode32));
  exports.Set(Napi::String::New(env, "V8ND1Decode32"), Napi::Function::New(env, V8ND1Decode32));

  exports.Set(Napi::String::New(env, "V8NZEncode32"), Napi::Function::New(env, V8NZEncode32));
  exports.Set(Napi::String::New(env, "V8NZDecode32"), Napi::Function::New(env, V8NZDecode32));

  exports.Set(Napi::String::New(env, "V8NEncode128v32"), Napi::Function::New(env, V8NEncode128v32));
  exports.Set(Napi::String::New(env, "V8NDecode128v32"), Napi::Function::New(env, V8NDecode128v32));

  exports.Set(Napi::String::New(env, "V8NDEncode128v32"), Napi::Function::New(env, V8NDEncode128v32));
  exports.Set(Napi::String::New(env, "V8NDDecode128v32"), Napi::Function::New(env, V8NDDecode128v32));

  exports.Set(Napi::String::New(env, "V8ND1Encode128v32"), Napi::Function::New(env, V8ND1Encode128v32));
  exports.Set(Napi::String::New(env, "V8ND1Decode128v32"), Napi::Function::New(env, V8ND1Decode128v32));

  exports.Set(Napi::String::New(env, "V8NZEncode128v32"), Napi::Function::New(env, V8NZEncode128v32));
  exports.Set(Napi::String::New(env, "V8NZDecode128v32"), Napi::Function::New(env, V8NZDecode128v32));

  exports.Set(Napi::String::New(env, "V8NEncode256v32"), Napi::Function::New(env, V8NEncode256v32));
  exports.Set(Napi::String::New(env, "V8NDecode256v32"), Napi::Function::New(env, V8NDecode256v32));

  exports.Set(Napi::String::New(env, "V8NDEncode256v32"), Napi::Function::New(env, V8NDEncode256v32));
  exports.Set(Napi::String::New(env, "V8NDDecode256v32"), Napi::Function::New(env, V8NDDecode256v32));

  exports.Set(Napi::String::New(env, "V8ND1Encode256v32"), Napi::Function::New(env, V8ND1Encode256v32));
  exports.Set(Napi::String::New(env, "V8ND1Decode256v32"), Napi::Function::New(env, V8ND1Decode256v32));

  exports.Set(Napi::String::New(env, "V8NZEncode256v32"), Napi::Function::New(env, V8NZEncode256v32));
  exports.Set(Napi::String::New(env, "V8NZDecode256v32"), Napi::Function::New(env, V8NZDecode256v32));

  return exports;
}

NODE_API_MODULE(addon, Init)
