

# OhBoi


OhBoi is a project which allows you to do inject and execute javascript in native processes with an API aimed at reverse engineering and game modification

# Features

The runtime has a bunch of diffrent functions...

## console:
* alloc()
	* `console.alloc();`
* setTitle(title)
	* `console.setTitle("My cool app");`
* free()
	* `console.free();`
* log(message)
	* `console.log("No errors");`

## memory:
* int readInt(address)
	* `let value = memory.readInt(0x1234);`
* writeInt(address,value)
	* `memory.writeInt(0x1234,1234);`
* bool readBool(address)
	* `let value = memory.readBool(0x1234);`
* writeBool(address,value)
	* `memory.writeBool(0x1234,true);`
* string readString(address)
	* `let value = memory.readString(0x1234);`
* writeString(address, value)
	* `memory.writeString(0x1234,"I am a string");`
* float readFloat(address)
	* `let value = memory.readFloat(0x1234);`
* writeFloat(address, value)
	* `memory.writeFloat(0x1234,1.0);`
* double readDouble(address)
	* `let value = memory.readDouble(0x1234,1.0);`
* writeDouble(address, value)
	* `writeDouble(0x1234,1.0);`
* writeIntArray(address,value);
	* `writeIntArray(0x1234,[1,2,3,4]);`
* writeFloatArray(address,value)
	* `writeFloatArray(0x1234,[1.0,2.0,3.0,4.0]);`
* writeBoolArray(address,value)
	* `writeBoolArray(0x1234,[true,false,true,false]);`
* writeDoubleArray(address,value)
	* `writeDoubleArray(0x1234,[1.1,1.2,1.3,1.4]);`
* array readIntArray(address,value);
	* `readIntArray(0x1234,4);`
* array readFloatArray(address,value)
	* `readFloatArray(0x1234,4);`
* array readBoolArray(address,value)
	* `readBoolArray(0x1234,4);`
* array readDoubleArray(address,value)
	* `readDoubleArray(0x1234,4);`
* int alloc(size)
	* `let allocatedMemory = memory.alloc(1024);`
* free(address, size)
	* `memory.free(allocatedMemory,1024);`
* setProtection(address,protection,size)
	* `memory.setProtection(allocatedMemory,protection.EXECUTEREADWRITE,1024);`
* protection getProtection(address)
	* `let protection = memory.getProtection(address);`

## asm
* writeShellcode(int address, string shellcode)
	* `asm.writeShellcode(0x1234,"mov eax, edx; call eax; ret 4;");`
* placeShellcodeHook(int address, string shellcode)
	* `asm.placeShellcodeHook(0x1234,"add eax, edx;");`
* placeCallbackHook(int address, string format, function callback);
```javascript
function hookedFunction(arg1,arg2,arg3) { 
	console.log("String:" + arg1 + ";Int:" + arg2.toString() + ";float:" + arg3.toString());
}
asm.placeCallbackHook(0x1234,"string,int,float",hookedFunction);
```
* placeManualHook(int address, string prologue, string epilogue, function callback);
```javascript
function hookedFunction() {
	console.log("I am hooked!");
}
asm.placeManualHook(0x1234,"mov eax,0x5678; call eax; pushad; pushfd;","popfd; popad;",hookedFunction);
```
* nativeCall initializeCall(int address, callingConvention, string returnFormat, string parameterFormat);
```javascript
let nativeCall = asm.initializeCall(0x1234,callingConvention.stdcall,"int","string");
let result = nativeCall.call("Hello World");
```

## winapi
* module[] getModules();
```javascript
for(var module of winapi.getModules())
	console.log(module.name + "::" + module.path + "::" module.address.toString(16));
```
* module getModule(moduleName);
```javascript
let m = winapi.getModule("kernel32.dll");
console.log(m.name + "::" + m.path + "::" + m.address.toString(16));
```
* export[] getExports(moduleName);
```javascript
for(var export in winapi.getExports("kernel32.dll"))
	console.log(export.name + "::" + export.address.toString(16));
```
* export getExport(moduleName, exportName);
```javascript
let loadLib = winapi.getExport("kernel32.dll","LoadLibraryA");
console.log(loadLib.name + "::" + loadLib.address.toString(16));
```
* addExceptionHandler(exceptionHandler);
```javascript
function exceptionHandler(exception) {
	console.log(exception.location.toString(16) + "::" + exception.address.toString(16) + "::" + exception.operation + "::" + exception.type);
}
winapi.addExceptionHandler(exceptionHandler);
```
* removeExceptionHandler(exceptionHandler);
```javascript
winapi.removeExceptionHandler(exceptionHandler);
```
* setBreakpoint()
```javascript
winapi.setBreakpoint();
```
## file
* create(fileName)
	* `file.create("example.txt");`
* log(message)
	* `file.log("Some message!");`

# Constants

## protection:
* EXECUTE
* EXECUTE_READ
* EXECUTE_READWRITE
* EXECUTE_WRITECOPY
* NOACCESS
* READONLY
* READWRITE
* WRITECOPY

## callingConvention
* stdcall
* cdecl
* thiscall

## color
* black
* red
* green
* blue
* white
* yellow
* pink
* cyan

# Types

## module:
* name
* path
* address

## export:
* name
* address

## nativeCall:
* address
* call(arguments) 

# Miscellanous

## format:
In regards to the argument passing in the initializeCall function.
* delemiter: "," 
* int
* float
* double
* bool
* string
* wstring
* none
