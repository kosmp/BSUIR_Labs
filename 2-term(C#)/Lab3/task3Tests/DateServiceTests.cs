using Microsoft.VisualStudio.TestTools.UnitTesting;
using task3;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task3.Tests
{
    [TestClass()]
    public class DateServiceTests
    {
        [TestMethod()]
        public void GetDaytest_test_Friday()
        {
            if (DateService.GetDay("01.04.2022") != "Friday")
                Assert.Fail();
        }

        [TestMethod()]
        public void GetDaytest_test_Monday()
        {
            if (DateService.GetDay("04.04.2022") != "Monday")
                Assert.Fail();
        }

        [TestMethod()]
        public void GetDaysSpan_test()
        {
            DateTime dt = DateTime.Now;
            DateTime current = new DateTime(2022, 04, 03);
            if (int.Parse(DateService.GetDaysSpan(03, 04, 2022)) != (dt - current).Days)
                Assert.Fail();
        }
    }
}