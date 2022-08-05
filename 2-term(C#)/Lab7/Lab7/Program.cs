using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    public class Program
    {
        static void Main(string[] args)
        {
            Polinom polinom = new Polinom(3, 4, 5);
            Console.WriteLine(polinom.ToString());
            int x = (int)polinom;
            Console.WriteLine(x);

            Polinom newPolinom = new Polinom(1, 2, 3);
            newPolinom = (Polinom)x;
            Console.WriteLine(newPolinom.ToString());

            Polinom polinom1 = new Polinom(1, 2, 3);
            Polinom polinom2 = new Polinom(5, 7, 9);
            Polinom polinom3 = new Polinom(4, 9, 6);
            Console.WriteLine("pol1:  " + polinom1.ToString());
            Console.WriteLine("pol2:  " + polinom2.ToString());

            polinom3 = polinom1 + polinom2;
            Console.WriteLine("pol1 + pol2:  " + polinom3.ToString());

            polinom3 = polinom2 - polinom1;
            Console.WriteLine("pol2 - pol1:  " + polinom3.ToString());

            polinom3++;
            Console.WriteLine("pol3++:  " + polinom3.ToString());

            polinom3--;
            Console.WriteLine("pol3--:  " + polinom3.ToString());

            polinom3 = polinom1 * polinom2;
            Console.WriteLine("pol1 * pol2:  " + polinom3.ToString());

            polinom3 = polinom1 * 4;
            Console.WriteLine("pol1 * 4:  " + polinom3.ToString());

            polinom3 = polinom2 / 4;
            Console.WriteLine("pol2 / 4:  " + polinom3.ToString());

            if (polinom1 == polinom2)
                Console.WriteLine("pol1 == pol2");
            else
                Console.WriteLine("pol1 != pol2");

            if (polinom1)
             Console.WriteLine("polinom1 = true");
            else
             Console.WriteLine("polinom1 = false");

            Polinom polinom4 = new Polinom(0, 0, 0);
            Console.WriteLine("pol4:  " + polinom4.ToString());
            if (polinom4)
                Console.WriteLine("polinom4 = true");
            else
                Console.WriteLine("polinom4 = false");
        }
    }
}
