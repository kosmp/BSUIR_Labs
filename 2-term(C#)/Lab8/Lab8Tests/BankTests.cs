using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab8;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab8.Tests
{
    [TestClass()]
    public class BankTests
    {
        [TestMethod()]
        public void getSumContributionsTest()
        {
            Bank belarusBank = new Bank();
            belarusBank.addCommonContributor("Egor", 30);
            belarusBank.addBonusContributor("Pavel", 200, 50);
            if (belarusBank.getSumContributions() != 280)
                Assert.Fail();
        }

        [TestMethod()]
        public void addCommonContributorTest()
        {
            Bank belarusBank = new Bank();
            belarusBank.addCommonContributor("Egor", 30);
            if (belarusBank.getSumContributions() != 30)
                Assert.Fail();
        }

        [TestMethod()]
        public void addBonusContributorTest()
        {
            Bank belarusBank = new Bank();
            belarusBank.addBonusContributor("Pavel", 200, 50);
            if (belarusBank.getSumContributions() != 250)
                Assert.Fail();
        }
    }
}