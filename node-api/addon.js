var addon = require('bindings')('addon.node')

console.log(addon.StrConcat("FoooO", "BaRr"))

const n = 4*1024*1024
var src = new Uint32Array(n)
for (let i = 0; i < src.length; i++) {
    src[i] = i;//Math.floor(Math.random() * 1000000);
}

var dst2 = new Uint8Array(16*n)
let s2 = addon.VbEncode32(src, dst2)
console.log("[VbEncode32]\t encoded length is: ", s2)

let check2 = new Uint32Array(n);
let s2_d = addon.VbDecode32(dst2, n, check2);
console.log("[VbDecode32]\t decoded bytes: ", s2_d);

for (let i = 0; i < n; i++) {
    if (src[i] != check2[i]) {
        console.log("elements at %d not equal: %d != %d", i, src[i], check2[i]);
    }
}

//---------------------------

var dst1 = new Uint8Array(16*n)
let s1 = addon.VbDEncode32(src, dst1)
console.log("[VbDEncode32]\t encoded length is: ", s1)

var dst3 = new Uint8Array(16*n)
let s3 = addon.VbD1Encode32(src, dst3)
console.log("[VbD1Encode32]\t encoded length is: ", s3)

var dst4 = new Uint8Array(16*n)
let s4 = addon.VbZEncode32(src, dst4)
console.log("[VbZEncode32]\t encoded length is: ", s4)

var dst5 = new Uint8Array(16*n)
let s5 = addon.VbXEncode32(src, dst5)
console.log("[VbXEncode32]\t encoded length is: ", s5)

var dst6 = new Uint8Array(16*n)
let s6 = addon.VbDdEncode32(src, dst6)
console.log("[VbDdEncode32]\t encoded length is: ", s6)

var dst7 = new Uint8Array(16*n)
let s7 = addon.V8Encode32(src, dst7)
console.log("[V8Encode32]\t encoded length is: ", s7)

var dst8 = new Uint8Array(16*n)
let s8 = addon.V8DEncode32(src, dst8)
console.log("[V8DEncode32]\t encoded length is: ", s8)

var dst9 = new Uint8Array(16*n)
let s9 = addon.V8D1Encode32(src, dst9)
console.log("[V8D1Encode32]\t encoded length is: ", s9)

var dst10 = new Uint8Array(16*n)
let s10 = addon.V8ZEncode32(src, dst10)
console.log("[V8ZEncode32]\t encoded length is: ", s10)

var dst12 = new Uint8Array(16*n)
let s12 = addon.V8XEncode32(src, dst12)
console.log("[V8XEncode32]\t encoded length is: ", s12)

var dst13 = new Uint8Array(16*n)
let s13 = addon.V8NEncode32(src, dst13)
console.log("[V8NEncode32]\t encoded length is: ", s13)

var dst14 = new Uint8Array(16*n)
let s14 = addon.V8NDEncode32(src, dst14)
console.log("[V8NDEncode32]\t encoded length is: ", s14)

var dst15 = new Uint8Array(16*n)
let s15 = addon.V8ND1Encode32(src, dst15)
console.log("[V8ND1Encode32]\t encoded length is: ", s15)

var dst17 = new Uint8Array(16*n)
let s17 = addon.V8NZEncode32(src, dst17)
console.log("[V8NZEncode32]\t encoded length is: ", s17)

// -------------------------

var dst18 = new Uint8Array(16*n)
let s18 = addon.V8NEncode128v32(src, dst18)
console.log("[V8NEncode128v32]\t encoded length is: ", s18)

var dst19 = new Uint8Array(16*n)
let s19 = addon.V8NDEncode128v32(src, dst19)
console.log("[V8NDEncode128v32]\t encoded length is: ", s19)

var dst20 = new Uint8Array(16*n)
let s20 = addon.V8ND1Encode128v32(src, dst20)
console.log("[V8ND1Encode128v32]\t encoded length is: ", s20)

var dst21 = new Uint8Array(16*n)
let s21 = addon.V8NZEncode128v32(src, dst21)
console.log("[V8NZEncode128v32]\t encoded length is: ", s21)

//-------------------------

var dst22 = new Uint8Array(16*n)
let s22 = addon.V8NEncode256v32(src, dst22)
console.log("[V8NEncode256v32]\t encoded length is: ", s22)

var dst23 = new Uint8Array(16*n)
let s23 = addon.V8NDEncode256v32(src, dst23)
console.log("[V8NDEncode256v32]\t encoded length is: ", s23)

var dst24 = new Uint8Array(16*n)
let s24 = addon.V8ND1Encode256v32(src, dst24)
console.log("[V8ND1Encode256v32]\t encoded length is: ", s24)

var dst25 = new Uint8Array(16*n)
let s25 = addon.V8NZEncode256v32(src, dst25)
console.log("[V8NZEncode256v32]\t encoded length is: ", s25)

//-----------------------------

let dst = new Uint8Array(16*n)
let len = addon.VsEncode32(src, dst)
console.log("[VsEncode32]\t\t encoded length is: ", len)

