using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSharpChannel
{
    class Program
    {
        static ChannelQueue<int> intChan = new ChannelQueue<int>(10, 0);

        static void Main(string[] args)
        {
            new Thread(writeThreading1).Start();
            new Thread(writeThreading100).Start();
            new Thread(readThreading).Start();
        }

        static void writeThreading1()
        {
            int i = 0;
            while(i < 100)
            {                
                intChan.writeElem(i);
                i++;
            }
        }

        static void writeThreading100()
        {
            int i = 100;
            while (i < 200)
            {
                intChan.writeElem(i);
                i++;
            }
        }

        static void readThreading()
        {
            while (true)
            {
                Console.WriteLine(intChan.readElem());
            }
        }
    }
}
