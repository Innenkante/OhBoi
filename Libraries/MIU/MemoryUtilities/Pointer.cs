using System;

namespace MemoryUtilities
{
    public class Pointer<T> : IMemoryInteraction
    {
        public int ParentProcessId { get; set; }
        public IntPtr ParentProcessHandle { get; set; }
        public NativeAdress Adress { get; set; }
        public int Size { get; set; }

        public Pointer(int parentProcessId, IntPtr parentProcessHandle, NativeAdress adress, int size)
        {
            ParentProcessId = parentProcessId;
            ParentProcessHandle = parentProcessHandle;
            Adress = adress;
            Size = size;
        }

        public T GetValue()
        {
            byte[] bufferToReadIn = new byte[Size];
            WinApi.ReadProcessMemory(ParentProcessHandle, Adress, bufferToReadIn, Size, out IntPtr bytesRead);
            return new TypeParser<T>().ToType(bufferToReadIn);
        }

        public void SetValue(T value)
            => WinApi.WriteProcessMemory(ParentProcessHandle, Adress, new TypeParser<T>().ToByteArray(value), Size, out IntPtr bytesWritten);
    }
}