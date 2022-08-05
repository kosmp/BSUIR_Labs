using System;
using Lab4;

namespace Lab4
{
    public class Bank
    {
        private static Bank bankInstance;

        private string bankName;
        private int countOfContrib = 0;
        private static Сontribution сontribution = new Сontribution();

        private Bank() { }

        public string BankName
        {
            get { return bankInstance.bankName; }
            private set { bankInstance.bankName = value; }
        }

        public int CountOfContrib
        {
            get { return bankInstance.countOfContrib; }
            set
            {
                if (value >= 0)
                    bankInstance.countOfContrib = value;
                else
                    bankInstance.countOfContrib = 0;
            }
        }

        public static Bank getInstance(string name)
        {
            if (bankInstance == null)
            {
                bankInstance = new Bank();
                bankInstance.bankName = name;
            }

            return bankInstance;
        }

        public Сontribution GetContribution
        {
            get { return сontribution; }
        }

        public int totalPayment()
        {
            if (сontribution != null)
                return сontribution.GetAmount * сontribution.GetPercent / 100 * countOfContrib;
            else
                return 0;
        }
    }
}
