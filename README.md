# OhBoi

OhBoi is a project which allows you to inject and execute javascript in native processes with an API aimed at reverse engineering and game hacking

## Modules
* [console](###console)
* [memory](###memory)
* [asm](###asm)
* [winapi](###winapi)
* [file](###file)
* [ui](###ui)
## Constants
* [protection](###protection)
* [callingConvention](###callingConvention)
* [color](###color)
## Types
* [module](###module)
* [export](###export)
* [nativeCall](###nativeCall)
## Miscellanous
* [format](###format)
## Examples
TODO!
***
### console:

* alloc()

	

``` javascript
		console.alloc();
```

* setTitle(title)

	

``` javascript
console.setTitle("My cool app")
```

* free()

	

``` javascript
console.free()
```

* log(message)

	

``` javascript
console.log("No errors")
```

### memory

* int readInt(address)

	

``` javascript
let value = memory.readInt(0x1234)
```

* writeInt(address, value)

	

``` javascript
memory.writeInt(0x1234, 1234)
```

* bool readBool(address)

	

``` javascript
let value = memory.readBool(0x1234)
```

* writeBool(address, value)

	

``` javascript
memory.writeBool(0x1234, true)
```

* string readString(address)

	

``` javascript
let value = memory.readString(0x1234)
```

* writeString(address, value)

	

``` javascript
memory.writeString(0x1234, "I am a string")
```

* float readFloat(address)

	

``` javascript
let value = memory.readFloat(0x1234)
```

* writeFloat(address, value)

	

``` javascript
memory.writeFloat(0x1234, 1.0)
```

* double readDouble(address)

	

``` javascript
let value = memory.readDouble(0x1234, 1.0)
```

* writeDouble(address, value)

	

``` javascript
writeDouble(0x1234, 1.0)
```

* writeIntArray(address, value); 

	

``` javascript
writeIntArray(0x1234, [1, 2, 3, 4])
```

* writeFloatArray(address, value)

	

``` javascript
writeFloatArray(0x1234, [1.0, 2.0, 3.0, 4.0])
```

* writeBoolArray(address, value)

	

``` javascript
writeBoolArray(0x1234, [true, false, true, false])
```

* writeDoubleArray(address, value)

	

``` javascript
writeDoubleArray(0x1234, [1.1, 1.2, 1.3, 1.4])
```

* array readIntArray(address, value); 

	

``` javascript
readIntArray(0x1234, 4)
```

* array readFloatArray(address, value)

	

``` javascript
readFloatArray(0x1234, 4)
```

* array readBoolArray(address, value)

	

``` javascript
readBoolArray(0x1234, 4)
```

* array readDoubleArray(address, value)

	

``` javascript
readDoubleArray(0x1234, 4)
```

* int alloc(size)

	

``` javascript
let allocatedMemory = memory.alloc(1024)
```

* free(address, size)

	

``` javascript
memory.free(allocatedMemory, 1024)
```

* setProtection(address, protection, size)

	

``` javascript
memory.setProtection(allocatedMemory, protection.EXECUTEREADWRITE, 1024)
```

* protection getProtection(address)

	

``` javascript
let protection = memory.getProtection(address)
```

### asm

* writeShellcode(int address, string shellcode)

	

``` javascript
asm.writeShellcode(0x1234, "mov eax, edx; call eax; ret 4;")
```

* placeShellcodeHook(int address, string shellcode)

	

``` javascript
asm.placeShellcodeHook(0x1234, "add eax, edx;")
```

* placeCallbackHook(int address, string format, function callback); 

``` javascript
function hookedFunction(arg1, arg2, arg3) {
    console.log("String:" + arg1 + ";Int:" + arg2.toString() + ";float:" + arg3.toString());
}
asm.placeCallbackHook(0x1234, "string,int,float", hookedFunction);
```

* placeManualHook(int address, string prologue, string epilogue, function callback); 

``` javascript
function hookedFunction() {
    console.log("I am hooked!");
}
asm.placeManualHook(0x1234, "mov eax,0x5678; call eax; pushad; pushfd;", "popfd; popad;", hookedFunction);
```

* nativeCall initializeCall(int address, callingConvention, string returnFormat, string parameterFormat); 

``` javascript
let nativeCall = asm.initializeCall(0x1234, callingConvention.stdcall, "int", "string");
let result = nativeCall.call("Hello World");
```

### winapi

* module[] getModules(); 

``` javascript
for (var module of winapi.getModules())
    console.log(module.name + "::" + module.path + "::"
        module.address.toString(16));
```

* module getModule(moduleName); 

``` javascript
let m = winapi.getModule("kernel32.dll");
console.log(m.name + "::" + m.path + "::" + m.address.toString(16));
```

* export[] getExports(moduleName); 

``` javascript
for (var
    export in winapi.getExports("kernel32.dll"))
    console.log(
        export.name + "::" +
        export.address.toString(16));
```

* export getExport(moduleName, exportName); 

``` javascript
let loadLib = winapi.getExport("kernel32.dll", "LoadLibraryA");
console.log(loadLib.name + "::" + loadLib.address.toString(16));
```

* addExceptionHandler(exceptionHandler); 

``` javascript
function exceptionHandler(exception) {
    console.log(exception.location.toString(16) + "::" + exception.address.toString(16) + "::" + exception.operation + "::" + exception.type);
}
winapi.addExceptionHandler(exceptionHandler);
```

* removeExceptionHandler(exceptionHandler); 

``` javascript
winapi.removeExceptionHandler(exceptionHandler);
```

* raiseInterrupt()

``` javascript
winapi.raiseInterrupt();
```

### file

* create(fileName)

	

``` javascript
file.create("example.txt")
```

* log(message)

	

``` javascript
file.log("Some message!")
```

### ui

* create(renderer); 

``` javascript
function renderer() {
    ui.drawLine(0, 0, 100, 100, 1, color.cyan);
}

ui.create(renderer);
```

* drawBox(x, y, width, height, color)

``` javascript
function renderer() {
    ui.drawBox(100, 100, 50, 50, color.red);
}

ui.create(renderer);
```

* drawLine(xStart, yStart, xEnd, yEnd, thickness, color)

``` javascript
function renderer() {
    ui.drawLine(0, 0, 100, 100, 1, color.cyan);
}

ui.create(renderer);
```

* drawRectangle(x, y, width, height, thickness, color)

``` javascript
function renderer() {
    ui.drawBox(100, 100, 50, 50, color.red);
}

ui.create(renderer);
```

## Constants

### protection:

* EXECUTE
* EXECUTE_READ
* EXECUTE_READWRITE
* EXECUTE_WRITECOPY
* NOACCESS
* READONLY
* READWRITE
* WRITECOPY

### callingConvention

* stdcall
* cdecl
* thiscall

### color

* black
* red
* green
* blue
* white
* yellow
* pink
* cyan

## Types

### module:

* name
* path
* address

### export:

* name
* address

### nativeCall:

* address
* call(arguments) 

## Miscellanous

### format:

In regards to the argument passing in the initializeCall function, as shown above the delemiter used is a simple comma ",". The types available are listed below.

* delemiter: ", " 
* int
* float
* double
* bool
* string
* wstring
* none

