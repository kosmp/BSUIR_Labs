// variant 8
using System;

namespace task1
{
    public class Program
    {
        public static string enterNum()
        {
            bool first = false;
            int number = 0;
            string sNumber;
            do
            {
                if (first) Console.WriteLine("Incorrect double number.");
                Console.WriteLine("Enter a double number: ");
                sNumber = Console.ReadLine();
                if (sNumber.Length != 2 || sNumber[0] > 57 || sNumber[0] < 48 || sNumber[1] > 57 || sNumber[1] < 48)
                {
                    first = true;
                    continue;
                }
                number = int.Parse(sNumber);
            } while (number > 99 || number < 10);
            return sNumber;
        }

        public static bool checkEven(string sNumber)
        {
            switch ((Convert.ToInt32(sNumber[0]) + Convert.ToInt32(sNumber[1])) % 2)
            {
                case 0:
                    Console.WriteLine("The sum of digits is even.");
                    return true;
                default:
                    Console.WriteLine("The sum of digits isn't even.");
                    return false;
            }
        }

        static void Main(string[] args)
        {
            string op;
            do
            {
                string sNumber = enterNum();
                checkEven(sNumber);
                do
                {
                    Console.WriteLine("Press 'y' to continue or 'n' to stop.");
                    op = Console.ReadLine();
                } while (op.Length != 1 || (op[0] != 'y' && op[0] != 'n'));
            } while (op[0] == 'y');
        }
    }
}
