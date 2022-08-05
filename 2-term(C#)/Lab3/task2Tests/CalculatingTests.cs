using Microsoft.VisualStudio.TestTools.UnitTesting;
using task2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2.Tests
{
    [TestClass()]
    public class CalculatingTests
    {
        [TestMethod()]
        public void powSq_test_10()
        {
            if (Calculating.powSq(10) != 100)
                Assert.Fail();
        }

        [TestMethod()]
        public void calcY_test()
        {
            if (Calculating.calculateY(1, 1) < 0.029)
                Assert.Fail();
        }
    }
}