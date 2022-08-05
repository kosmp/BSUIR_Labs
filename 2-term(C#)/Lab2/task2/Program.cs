// variant 11
using System;

namespace task2
{
    public class Program
    {
        public static int checkPointPos(int x, int y)
        {
            if (((y == x || y == -x) && y <= 0 && y >= -100) || (y == -100 && x >= -100 && x <= 100))
            {
                Console.WriteLine("Point is on the border.");
                return 1;   // for test
            }
            else if (y > -100 && y < 0 && x > y && x < -y)
            {
                Console.WriteLine("Yes");
                return 2;   // for test
            }  
            else
            {
                Console.WriteLine("No");
                return 3;   // for test
            }   
        }

        static void Main(string[] args)
        {
            string op;
            do
            {
                int x = 0, y = 0;
                bool check = false;
                do
                {
                    switch (check)
                    {
                        case true:
                            Console.WriteLine("You entered smth incorrect.");
                            break;
                        default:
                            break;
                    }
                    check = false;
                    Console.WriteLine("Enter point coordinates.");
                    Console.WriteLine("Enter x(is integer):");
                    try
                    {
                        x = int.Parse(Console.ReadLine());
                    }
                    catch (FormatException)
                    {
                        check = true;
                        continue;
                    }
                    Console.WriteLine("Enter y(is integer):");
                    try
                    {
                        y = int.Parse(Console.ReadLine());
                    }
                    catch (FormatException)
                    {
                        check = true;
                        continue;
                    }
                } while (check);
                Console.WriteLine("Is point inside of figure?");
                checkPointPos(x, y);
                do
                {
                    Console.WriteLine("Press 'y' to continue or 'n' to stop.");
                    op = Console.ReadLine();
                } while (op.Length != 1 || (op[0] != 'y' && op[0] != 'n'));
            } while (op[0] == 'y');
        }
    }
}