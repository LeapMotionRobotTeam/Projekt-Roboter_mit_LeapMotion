using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Leap;
using System.IO.Ports;


namespace LeapMotionRobot
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Programm gestartet");

            // Erzeugen eines neuen LeapMotion-Controllers 
            HandMoves handMoves = new HandMoves(); // Dieses Objekt wird in weiterer Folge als Listener dem Controller übergeben 
            Controller controller = new Controller();

            // Controller soll auf Handbewegungen horchen 
            controller.AddListener(handMoves);
            
            Console.WriteLine("Beliebige Taste drücken zum Beenden des Programms");
            Console.ReadKey();

            // Bereinigung durchführen am Ende des Programms 
            controller.RemoveListener(handMoves);
            controller.Dispose();
        }
    }
}
