using System;
using System.Runtime.InteropServices;

namespace SimpleConsole 
{
    public static class Test 
    {
        [UnmanagedCallersOnly]
        public static void Write()
        {
            Console.WriteLine("Called from Native");
        }
    }
}
