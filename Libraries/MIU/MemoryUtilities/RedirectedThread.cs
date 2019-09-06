using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MemoryUtilities
{
    public class RedirectedThread
    {
        private IntPtr _threadToRedirect;
        private IntPtr _processHandle;
        private IntPtr _shellcodeMemory;
        private byte[] _startShellcode;
        private byte[] _endShellcode;
        private WinApi.CONTEXT _context = new WinApi.CONTEXT();

        public RedirectedThread(IntPtr processHandle,int threadId)
        {
            _processHandle = processHandle;
            _threadToRedirect = WinApi.OpenThread(WinApi.ThreadAccessFlags.SET_CONTEXT | WinApi.ThreadAccessFlags.GET_CONTEXT | WinApi.ThreadAccessFlags.SUSPEND_RESUME,false,(uint)threadId);
            _shellcodeMemory = WinApi.VirtualAllocEx(_processHandle, IntPtr.Zero, 1024, WinApi.AllocationType.Commit, WinApi.MemoryProtection.ExecuteReadWrite);
        }

        public void Initialize()
        {
            _context.ContextFlags = WinApi.CONTEXT_FLAGS.CONTEXT_ALL;

            WinApi.GetThreadContext(_threadToRedirect, ref _context);

            var oldEip = _context.Eip;

            var pushEip = new byte[] { 0x68 }.Concat(BitConverter.GetBytes(oldEip)).ToArray();
            var saveRegisters = new byte[] { 0x60, 0x9C };
            _startShellcode = pushEip.Concat(saveRegisters).ToArray();

            var restoreRegisters = new byte[] { 0x9D, 0x61 };
            var ret = new byte[] { 0xC3 };
            _endShellcode = restoreRegisters.Concat(ret).ToArray();
        }

        public IntPtr GetShellcodeStartAddress()
        {
            return _shellcodeMemory + _startShellcode.Count();
        }

        public void ExecuteShellcode(byte[] shellcode)
        {
            WinApi.WriteProcessMemory(_processHandle, _shellcodeMemory, _startShellcode, _startShellcode.Count(), out var _1);
            WinApi.WriteProcessMemory(_processHandle, _shellcodeMemory + _startShellcode.Count(), shellcode, shellcode.Count(), out var _2);
            WinApi.WriteProcessMemory(_processHandle, _shellcodeMemory + _startShellcode.Count() + shellcode.Count(), _endShellcode, _endShellcode.Count(), out var _3);


            _context.Eip = (uint)_shellcodeMemory;

            WinApi.SetThreadContext(_threadToRedirect, ref _context);
        }
    }
}
