
declare global {
    export enum protection {
        EXECUTE,
        EXECUTE_READ,
        EXECUTE_READWRITE,
        EXECUTE_WRITECOPY,
        NOACCESS,
        READONLY,
        READWRITE,
        WRITECOPY
    }

    export enum callingConvention {
        stdcall,
        cdecl,
        thiscall
    }

    export enum color {
        black,
        red,
        green,
        blue,
        white,
        yellow,
        pink,
        cyan
    }

    /**
     * Represents a native function 
     */
    export class nativeFunction {
        /**
         * Invokes the native function
         * @param params The parameters for the function 
         */
        call(...params: any): any;
    }

    /**
     * Represents a native module ex. "kernel32.dll"
     */
    export class nativeModule {
        /**
         * Man fuck js docs already, Name of the module
         */
        public name: string;
        /**
         * Path of the module
         */
        public path: string;
        /**
         * Baseaddress of the module
         */
        public address: string;
    }

    /**
     * Represents a native modules' export ex. "LoadLibraryA"
     */
    export class nativeExport {
        /**
         * Name of the function exported
         */
        public name: string;
        /**
         * Address of the function exported
         */
        public address: number;
    }

    /**
     * Represents a native exception
     */
    export class nativeException {
        /**
         * The location at which the exception occurs
         */
        public location: number;
        /**
         * The address of the exception
         */
        public address:number;
        /**
         * What kind of operation happend
         */
        public operation:string;
        /**
         * The exception type
         */
        public type:string;
    }

    /**
     * Handles all console output
     */
    export namespace log {
        /**
         * Creates a new console window
         */
        export function create(): void;
        /**
         * Sets the title of the console
         * @param title The title to set
         */
        export function setTitle(title: string): void;
        /**
         * Closes the console
         */
        export function free(): void;
        /**
         * Writes to the console
         * @param message The string to output
         */
        export function write(message: string): void;
    }

    /**
     * Handles all memory interactions
     */
    export namespace memory {
        /**
         * Reads an integer from an address
         * @param address The Address to read the integer from
         */
        export function readInt(address: number): number;
        /**
         * Writes an integer to an address
         * @param address The Address to write the double to
         * @param value The integer to write
         */
        export function writeInt(address: number, value: number): void;

        /**
         * Reads a boolean from an address
         * @param address The Address to read the boolean from
         */
        export function readBool(address: number): boolean;
        /**
         * Writes a boolean to an address
         * @param address The Address to write the boolean to
         * @param value The boolean to write
         */
        export function writeBool(address: number, value: boolean): void;

        /**
         * Reads a string from an address
         * @param address The Address to read the string from
         * @param size The length of the string
         */
        export function readString(address: number,size:number): string;
        /**
         * Writes a string to an address
         * @param address The Address to write the string to
         * @param value The string to write
         */
        export function writeString(address: number, value: string): void;

        /**
         * Reads a float from an address
         * @param address The Address to read the float from
         */
        export function readFloat(address: number): number;
        /**
         * Writes a float to an address
         * @param address The Address to write the float to
         * @param value The float to write
         */
        export function writeFloat(address: number, value: number): void;

        /**
         * Reads an double from an address
         * @param address The Address to read the double from
         */
        export function readDouble(address: number): number;
        /**
         * Writes a double to an address
         * @param address The Address to write the double to
         * @param value The double to write
         */
        export function writeDouble(address: number, value: number): void;




        /**
         * Reads an integer Array from an address
         * @param address The Address to read the integer array from
         * @param size The size to read
         */
        export function readIntArray(address: number, size: number): number[];
        /**
         * Writes an integer Array to an adress
         * @param address The Adress to write the integer array to
         * @param value The integer array to write
         */
        export function writeIntArray(address: number, value: number[]): void;

        /**
         * Reads a float Array from an address
         * @param address The Address to read the float array from
         * @param size The size to read
         */
        export function readFloatArray(address: number, size: number): number[];
        /**
         * Writes a float Array to an adress
         * @param address The Adress to write the float array to
         * @param value The float array to write
         */
        export function writeFloatArray(address: number, value: number[]): void;

        /**
         * Reads a boolean Array from an address
         * @param address The Address to read the boolean array from
         * @param size The size to read
         */
        export function readBoolArray(address: number, size: number): number[];
        /**
         * Writes a boolean Array to an adress
         * @param address The Adress to write the boolean array to
         * @param value The boolean array to write
         */
        export function writeBoolArray(address: number, value: number[]): void;

        /**
         * Reads a double Array from an address
         * @param address The Address to read the double array from
         * @param size The size to read
         */
        export function readDoubleArray(address: number, size: number): number[];
        /**
         * Writes a double Array to an adress
         * @param address The Adress to write the double array to
         * @param value The double array to write
         */
        export function writeDoubleArray(address: number, value: number[]): void;


        /**
         * Allocates a certain amount of memory
         * @param size The size of memory to allocate
         * @returns The address of the memory allocated
         */
        export function alloc(size: number): number;

        /**
         * Frees a certain amount of memory at an address
         * @param address The adress of the memory to free
         * @param size The size of the memory to free
         */
        export function free(address: number, size: number): void;

        /**
         * Protects a chunk of memory
         * @param address Address to start protection on
         * @param protection Type of protection
         * @param size Size of chunk to protect
         */
        export function setProtection(address: number, protection: protection, size: number): void;

        /**
         * Get the protection of an adress
         * @param address The address to get the protection from
         * @returns The protection
         */
        export function getProtection(address: number): protection;
    }

    export namespace asm {
        /**
         * Writes shellcode to an address provided
         * @param address The address to write the shellcode to
         * @param shellcode The shellcode to write in assembly language
         * @returns A boolean indicating wether the shellcode could be interpreted
         */
        export function writeShellcode(address: number, shellcode: string): boolean;
        /**
         * Places a hook at an address provided
         * @param address The address where the hook should be placed
         * @param shellcode The shellcode which should be executed in the hook
         * @returns A boolean indicating wether the shellcode could be interpreted
         */
        export function placeShellcodeHook(address: number, shellcode: string): boolean;
        /**
         * Places a function hook at an address provided
         * @param address The address where the function hook should be placed
         * @param format The format of the arguments ex. "int,string"
         * @param callback The callback which is invoked once the hook is hit 
         */
        export function placeCallbackHook(address: number, format: string, callback: (...params) => void): void;
        /**
         * Places a callback hook at an address provided, while manually giving pro and epilogue
         * @param address The address where the callback hook should be placed
         * @param prologue The prologue
         * @param epilogue The epilogue
         * @param callback The callback which is executed once the hook is hit and the prologue executed ex. let c = (){};
         * @returns A boolean indicating wether the shellcode could be interpreted
         */
        export function placeManualHook(address: number, prologue: string, epilogue: string, callback: () => void): boolean;
        /**
         * Creates a function object to a native function, which can be called later on
         * @param address The address of the function
         * @param callingConvention The calling convention of the function
         * @param returnFormat The return type of the function ex. "none"
         * @param parameterFormat The format in which the arguments are suplied ex. "int,string"
         * @returns A native function object representing the function created
         */
        export function createFunction(address: number, callingConvention: callingConvention, returnFormat: string, parameterFormat: string): nativeFunction;
    }
    export namespace winapi {
        /**
         * Gets all loaded modules of the current process
         * @returns All modules loaded
         */
        export function getModules(): nativeModule[];
        /**
         * Gets a module
         * @param module The module to get
         * @returns The module
         */
        export function getModule(module:string) : nativeModule;
        /**
         * Gets all exports for a module
         * @param module The module to get the exports for
         * @returns All exports of the module
         */
        export function getExports(module:string) : nativeExport[];
        /**
         * Gets an export of a module
         * @param module The module to get the export from
         * @param exportedFunction The name of the export
         * @return The export
         */
        export function getExport(module:string, exportedFunction:string) : nativeExport;
        /**
         * Adds an "VectoredExceptionHandler"
         * @param exceptionHandler A callback to a function taking one parameter ex. let c = (exception) => {}
         */
        export function addExceptionHandler(exceptionHandler : (exception:nativeException) => void) : void;
        /**
         * Removes the "VectoredExceptionHandler"
         * @param exceptionHandler The callback to remove
         */
        export function removeExceptionHandler(exceptionHandler: (exception: nativeException) => void) : void;
        /**
         * int 3;
         */
        export function raiseInterrupt() : void;
    }
    /**
     * Represents a log file
     */
    export namespace file {
        /**
         * Creates a file
         * @param fileName The name of the file to be created
         */
        export function create(fileName: string): void;
        /**
         * Writes a message to the file
         * @param message The message 
         */
        export function write(message:string):void;
    }

    /**
     * Represents an overlay
     */
    export namespace ui {
        /**
         * Creates an DirectX overlay
         * @param renderer The callback in which all rendering has to happen
         */
        export function create(renderer:() => void);
        /**
         * Draws a filled box
         * @param x X Postion
         * @param y Y Postion
         * @param width Width of the box
         * @param heigt Height of the box
         * @param color Color of the box
         */
        export function drawBox(x:number,y:number,width:number,heigt:number,color:color);
        /**
         * Draws a line between two points
         * @param xStart X Starting point
         * @param yStart Y Starting point
         * @param xEnd X Ending point
         * @param yEnd Y Ending point
         * @param thickness Thickness of the line
         * @param color Color of the line
         */
        export function drawLine(xStart:number,yStart:number,xEnd:number,yEnd:number,thickness:number,color:color);
        /**
         * Draws a rectangle
         * @param x X Postion
         * @param y Y Postion
         * @param width Width of the rectangle
         * @param heigt Height of the rectangle
         * @param thickness Thickness of the lines
         * @param color Color of the rectangle
         */
        export function drawRectangle(x: number, y: number, width: number, heigt: number,thickness:number,color: color);
        /**
         * Draws a string
         * @param x X Position
         * @param y Y Position
         * @param size Font size
         * @param color Text color
         * @param text The text to draw
         */
        export function drawText(x:number, y:number, size:number, color:color, text:string);
    }

}

export = global;