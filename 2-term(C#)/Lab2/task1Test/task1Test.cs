using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using task1;

namespace task1Test
{
    [TestClass]
    public class task1Test
    {
        [TestMethod]
        public void check_even_number()
        {
            if(Program.checkEven("43")) Assert.Fail();
            if (!Program.checkEven("99")) Assert.Fail();
        }
    }
}
