using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MemoryUtilities
{
    public class EntryPoint : IMemoryInteraction
    {
        public int ParentProcessId { get; set; }
        public IntPtr ParentProcessHandle { get; set; }

        private IntPtr _peb; 


        private IntPtr GetPEB(IntPtr handle)
        {
            WinApi.PROCESS_BASIC_INFORMATION pbi = new WinApi.PROCESS_BASIC_INFORMATION();

            IntPtr outPtr = IntPtr.Zero;

            int queryStatus = 0;

            queryStatus = WinApi.NtQueryInformationProcess(handle, 0, ref pbi, Marshal.SizeOf(typeof(WinApi.PROCESS_BASIC_INFORMATION)), out int size);


            if (queryStatus == 0)
                outPtr = pbi.PebBaseAddress;

            return outPtr;
        }

        public EntryPoint(int processId)
        {
            ParentProcessId = processId;
            ParentProcessHandle = WinApi.OpenProcess(WinApi.ProcessAccessFlags.All, false, processId);


            _peb = GetPEB(ParentProcessHandle);
        }

        public int Get()
        {
            var processBase = new Pointer<int>(ParentProcessId, ParentProcessHandle, _peb + 0x8, 4).GetValue();

            var dosHeader = new Pointer<WinApi.IMAGE_DOS_HEADER>(ParentProcessId, ParentProcessHandle, processBase, Marshal.SizeOf(typeof(WinApi.IMAGE_DOS_HEADER))).GetValue();
            var ntHeader = new Pointer<WinApi.IMAGE_NT_HEADERS>(ParentProcessId, ParentProcessHandle, processBase + dosHeader.e_lfanew, Marshal.SizeOf(typeof(WinApi.IMAGE_NT_HEADERS))).GetValue();


            return processBase + (int)ntHeader.OptionalHeader.AddressOfEntryPoint;
        }

        //public void Set(IntPtr address)
        //{
        //    var processBase = new Pointer<int>(ParentProcessId, ParentProcessHandle, _peb + 0x8, 4).GetValue();

        //    var dosHeader = new Pointer<WinApi.IMAGE_DOS_HEADER>(ParentProcessId, ParentProcessHandle, processBase, Marshal.SizeOf(typeof(WinApi.IMAGE_DOS_HEADER))).GetValue();
        //    var ntHeaderStart = processBase + dosHeader.e_lfanew;
        //    var optionalHeaderStart = ntHeaderStart + 0x18;
        //    var entryPoint = optionalHeaderStart + 0x10;

        //    WinApi.VirtualProtectEx(ParentProcessHandle, new IntPtr(entryPoint), 4, WinApi.MemoryProtection.ReadWrite, out var old);
            
        //    new Pointer<IntPtr>(ParentProcessId, ParentProcessHandle, entryPoint, 4).SetValue(address);

        //    WinApi.VirtualProtectEx(ParentProcessHandle, new IntPtr(entryPoint), 4, old, out var old2);
        //}
    }
}
