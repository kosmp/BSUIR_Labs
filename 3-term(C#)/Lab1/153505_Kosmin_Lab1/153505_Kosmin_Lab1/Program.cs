using _153505_Kosmin_Lab1.Collections;

public class Program
{
    static void Main(string[] args)
    {
        Bank belarusBank = new Bank();
        belarusBank.addNewContributor("Fg");
        belarusBank.doContribution("Fg", new FivePercentContribution("542", 70));
        belarusBank.replenishContribution("Fg", "542", 30);
        belarusBank.replenishContribution("Fg", "542", 100);

        belarusBank.doContribution("Fg", new FivePercentContribution("34", 50));
        belarusBank.replenishContribution("Fg", "34", 10);

        belarusBank.addNewContributor("Gh");
        belarusBank.doContribution("Gh", new TenPercentContribution("542", 50));
        belarusBank.replenishContribution("Gh", "542", 10);
        belarusBank.doContribution("Gh", new FivePercentContribution("13", 100));

        Console.WriteLine(belarusBank.getTotalPaymentBySurname("Fg"));
        Console.WriteLine(belarusBank.getSumOfContributionsBySurname("Fg"));
        Console.WriteLine(belarusBank.getContributionPercent("Fg", "542"));
        Console.WriteLine(belarusBank.getSumOfContributionsBySurname("Gh"));
    }
}