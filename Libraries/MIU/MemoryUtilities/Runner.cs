using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MemoryUtilities
{
    public class Runner
    {
        private string _programToRun;
        private IntPtr _handle;

        public Runner(string programToRun)
        {
            _programToRun = programToRun;
        }

        public int RunProcess(string arguments)
        {
            WinApi.SECURITY_ATTRIBUTES processSecurityAttributes = new WinApi.SECURITY_ATTRIBUTES();
            WinApi.SECURITY_ATTRIBUTES threadSecurityAttributes = new WinApi.SECURITY_ATTRIBUTES();

            processSecurityAttributes.nLength = Marshal.SizeOf(processSecurityAttributes);
            threadSecurityAttributes.nLength = Marshal.SizeOf(threadSecurityAttributes);

            WinApi.STARTUPINFO startupInfo = new WinApi.STARTUPINFO();

            WinApi.PROCESS_INFORMATION processInformation = new WinApi.PROCESS_INFORMATION();

            System.IO.Directory.SetCurrentDirectory(System.IO.Path.GetDirectoryName(_programToRun));

            WinApi.CreateProcessA(_programToRun, arguments, ref processSecurityAttributes, ref threadSecurityAttributes, false, 0, IntPtr.Zero, null, ref startupInfo, out processInformation);

            _handle = processInformation.hProcess;

            return processInformation.dwProcessId;
        }

        public int RunProcessSuspended(string arguments)
        {
            WinApi.SECURITY_ATTRIBUTES processSecurityAttributes = new WinApi.SECURITY_ATTRIBUTES();
            WinApi.SECURITY_ATTRIBUTES threadSecurityAttributes = new WinApi.SECURITY_ATTRIBUTES();

            

            WinApi.STARTUPINFO startupInfo = new WinApi.STARTUPINFO();
            WinApi.PROCESS_INFORMATION processInformation = new WinApi.PROCESS_INFORMATION();

            System.IO.Directory.SetCurrentDirectory(System.IO.Path.GetDirectoryName(_programToRun));

            WinApi.CreateProcessA(_programToRun, arguments, ref processSecurityAttributes, ref threadSecurityAttributes, false, WinApi.CreateProcessFlags.CREATE_SUSPENDED, IntPtr.Zero, null, ref startupInfo, out processInformation);

            _handle = processInformation.hProcess;

            return processInformation.dwProcessId;
        }

        public void ResumeProcess()
        {
            WinApi.NtResumeProcess(_handle);
        }

        public IntPtr GetProcessHandle()
        {
            return _handle;
        }

    }
}
