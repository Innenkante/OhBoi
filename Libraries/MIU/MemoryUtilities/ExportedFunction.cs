using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
namespace MemoryUtilities
{
    public class ExportedFunction : IMemoryInteraction
    {
        public int ParentProcessId { get; set; }
        public IntPtr ParentProcessHandle { get; set; }
        public string Module { get; set; }
        public string Function { get; set; }

        public ExportedFunction(int parentProcessId, IntPtr parentProcessHandle, string module, string function)
        {
            ParentProcessId = parentProcessId;
            ParentProcessHandle = parentProcessHandle;
            Module = module;
            Function = function;
        }

        private class ModuleInformation
        {
            public string Path { get; set; }
            public IntPtr BaseAdress { get; set; }
            public IntPtr EntryPoint { get; set; }
            public int Size { get; set; }

            public static ModuleInformation InitializeFromHandle(IntPtr processHandle,IntPtr moduleHandle)
            {
                WinApi.GetModuleInformation(processHandle, moduleHandle, out WinApi.MODULEINFO moduleInfo, Marshal.SizeOf(typeof(WinApi.MODULEINFO)));
                StringBuilder stringBuilder = new StringBuilder(1024);
                WinApi.GetModuleFileNameEx(processHandle, moduleHandle, stringBuilder, stringBuilder.Capacity);
                return new ModuleInformation()
                {
                    Path = stringBuilder.ToString(),
                    BaseAdress = moduleInfo.BaseAdress,
                    EntryPoint = moduleInfo.EntryPoint,
                    Size = (int)moduleInfo.Size
                };
                
            }
        }

        public class NativeFunction
        {
            public string Name { get; set; }
            public IntPtr Address { get; set; }
            public short Id { get; set; }
        }

        private class NativeImage
        {
            public ModuleInformation ModuleInformation { get; set; }
            public WinApi.IMAGE_DOS_HEADER DosHeader { get; set; }
            public WinApi.IMAGE_NT_HEADERS NtHeader { get; set; }
            public WinApi.IMAGE_EXPORT_DIRECTORY ExportDirectory { get; set; }


        }
      

        private List<ModuleInformation> GetModuleInfos()
        {
            IntPtr[] moduleHandles = new IntPtr[1024];

            WinApi.EnumProcessModules(ParentProcessHandle, moduleHandles, Marshal.SizeOf(typeof(IntPtr)) * moduleHandles.Length, out var needed);

            List<ModuleInformation> moduleInfos= new List<ModuleInformation>();

            for (int i = 0; i < moduleHandles.Length; i++)
                if (moduleHandles[i] != IntPtr.Zero)
                    moduleInfos.Add(ModuleInformation.InitializeFromHandle(ParentProcessHandle, moduleHandles[i]));

            return moduleInfos;
        }

        private List<NativeImage> GetNativeImages(List<ModuleInformation> modules)
        {
            List<NativeImage> nativeImages = new List<NativeImage>();
            foreach(var module in modules.Where(m => Path.GetFileName(m.Path) == Module))
            {
                NativeImage nativeImage = new NativeImage();
                nativeImage.ModuleInformation = module;
                nativeImage.DosHeader = new Pointer<WinApi.IMAGE_DOS_HEADER>(ParentProcessId, ParentProcessHandle, module.BaseAdress, Marshal.SizeOf(typeof(WinApi.IMAGE_DOS_HEADER))).GetValue();
                nativeImage.NtHeader = new Pointer<WinApi.IMAGE_NT_HEADERS>(ParentProcessId, ParentProcessHandle, module.BaseAdress + nativeImage.DosHeader.e_lfanew, Marshal.SizeOf(typeof(WinApi.IMAGE_NT_HEADERS))).GetValue();
                nativeImage.ExportDirectory = new Pointer<WinApi.IMAGE_EXPORT_DIRECTORY>(ParentProcessId, ParentProcessHandle, module.BaseAdress + (int)nativeImage.NtHeader.OptionalHeader.ExportTable.VirtualAddress,Marshal.SizeOf(typeof(WinApi.IMAGE_EXPORT_DIRECTORY))).GetValue();

                nativeImages.Add(nativeImage);
            }
            return nativeImages;
        }

        private NativeFunction GetNativeFunction(List<NativeImage> images)
        {
            List<NativeFunction> functions = new List<NativeFunction>();
            foreach(var image in images)
            {
                var moduleBase = image.ModuleInformation.BaseAdress;
                var adressOfFunctions = moduleBase + (int)image.ExportDirectory.AddressOfFunctions;
                var adressOfNames = moduleBase + (int)image.ExportDirectory.AddressOfNames;
                var adressOfOrdinals = moduleBase + (int)image.ExportDirectory.AddressOfNameOrdinals;
                var numberOfNames = image.ExportDirectory.NumberOfNames;
                for(int i = 0; i < numberOfNames; i++)
                {
                    NativeFunction nativeFunction = new NativeFunction();
                    var adressOfString = new Pointer<int>(ParentProcessId, ParentProcessHandle, adressOfNames + (i * Marshal.SizeOf(typeof(int))), Marshal.SizeOf(typeof(int))).GetValue();
                    nativeFunction.Name = new Pointer<string>(ParentProcessId, ParentProcessHandle, moduleBase + adressOfString, Function.Length).GetValue();


                    nativeFunction.Id = new Pointer<short>(ParentProcessId, ParentProcessHandle, adressOfOrdinals + (i * Marshal.SizeOf(typeof(short))), Marshal.SizeOf(typeof(short))).GetValue();

                    var adressOfFunction = new Pointer<int>(ParentProcessId, ParentProcessHandle, adressOfFunctions + (nativeFunction.Id * Marshal.SizeOf(typeof(int))), Marshal.SizeOf(typeof(int))).GetValue();
                    nativeFunction.Address = moduleBase + adressOfFunction;

                    if(nativeFunction.Name == Function)
                        functions.Add(nativeFunction);
                }
            }
            return functions[0];
        }

        
        public NativeFunction GetFunction()
        {
            return GetNativeFunction(GetNativeImages(GetModuleInfos()));
        }
    }
}
