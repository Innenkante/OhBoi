# OhBoi

OhBoi is a project which allows you to inject and execute javascript in native processes with an API aimed at reverse engineering and game hacking

## Modules

* [log](###log)
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

* [nativeModule](###nativeModule)
* [nativeExport](###nativeExport)
* [nativeFunction](###nativeFunction)
* [nativeException](###nativeException)

## Miscellanous

* [format](###format)

## Examples
 * [MW3-ESP](##MW3-ESP)


### log:

* create()

	

``` javascript
log.create();
```

* setTitle(title)

	

``` javascript
log.setTitle("My cool app")
```

* free()

	

``` javascript
log.free()
```

* write(message)

	

``` javascript
log.write("No errors")
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

* array readIntArray(address, value); 

	

``` javascript
readIntArray(0x1234, 4)
```

* writeFloatArray(address, value)

	

``` javascript
writeFloatArray(0x1234, [1.0, 2.0, 3.0, 4.0])
```

* array readFloatArray(address, value)

	

``` javascript
readFloatArray(0x1234, 4)
```

* writeBoolArray(address, value)

	

``` javascript
writeBoolArray(0x1234, [true, false, true, false])
```

* array readBoolArray(address, value)

	

``` javascript
readBoolArray(0x1234, 4)
```

* writeDoubleArray(address, value)

	

``` javascript
writeDoubleArray(0x1234, [1.1, 1.2, 1.3, 1.4])
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

* nativeFunction createFunction(int address, callingConvention, string returnFormat, string parameterFormat); 

``` javascript
let nativeFunction = asm.createFunction(0x1234, callingConvention.stdcall, "int", "string");
let result = nativeFunction.call("Hello World");
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

* write(message)

	

``` javascript
file.write("Some message!")
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
    ui.drawRectangle(100, 100, 50, 50, color.red);
}

ui.create(renderer);
```

* drawText(x, y, size, color, text)
```javascript
function renderer() {
    ui.drawText(0,0,20,color.cyan,"Hello World!");
}
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

### nativeModule

* name
* path
* address

```typescript
class nativeModule {
    public name: string;
    public path: string;
    public address: string;
}
```
### nativeExport

* name
* address

```typescript
class nativeExport {
    public name: string;
    public address: number;
}
```
### nativeFunction:

* call(arguments) 
```typescript
class nativeFunction {
    call(...params: any): any;
}
```

### nativeException
* location
* address
* operation
* type
```typescript
class nativeException {
    public location: number;
    public address:number;
    public operation:string;
    public type:string;
}
```

## Miscellanous

### format

In regards to the argument passing in the initializeCall function, as shown above the delemiter used is a simple comma ", ". The types available are listed below.

* delemiter: ", " 
* int
* float
* double
* bool
* string
* wstring
* none

## Examples

### MW3-ESP
```javascript
//@ts-check
//yourcode
function Entity(clientBase, entityBase) {
    this.ClientAddress = clientBase;
    this.EntityAddress = entityBase;

    this.Id = memory.readInt(clientBase);
    this.Valid = memory.readInt(clientBase + 4);
    this.Alive = memory.readInt(entityBase + 464);
    this.UserName = memory.readString(clientBase + 0xC, 16);
    this.Team = memory.readInt(clientBase + 0x1C);
    this.Coords = memory.readFloatArray(entityBase + 0x14, 3);
}

let parameterChunk = memory.alloc(20);

let getScreenMatrix = asm.createFunction(0x004B6350, callingConvention.cdecl, "int", "none");
let worldToScreen = asm.createFunction(0x004E5FC0, callingConvention.cdecl, "none", "int,int,int,int");

function getPlayers() {
    var players = [];

    for (var i = 0; i < 18; i++) {
        var clientBase = 0x009FC748 + i * 0x560;
        var entityBase = 0x00A08630 + i * 0x1F8;

        players.push(new Entity(clientBase, entityBase));
    }

    return players;
}


function getScreenPosition(vector3) {
    let matrix = getScreenMatrix.call();
    memory.writeFloatArray(parameterChunk, vector3);

    worldToScreen.call(0, matrix, parameterChunk, parameterChunk + 12)
    return memory.readFloatArray(parameterChunk + 12, 2);

}

function draw3DLine(position, x1, y1, z1, x2, y2, z2, c) {
    var pointPos1 = [position[0] + x1, position[1] + y1, position[2] + z1];
    var pointPos2 = [position[0] + x2, position[1] + y2, position[2] + z2];

    var xy1 = getScreenPosition(pointPos1);
    var xy2 = getScreenPosition(pointPos2);

    ui.drawLine(xy1[0], xy1[1], xy2[0], xy2[1], 2, c);

}

function draw3DBox(position, width, height, c) {
    //bottom
    draw3DLine(position, -width, -width, 0, width, -width, 0, c);
    draw3DLine(position, -width, -width, 0, -width, width, 0, c);
    draw3DLine(position, width, width, 0, width, -width, 0, c);
    draw3DLine(position, width, width, 0, -width, width, 0, c);

    //middle
    draw3DLine(position, -width, -width, 0, -width, -width, height, c);
    draw3DLine(position, -width, width, 0, -width, width, height, c);
    draw3DLine(position, width, -width, 0, width, -width, height, c);
    draw3DLine(position, width, width, 0, width, width, height, c);

    //top
    draw3DLine(position, -width, -width, height, width, -width, height, c);
    draw3DLine(position, -width, -width, height, -width, width, height, c);
    draw3DLine(position, width, width, height, width, -width, height, c);
    draw3DLine(position, width, width, height, -width, width, height, c);
}

function renderer() {
    //ui.drawText(0,0,14,color.pink,"OhBoi loaded...");
    var players = getPlayers().filter(e => e.UserName != "Boboo99");
    var me = getPlayers().find(p => p.UserName == "Boboo99");

    for (var i = 0; i < players.length; i++) {
        
        if (players[i].Valid != 0 && players[i].Alive & 0x1) {
			players[i].Coords[2] -= 20;
            if (players[i].Team == me.Team)
                draw3DBox(players[i].Coords, 20, 80, color.green);
            else
                draw3DBox(players[i].Coords, 20, 80, color.red);
        }

    }
}

ui.create(renderer);
```