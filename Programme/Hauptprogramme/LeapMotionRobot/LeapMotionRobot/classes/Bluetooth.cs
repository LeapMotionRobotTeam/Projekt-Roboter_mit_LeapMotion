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
        private const string ARDUINOPORT = "COM6";

        public SerialPort SerialPortArduino { get; set; }

        public Bluetooth()
        {
            this.SerialPortArduino = new SerialPort(ARDUINOPORT);
            this.SerialPortArduino.BaudRate = 9600;
        }


    }
}
