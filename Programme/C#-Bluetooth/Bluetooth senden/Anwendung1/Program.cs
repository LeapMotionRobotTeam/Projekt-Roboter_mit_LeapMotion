using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Anwendung1.classes;
using System.Threading;

namespace Anwendung1
{
    class Program
    {
        static void Main(string[] args)
        {
            Bluetooth bt = new Bluetooth();
            bt.SerialPortArduino.Open();

            for (int i = 0; i < 10; i++)
            {
                
                bt.SerialPortArduino.WriteLine("A90.0B45.0");
                Thread.Sleep(3000);
                bt.SerialPortArduino.WriteLine("A80.0B23.0");
                Thread.Sleep(3000);
                bt.SerialPortArduino.WriteLine("A0.0B197.0");
                Thread.Sleep(3000);
                bt.SerialPortArduino.WriteLine("A199.0B169.0");
                Thread.Sleep(3000);
                /*
                bt.SerialPortArduino.WriteLine("11111");
                Thread.Sleep(3000);
                bt.SerialPortArduino.WriteLine("000");
                Thread.Sleep(5000);
                bt.SerialPortArduino.WriteLine("1111");
                Thread.Sleep(1000);
                bt.SerialPortArduino.WriteLine("00");
                Thread.Sleep(3000);
                 */
            }
            bt.SerialPortArduino.Close();
        }
    }
}
