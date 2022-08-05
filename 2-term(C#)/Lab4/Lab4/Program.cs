using System;

namespace Lab4
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Bank bank = Bank.getInstance("BelarusBank");
            Console.WriteLine(bank.GetContribution.GetAmount);
            bank.GetContribution.incAmountBy10();
            Console.WriteLine(bank.GetContribution.GetAmount);
        }
    }
}
