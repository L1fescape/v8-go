#include "v8.h"
#include "libplatform/libplatform.h"

#include "v8wrapper.h"

static void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) return;
  v8::HandleScope scope(args.GetIsolate());
  v8::Handle<v8::Value> arg = args[0];
  v8::String::Utf8Value value(arg);
  printf("%s\n", *value);
}

using namespace v8;

int runv8(char *jssrc) {
  // Initialize V8.
  V8::InitializeICU();
  Platform* platform = platform::CreateDefaultPlatform();
  V8::InitializePlatform(platform);
  V8::Initialize();


  // Create a new Isolate and make it the current one.
  Isolate* isolate = Isolate::New();
  {
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a template for the global object and set the
    // built-in global functions.
    Local<ObjectTemplate> global = ObjectTemplate::New(isolate);

    // create a console object
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
    console->Set(String::NewFromUtf8(isolate, "log"), FunctionTemplate::New(isolate, LogCallback));

    global->Set(String::NewFromUtf8(isolate, "console"), console);
    // Each processor gets its own context so different processors
    // do not affect each other.
    Local<Context> context = Context::New(isolate, NULL, global);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    // Create a string containing the JavaScript source code.
    Local<String> source = String::NewFromUtf8(isolate, jssrc);

    // Compile the source code.
    Local<Script> script = Script::Compile(source);

    // Run the script to get the result.
    Local<Value> result = script->Run();

    // Convert the result to an UTF8 string and print it.
    String::Utf8Value utf8(result);
    printf("%s\n", *utf8);
  }

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  V8::Dispose();
  V8::ShutdownPlatform();
  delete platform;
  return 0;
}
