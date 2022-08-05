using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab4;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab4.Tests
{
    [TestClass()]
    public class BankTests
    {
        [TestMethod()]
        public void getInstanceTest()
        {
            Bank bank = Bank.getInstance("BelarusBank");
            Bank bank2 = Bank.getInstance("BelInvest");
            if (bank2.BankName != "BelarusBank")
                Assert.Fail();
        }

        [TestMethod()]
        public void totalPaymentTest()
        {
            Bank bank = Bank.getInstance("BelarusBank");
            bank.CountOfContrib = 10;
            if (bank.totalPayment() != 200)
                Assert.Fail();
        }

        [TestMethod()]
        public void incAmountTest()
        {
            Bank bank = Bank.getInstance("BelarusBank");
            bank.GetContribution.incAmountBy10();
            if (bank.GetContribution.GetAmount != 410)
                Assert.Fail();
            bank.GetContribution.decAmountBy10();
        }

        [TestMethod()]
        public void decAmountTest()
        {
            Bank bank = Bank.getInstance("BelarusBank");
            bank.GetContribution.decAmountBy10();
            if (bank.GetContribution.GetAmount != 390)
                Assert.Fail();
            bank.GetContribution.incAmountBy10();
        }
    }
}