using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LeapMotionRobot.classes
{
    class Bluetooth
    {
        public SerialPort SerialPortArduino { get; set; }

        public Bluetooth()
        {
            bool portOk = false;

            while (!portOk)
            {
                string choosedPort = chooseComPort(); // Auswählen des gewünschten Ports 

                try
                {
                    this.SerialPortArduino = new SerialPort(choosedPort);
                    portOk = true;
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine("Ungültige Eingabe");
                }

            }

            this.SerialPortArduino.BaudRate = 9600;
        }

        /*
         * Alle verfügbaren Com-Ports werden aufgelistet, 
         * Benutzer kann den zu verwendenden Port auswählen 
         * */
        private static string chooseComPort()
        {
            string[] serialPorts = SerialPort.GetPortNames();

            foreach (string s in serialPorts)
            {
                Console.WriteLine(s);
            }

            Console.Write("Bitte gewünschten Port eingeben: ");
            string choosedPort = Console.ReadLine();
            choosedPort = choosedPort.ToUpper();
            choosedPort = choosedPort.Trim();
            Console.WriteLine("Gewählter Port: " + choosedPort);
            return choosedPort;
        }


    }
}
