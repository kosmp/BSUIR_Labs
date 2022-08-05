using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using task2;

namespace task2Test
{
    [TestClass]
    public class task2Test
    {
        [TestMethod]
        public void check_point_position_test()
        {
            if (Program.checkPointPos(40, -40) != 1) Assert.Fail();
            if (Program.checkPointPos(34, -100) != 1) Assert.Fail();
            if (Program.checkPointPos(34, -50) != 2) Assert.Fail();
            if (Program.checkPointPos(50, -49) != 3) Assert.Fail();
        }
    }
}
