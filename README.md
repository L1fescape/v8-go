## V8-Go

> Compile and execute JavaScript inside of V8 via Go

### Building

First [download and install V8](https://code.google.com/p/v8-wiki/wiki/BuildingWithGYP).

Compile `v8wrapper.cpp`:

```
g++ -I. v8wrapper.cpp -o v8wrapper.so <v8 out dir>/libv8_{base,libbase,snapshot,libplatform}.a
```

Compilation might be difficult depending on what operating system you're on. I'm running OSX, so I built v8 with `make x64.debug` and compiled v8wrapper with:

```
g++ -I. v8wrapper.cpp -std=c++11 -stdlib=libstdc++ -o v8wrapper.so ../v8/v8/out/x64.debug/libv8_{base,libbase,snapshot,libplatform}.a -pthread -dynamiclib -flat_namespace
```

### Running

```
$ go run v8.go 'var a = new Array("Hello", "World"); a.join(" ");'
//-> Hello World

$ go run v8.go examples/person.js
//-> Andrew
//-> Andrew Kennedy
//-> undefined
```
