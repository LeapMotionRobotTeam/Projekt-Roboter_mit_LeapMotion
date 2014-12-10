using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Leap;


namespace LeapMotionRobot
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Program start");

            // Create a sample listener and controller
            HandMoves handMoves = new HandMoves();
            Controller controller = new Controller();

            // Have the sample listener receive events from the controller
            controller.AddListener(handMoves);

            Console.WriteLine("Press any key to quit");
            Console.ReadKey();

            // Remove the sample listener when done
            controller.RemoveListener(handMoves);
            controller.Dispose();
        }
    }
}
