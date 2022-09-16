// variant 5
using Lab3.Entities;
using Lab3.Interfaces;

public class Program
{
    static void Main(string[] args)
    {
        Bank belarusbank = new Bank();

        Journal journal = new Journal("BelarusBank");
        belarusbank.NotifyContributorChanged += journal.RegNewActions;
        belarusbank.NotifyNewContributionAdded += (string action, IContribution contribution, Contributor contributor) => Console.WriteLine("\nEvent: " + action +
            ". Surname: " + contributor.Surname + ", ID: " + contribution.getContributionID() + ", Deposit: " + contribution.getAmount());

        belarusbank.addNewContributor("Valentin", "Fg");
        belarusbank.doContribution("Fg", new FivePercentContribution("542", 70));
        belarusbank.replenishContribution("Fg", "542", 30);
        belarusbank.replenishContribution("Fg", "542", 200);

        belarusbank.doContribution("Fg", new ThirteenPercentContribution("34", 50));
        belarusbank.replenishContribution("Fg", "34", 10);

        belarusbank.addNewContributor("Oleg", "Gh");
        belarusbank.doContribution("Gh", new TenPercentContribution("743", 50));
        belarusbank.replenishContribution("Gh", "743", 10);
        belarusbank.doContribution("Gh", new FifteenPercentContribution("17", 100));
        belarusbank.removeContributorByName("Gh");

        belarusbank.addNewContributor("Valentin", "Bd");
        belarusbank.doContribution("Bd", new FivePercentContribution("71", 20));
        belarusbank.doContribution("Bd", new FifteenPercentContribution("53", 150));

        belarusbank.addNewContributor("Egor", "Gh");
        belarusbank.doContribution("Gh", new FifteenPercentContribution("57", 44));

        belarusbank.addNewContributor("Vadim", "Hj");
        belarusbank.doContribution("Hj", new FifteenPercentContribution("13", 56));
        belarusbank.doContribution("Hj", new FivePercentContribution("26", 250));

        belarusbank.addNewContributor("Vadim", "Dh");
        belarusbank.doContribution("Dh", new FivePercentContribution("51", 100));

        Console.WriteLine("\n" + belarusbank.getTotalPaymentBySurname("Fg"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Fg"));
        Console.WriteLine(belarusbank.getContributionPercent("Fg", "542"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Gh"));
        Console.WriteLine(belarusbank.getSumOfContributionsBySurname("Hj"));

        belarusbank.printInConsoleAllContributors();

        journal.printEventList();

        Console.WriteLine("getSortedListOfContributions: ");
        foreach (var x in belarusbank.getSortedListOfContributions())
            Console.WriteLine(x);
        Console.WriteLine("\ngetPaymentOnAllContributionsInBank:\n" + belarusbank.getPaymentOnAllContributionsInBank());
        Console.WriteLine("\ngetSumOfAllContributions:\n" + belarusbank.getSumOfAllContributions());
        Console.WriteLine("\ngetSurnameWhoPaidMaxAmountPercent:\n" + belarusbank.getSurnameWhoPaidMaxAmountPercent());
        Console.WriteLine("\ngetNumberOfContributorsWhoGotPaymentMoreThan:\n" + belarusbank.getNumberOfContributorsWhoGotPaymentMoreThan(22));
        belarusbank.printGroupOfPayments();
    }
}