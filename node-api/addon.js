var addon = require('bindings')('addon.node')

console.log(addon.StrConcat("FoooO", "BaRr"))

const n = 4*1024*1024
var src = new Uint32Array(n)
for (let i = 0; i < src.length; i++) {
    src[i] = i;//Math.floor(Math.random() * 1000000);
}

var dst1 = new Uint8Array(16*n)
let s1 = addon.VbZEncode32(src, dst1)
console.log("[VbZEncode32]\t encoded length is: ", s1)

var dst2 = new Uint8Array(16*n)
let s2 = addon.VbEncode32(src, dst2)
console.log("[VbEncode32]\t encoded length is: ", s2)

