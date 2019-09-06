using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MemoryUtilities
{
    public abstract class Function : IMemoryInteraction
    {
        public int ParentProcessId { get; set; }
        public IntPtr ParentProcessHandle { get; set; }

        public NativeAdress Adress { get; set; }

        public Function(int parentProcessId, IntPtr parentProcessHandle, NativeAdress adress)
        {
            ParentProcessId = parentProcessId;
            ParentProcessHandle = parentProcessHandle;
            Adress = adress;
        }
    }

    public class SingleParameterFunction : Function
    {
        public SingleParameterFunction(int parentProcessId, IntPtr parentProcessHandle, NativeAdress adress) : base(parentProcessId, parentProcessHandle, adress)
        {
        }

        public IntPtr Call()
        {
            return WinApi.CreateRemoteThread(ParentProcessHandle, IntPtr.Zero, 0, Adress, IntPtr.Zero, 0, out IntPtr threadId);
        }

        public IntPtr Call<T>(T parameter)
        {
            byte[] parameterAsByteArray = new TypeParser<T>().ToByteArray(parameter);
            var parameterLocation = WinApi.VirtualAllocEx(ParentProcessHandle, IntPtr.Zero, parameterAsByteArray.Length, WinApi.AllocationType.Commit, WinApi.MemoryProtection.ExecuteReadWrite);
            new Pointer<byte[]>(ParentProcessId, ParentProcessHandle, parameterLocation, parameterAsByteArray.Length).SetValue(parameterAsByteArray);

            return WinApi.CreateRemoteThread(ParentProcessHandle, IntPtr.Zero, 0, Adress, parameterLocation, 0, out IntPtr threadId);
        }


    }
}
