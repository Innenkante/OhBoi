using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace MemoryUtilities
{
    public static class ProcessExtender
    {
        public static Memory GetMemory(this Process process)
            => new Memory(process.Id); 
    }
}
