using System;

namespace task3
{
    public class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(DateService.GetDay("01.04.2022"));
            Console.WriteLine(DateService.GetDaysSpan(02, 05, 2022));
        }
    }
}
