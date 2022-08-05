using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab5;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab5.Tests
{
    [TestClass()]
    public class ProgramTests
    {
        [TestMethod()]
        public void incAmountInContribTest()
        {
            Bank newBank = new Bank("BelarusBank");
            newBank.addContributor("Misha");
            newBank.doContribution("Misha");
            newBank.incAmountInContrib(250, "Misha");
            Contributor temp = newBank.GetContributors.Find(item => item.getName == "Misha");
            if (temp.GetContribution().Amount != 260)
                Assert.Fail();
        }

        [TestMethod()]
        public void getTotalAmountOfPaymentsTest()
        {
            Bank newBank = new Bank("BelarusBank");
            newBank.addContributor("Misha");
            newBank.doContribution("Misha");
            if (newBank.getTotalAmountOfPayments() != 0.5)
                Assert.Fail();
        }

        [TestMethod()]
        public void addContributorTest()
        {
            Bank newBank = new Bank("BelarusBank");
            newBank.addContributor("Misha");
            if (newBank.GetContributors.Find(item => item.getName == "Misha") == null)
                Assert.Fail();
        }

        [TestMethod()]
        public void doContributionTest()
        {
            Bank newBank = new Bank("BelarusBank");
            newBank.addContributor("Misha");
            newBank.doContribution("Misha");
            if (newBank.GetContributors.Find(item => item.getName == "Misha").GetContribution() == null)
                Assert.Fail();
        }
    }
}