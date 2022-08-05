using Microsoft.VisualStudio.TestTools.UnitTesting;
using task1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task1.Tests
{
    [TestClass()]
    public class Class1Tests
    {
        [TestMethod()]
        public void powSq_Test_20()
        {
            if (Class1.powSq(20) != 400)
                Assert.Fail();
        }
        [TestMethod()]
        public void powSq_Test_minus_2()
        {
            if (Class1.powSq(-2) != 4)
                Assert.Fail();
        }
    }
}