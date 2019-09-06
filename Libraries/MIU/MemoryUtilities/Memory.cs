using System;

namespace MemoryUtilities
{
    public class Memory
    {
        public int ParentProcessId { get; set; }
        public IntPtr ParentProcessHandle { get; set; }

		public Memory(int parentProcessId)
		{
			ParentProcessId = parentProcessId;
            ParentProcessHandle = WinApi.OpenProcess(WinApi.ProcessAccessFlags.All,false,parentProcessId);
		}

        public Pointer<T> GetPointer<T>(NativeAdress nativeAdress,int size)
            => new Pointer<T>(ParentProcessId, ParentProcessHandle, nativeAdress, size);

        public SingleParameterFunction CreateSingleParameterFunction(NativeAdress nativeAdress)
            => new SingleParameterFunction(ParentProcessId, ParentProcessHandle, nativeAdress);

        public ExportedFunction GetExportedFunction(string module, string function)
            => new ExportedFunction(ParentProcessId, ParentProcessHandle, module, function);
    }
}