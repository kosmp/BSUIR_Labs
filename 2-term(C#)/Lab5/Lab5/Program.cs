// variant 5
using System;

namespace Lab5
{
    public class Program
    {
        static public void Main(string[] args)
        {
            Bank newBank = new Bank("BelarusBank");
            newBank.addContributor("Misha");
            newBank.doContribution("Misha");
            newBank.incAmountInContrib(250, "Misha");
            newBank.addContributor("Pavel");
            newBank.doContribution("Pavel");
            Console.WriteLine(newBank.getTotalAmountOfPayments());
            Console.WriteLine(newBank.getInfoAboutContributor("Pavel"));
            Console.WriteLine(newBank.getInfoAboutContributor("Misha"));
            Bank newBank2 = new Bank("BelinvestBank");
            newBank2.addContributor("Alex");
            newBank2.doContribution("Alex");
            Console.WriteLine(newBank2.getInfoAboutContributor("Alex"));
            Console.WriteLine(newBank2.getTotalAmountOfPayments());
            Console.WriteLine(newBank.getTotalAmountOfPayments());
        }
    }
}
