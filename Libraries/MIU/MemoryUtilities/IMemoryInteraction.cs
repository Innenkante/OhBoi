using System;

namespace MemoryUtilities
{
    interface IMemoryInteraction
    {
        int ParentProcessId { get; set; }
        IntPtr ParentProcessHandle {get; set; }
    }
}