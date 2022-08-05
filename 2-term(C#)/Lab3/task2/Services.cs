using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2
{
    public class Calculating
    {
       public static int powSq(int n)
       {
            return n * n;
       }
       public static double calculateY(int k, int z)
       {
            if (k < 1)
            {
                double y;
                Console.WriteLine("k < 1");
                int x = k * (int)Math.Pow(z, 3);
                y = Math.Pow(Math.Log(1 + powSq(x)) + Math.Cos(x+1), Math.Pow(Math.E, k * x));        
                Console.WriteLine(y);
                return y;
            }
            else
            {
                double y;
                Console.WriteLine("k >= 1");
                int x = z * (z + 1);
                y = Math.Pow(Math.Log(1 + powSq(x)) + Math.Cos(x + 1), Math.Pow(Math.E, k * x));
                Console.WriteLine(y);
                return y;
            }
       }
    }
}
