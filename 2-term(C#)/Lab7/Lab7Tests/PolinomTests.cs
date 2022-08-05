using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab7;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7.Tests
{
    [TestClass()]
    public class PolinomTests
    {
        [TestMethod()]
        public void ToString_test()
        {
            Polinom polinom1 = new Polinom(1, 2, 3);
            if (polinom1.ToString() != "1x + 2y + 3z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_plus_test()
        {
            Polinom polinom1 = new Polinom(1, 2, 3);
            Polinom polinom2 = new Polinom(5, 7, 9);
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3 = polinom1 + polinom2;
            if (polinom3.ToString() != "6x + 9y + 12z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_minus_test()
        {
            Polinom polinom1 = new Polinom(1, 2, 3);
            Polinom polinom2 = new Polinom(5, 7, 9);
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3 = polinom2 - polinom1;
            if (polinom3.ToString() != "4x + 5y + 6z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_plusplus_test()
        {
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3++;
            if (polinom3.ToString() != "5x + 10y + 7z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_minusminus_test()
        {
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3--;
            if (polinom3.ToString() != "3x + 8y + 5z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_multiply_test()
        {
            Polinom polinom1 = new Polinom(1, 2, 3);
            Polinom polinom2 = new Polinom(5, 7, 9);
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3 = polinom1 * polinom2;
            if (polinom3.ToString() != "5x + 14y + 27z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_multiplyNum_test()
        {
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3 = polinom3 * 2;
            if (polinom3.ToString() != "8x + 18y + 12z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_devideNum_test()
        {
            Polinom polinom3 = new Polinom(4, 9, 6);
            polinom3 = polinom3 / 2;
            if (polinom3.ToString() != "2x + 4y + 3z")
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_equal_test()
        {
            Polinom polinom1 = new Polinom(1, 2, 3);
            Polinom polinom2 = new Polinom(1, 2, 3);
            if (polinom1 != polinom2)
                Assert.Fail();
        }

        [TestMethod()]
        public void operator_boolFalse_test()
        {
            Polinom polinom4 = new Polinom(0, 0, 0);
            if (polinom4)
                Assert.Fail();
        }

        [TestMethod()]
        public void converting_test()
        {
            Polinom polinom = new Polinom(1, 2, 3);
            int x = (int)polinom;
            if (x != 14)
                Assert.Fail();
        }
    }
}