using System;

namespace _153501_Kosmin // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        static void Main(string[] args)
        {
            double first, second, res;
            Console.WriteLine("Enter first value: \n");
            first = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Enter second value: \n");
            second = Convert.ToDouble(Console.ReadLine());
            res = first / second;
            Console.WriteLine("Result of division (first / second) = " + res);
        }
    }
}