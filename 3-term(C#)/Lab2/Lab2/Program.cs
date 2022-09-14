// variant 5
using Lab2.Collections;
using Lab2.Entities;

public class Program
{
    static void Main(string[] args)
    {
        Bank belarusbank = new Bank();

        Journal journal = new Journal(ref belarusbank);
        belarusbank.NotifyNewContributionAdded += (string action, IContribution contribution, Contributor contributor) => Console.WriteLine("\nEvent: " + action +
            ". Surname: " + contributor.Surname + ", ID: " + contribution.getContributionID() + ", Deposit: " + contribution.getAmount());

        belarusbank.addNewContributor("Fg");
        belarusbank.doContribution("Fg", new FivePercentContribution("542", 70));
        belarusbank.replenishContribution("Fg", "542", 30);
        belarusbank.replenishContribution("Fg", "542", 100);

        belarusbank.doContribution("Fg", new FivePercentContribution("34", 50));
        belarusbank.replenishContribution("Fg", "34", 10);

        belarusbank.addNewContributor("Gh");
        belarusbank.doContribution("Gh", new TenPercentContribution("542", 50));
        belarusbank.replenishContribution("Gh", "542", 10);
        belarusbank.doContribution("Gh", new FivePercentContribution("13", 100));
        belarusbank.removeContributorByName("Gh");

        belarusbank.addNewContributor("Gh");
        belarusbank.doContribution("Gh", new FivePercentContribution("57", 44));
        belarusbank.addNewContributor("Hj");

        Console.WriteLine("\n" + belarusbank.getTotalPaymentBySurname("Fg"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Fg"));
        Console.WriteLine(belarusbank.getContributionPercent("Fg", "542"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Gh"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Hj"));

        belarusbank.printInConsoleAllContributors();

        journal.printEventList();

        try
        {
            MyCustomCollection<int> test = new MyCustomCollection<int>();
            test.Add(1);
            test.Remove(2);
        }
        catch (NoSuchObjectInCollection)
        {
            Console.WriteLine("\nTest of exception: exception was thrown.");
        }

        try
        {
            MyCustomCollection<int> test = new MyCustomCollection<int>();
            test.Add(1);
            test.Add(3);
            Console.WriteLine(test[2]);
        }
        catch(IndexOutOfRangeException)
        {
            Console.WriteLine("\nTest of exception: exception was thrown.");
        }
    }
}