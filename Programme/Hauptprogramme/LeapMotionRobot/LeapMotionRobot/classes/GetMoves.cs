using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Leap;
using System.Threading;
using LeapMotionRobot.classes;
using System.IO;


namespace LeapMotionRobot
{
    class HandMoves : Listener
    {
        private Object thisLock = new Object();
        Bluetooth bt = new Bluetooth();

        private void SafeWriteLine(String line)
        {
            lock (thisLock)
            {
                Console.WriteLine(line);
            }
        }


        public override void OnInit(Controller controller)
        {
            SafeWriteLine("Initialisiert");

            try
            {
                bt.SerialPortArduino.Open(); // TODO Exception abfangen
            }
            catch (Exception e)
            {
                Console.WriteLine("Fehler bei Bluetooth");
                OnExit(controller);
                System.Environment.Exit(0);
            }
        }
        


        public override void OnConnect(Controller controller)
        {
            controller.EnableGesture(Gesture.GestureType.TYPE_CIRCLE);
            controller.EnableGesture(Gesture.GestureType.TYPE_KEY_TAP);
            controller.EnableGesture(Gesture.GestureType.TYPE_SCREEN_TAP);
            controller.EnableGesture(Gesture.GestureType.TYPE_SWIPE);
            SafeWriteLine("Verbunden");
        }


        public override void OnDisconnect(Controller controller)
        {
            //Note: not dispatched when running in a debugger.
            bt.SerialPortArduino.Close();
            SafeWriteLine("Verbindung getrennt");
        }


        public override void OnExit(Controller controller)
        {
            bt.SerialPortArduino.Close();
            SafeWriteLine("Schließen");
        }



        public override void OnFrame(Controller controller)
        {
            // Get the most recent frame and report some basic information
            Frame frame = controller.Frame();

            SafeWriteLine("Frame id: " + frame.Id
                        + ", timestamp: " + frame.Timestamp
                        + ", hands: " + frame.Hands.Count
                        + ", fingers: " + frame.Fingers.Count);

            foreach (Hand hand in frame.Hands)
            {
                SafeWriteLine("  Hand id: " + hand.Id
                            + ", palm position: " + hand.PalmPosition);
                // Get the hand's normal vector and direction
                Vector normal = hand.PalmNormal;
                Vector direction = hand.Direction;
                double pitch = direction.Pitch * 180.0f / (float)Math.PI;
                double roll = normal.Roll * 180.0f / (float)Math.PI;
                double yaw = direction.Yaw * 180.0f / (float)Math.PI;

                SafeWriteLine("Hand normal vector: " + normal);

                // Calculate the hand's pitch, roll, and yaw angles
                SafeWriteLine("  Beschleunigen (pitch): " + pitch + " degrees, "
                            + "Lenken (roll): " + roll + " degrees, "
                            + "yaw: " + yaw + " degrees");


                // Code erzeugen und über Bluetooth senden
                string code = createCode(pitch, roll);

                try
                {
                    bt.SerialPortArduino.WriteLine(code); // TODO
                }
                catch (IOException e)
                {
                    Console.WriteLine("Fehler: Bluetooth-Device wurde wahrscheinlich entfernt");
                    OnExit(controller);
                    System.Environment.Exit(0);
                }
            }


            // Print an empty line if there is at minimum one hand or one gesture
            if (!frame.Hands.IsEmpty || !frame.Gestures().IsEmpty)
            {
                SafeWriteLine("");
            }

            Thread.Sleep(200);
        }


             /*
             * Hand Neigung vor/zurück:
             * pitch: 0° --> gerade
             * pitch positive Grad --> rückwärts
             * pitch negative Grad --> beschleunigen
             * Maximalwerte:
             * max. Beschleunigung: -50
             * max. Rückwärts: 50
             * 
             * Hand Neigung seitlich:
             * roll 0° --> gerade
             * roll positive Grad --> links lenken
             * roll negative Grad --> rechts lenken 
             * Maximalwerte:
             * max. links: 50
             * max. rechts: -50 
             * 
             * Toleranzbereich um Nullpunkt:
             * pitch: -10 bis 10 --> gilt als 0 --> keine Aktion
             * roll: -12 bis 12 --> gilt als 0 --> keine Aktion 
             * 
             * 
             * Codebeispiele:
             * A200B100 --> max. Geschwindigkeit
             * A100B100 --> keine Aktion
             * A0B100 --> max. Rückwärts
             * A100B0 --> max. Links, jedoch keine Geschwindigkeit
             * A100B200 --> max. Rechts, jedoch keine Geschwindigkeit
             * 
             * */
        private string createCode(double pitch, double roll)
        {
            int acceleration = 0; // Erster Teil des Codes, vor dem Trennzeichen
            int steering; // Zweiter Teil des Codes, nach dem Trennzeichen 
            string code; //Zu sendender Code 
            int tolerancePitch = 10; //Toleranz um den Nullbereich des pitch-Wertes, exclusiv
            int toleranceRoll = 12; //Toleranz um den Nullbereich des roll-Wertes, exclusiv
            int maxPitch = 50; // Maximale Neigung der Hand --> Alles über dieser Neigung wird als 100% gerechnet 
            int maxRoll = 50;

            Console.WriteLine("pitch: " + pitch);
            Console.WriteLine("roll: " + roll);

            pitch = pitch * (-1);
            // Wert von pitch ist außerhalb der Nullzone = Toleranzzone
            if (pitch < (tolerancePitch * (-1)) || (pitch > tolerancePitch))
            {
                // Wert von pitch liegt innerhalb der maximalen Grenzen
                if (pitch > (maxPitch * (-1)) && pitch < maxPitch)
                {
                    double pitchWithoutTolerance;

                    // Abziehen der Toleranz, damit 255-80gesamter Prozentbereich ausgeschöpft wird (nur int-Werte) 
                    if (pitch < 0)
                        pitchWithoutTolerance = pitch + tolerancePitch;
                    else
                        pitchWithoutTolerance = pitch - tolerancePitch;

                   // Console.WriteLine("pitchWithoutTolerance: " + pitchWithoutTolerance);

                    // Division durch maximalen Wert abzüglich der Toleranz, damit gesamter Prozentbereich ausgeschöpft wird (nur int-Werte)  
                    acceleration = (int)((pitchWithoutTolerance / (maxPitch - tolerancePitch) * (100)) + 100);

                   // Console.WriteLine("acceleration: " + acceleration);

                } else if (pitch >= maxPitch)
                    acceleration = 200;
                else if(pitch < (maxPitch * (-1)))
                    acceleration = 0;
            }
            else //Wert ist innerhalb der Nullzone 
                acceleration = 100;


            // Wert von roll ist außerhalb der Nullzone = Toleranzzone 
            roll = roll * (-1);
            if (roll < (toleranceRoll * (-1)) || roll > toleranceRoll)
            {
                if (roll > (maxRoll * (-1)) && (roll < (maxRoll)))
                {
                    double rollWithoutTolerance;

                    //Abziehen der Toleranz des roll-Wertes, um den gesamten Prozentbereich auszuschöpfen (nur int-Werte) 
                    if (roll < 0)
                        rollWithoutTolerance = roll + toleranceRoll;
                    else
                        rollWithoutTolerance = roll - toleranceRoll;
                        
                    // Division durch maximalen Wert abzüglich der Toleranz, damit gesamter Prozentbereich ausgeschöpft wird (nur int-Werte)
                    steering = (int)((rollWithoutTolerance / (maxRoll - toleranceRoll) * 100) + 100);
                }
                else if (roll >= maxRoll)
                    steering = 200;
                else
                    steering = 0;
            }
            else
                steering = 100;


            //Zusammensetzen des zu sendenden Codes
            code = "A" + acceleration + ".0" + "B" + steering + ".0";
            Console.WriteLine("Code: " + code);

            return code;
        }
    }
}