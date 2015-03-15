package main

// #cgo LDFLAGS: -L. v8wrapper.so -lv8  -lstdc++ -pthread
// #include <stdlib.h>
// #include "v8wrapper.h"
import "C"
import (
  "unsafe"
  "os"
  "io/ioutil"
)


func main(){
  script := os.Args[1]
  var cstr *C.char;

  file, err := ioutil.ReadFile(script)
  if err == nil {
    cstr = C.CString(string(file))
  } else {
    // assume argument is js string instead of file name
    cstr = C.CString(string(script))
  }

  defer C.free(unsafe.Pointer(cstr))

  C.runv8(cstr)
}

