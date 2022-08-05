using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    public class Polinom
    {
        public Polinom(int _a, int _b, int _c)
        {
            a = _a;
            b = _b;
            c = _c;
        }

        public Polinom()
        {
            a = 1;
            b = 2;
            c = 3;
        }

        public int Value_a { get; set; }
        public int Value_b { get; set; }
        public int Value_c { get; set; }

        private int a, b, c;

        public static Polinom operator +(Polinom polinom1, Polinom polinom2)
        {
            return new Polinom(polinom1.a + polinom2.a, polinom1.b + polinom2.b, polinom1.c + polinom2.c);
        }

        public static Polinom operator -(Polinom polinom1, Polinom polinom2)
        {
            return new Polinom(polinom1.a - polinom2.a, polinom1.b - polinom2.b, polinom1.c - polinom2.c);
        }

        public static Polinom operator ++(Polinom polinom1)
        {
            return new Polinom(polinom1.a + 1, polinom1.b + 1, polinom1.c + 1);
        }

        public static Polinom operator --(Polinom polinom1)
        {
            return new Polinom(polinom1.a - 1, polinom1.b - 1, polinom1.c - 1);
        }

        public static Polinom operator *(Polinom polinom1, Polinom polinom2)
        {
            return new Polinom (polinom1.a * polinom2.a, polinom1.b * polinom2.b, polinom1.c * polinom2.c);
        }

        public static Polinom operator *(Polinom polinom1, int num)
        {
            return new Polinom(polinom1.a * num, polinom1.b * num, polinom1.c * num);
        }

        public static Polinom operator /(Polinom polinom1, int num)
        {
            return new Polinom(polinom1.a / num, polinom1.b / num, polinom1.c / num);
        }

        public static bool operator ==(Polinom polinom1, Polinom polinom2)
        {
            return polinom1.a == polinom2.a && polinom1.b == polinom2.b && polinom1.c == polinom2.c;
        }

        public static bool operator !=(Polinom polinom1, Polinom polinom2)
        {
            return polinom1.a != polinom2.a || polinom1.b != polinom2.b || polinom1.c != polinom2.c;
        }

        public static bool operator false(Polinom polinom1)
        {
           return polinom1.a == polinom1.b && polinom1.b == polinom1.c && polinom1.a == 0;
        }

        public static bool operator true(Polinom polinom1)
        {
            return !(polinom1.a == polinom1.b && polinom1.b == polinom1.c && polinom1.a == 0);
        }

        public override string ToString()
        {
            return a + "x + " + b + "y + " + c + "z";  
        }

        public static explicit operator int(Polinom polinom)
        {
            return Convert.ToInt16(Math.Pow(polinom.a, 2)) + Convert.ToInt16(Math.Pow(polinom.b, 2)) + Convert.ToInt16(Math.Pow(polinom.c, 2));
        }

        public static explicit operator Polinom(int x)
        {
            return new Polinom(x, 0, 0);
        }
    }
}
