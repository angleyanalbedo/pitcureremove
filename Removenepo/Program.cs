using Memory;
using System.Diagnostics;

namespace Removenepo
{
    internal class Program
    {
        static void Main(string[] args)
        {

            while (Process.GetProcessesByName("GenshinImpact").Length<=0)
            {
                Thread.Sleep(1000);
            }
            Process process = Process.GetProcessesByName("GenshinImpact")[0];
            ProcessModule processModule;
            ProcessModuleCollection processModuleCollection = process.Modules;
            for (int i = 0; i < processModuleCollection.Count; i++)
            {
                processModule = processModuleCollection[i];
                if (processModule.ModuleName == "CLibrary.dll")
                {
                    IntPtr baseaddr = processModule.BaseAddress;
                    Mem mem = new Mem();
                    if (!mem.OpenProcess("GenshinImpact"))
                    {
                        Console.WriteLine("shibai");
                    }
                    int value = mem.ReadInt("CLibrary.dll+395F68");
                    Console.WriteLine("value的只是"+value);
                    if (value != 256)
                    {
                        mem.WriteMemory("CLibrary.dll+395F68", "int", "256");
                    }

                    Console.WriteLine("the address is " + baseaddr);
                }
            }

        }
    }
}