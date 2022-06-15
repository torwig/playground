var addon = require('bindings')('addon.node')

console.log('This should be eight:', addon.add(3, 5))
console.log(addon.StrConcat("FoooO", "BaRr"))

var src = new Uint8Array([10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95])
addon.VbzEncode(src)
