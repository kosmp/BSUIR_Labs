using Lab3.Interfaces;
using System.Linq;
using System.Collections.Generic;
using System.Xml.Linq;

namespace Lab3.Entities
{
    public class Bank
    {
        public delegate void ContributorHandler(string action);
        public event ContributorHandler? NotifyContributorChanged;
        public delegate void NewContributionHandler(string action, IContribution newContribution, Contributor contributor);
        public event NewContributionHandler? NotifyNewContributionAdded;

        protected List<Contributor> contributors = new List<Contributor>();
        protected Dictionary<string, IContribution> contributions = new Dictionary<string, IContribution>();

        public List<string> getSortedListOfContributions()
        {
            var finalSec = contributions.OrderBy(p => p.Value.getPercent());
            List<string> sortedByPercentListIDs = new List<string>();
            foreach (var x in finalSec)
                sortedByPercentListIDs.Add(x.Key);
            return sortedByPercentListIDs;
        }

        public double getPaymentOnAllContributionsInBank()
        {
            var finalSec = from i in contributions select i.Value;
            double res = 0;
            foreach (var x in finalSec)
                res += x.getPercent() / 100.0 * x.getAmount();
            return res;
        }

        public int getSumOfAllContributions()
        {
            var finalSec = (from i in contributions select i.Value.getAmount()).ToList();
            int res = 0;
            foreach (var x in finalSec)
                res += x;
            return res;
        }

        public string getSurnameWhoPaidMaxAmountPercent()
        {
            var res = contributors.OrderByDescending(p => p.getTotalPaymentOnContributions()).ToList();
            return res[0].Surname;
        }

        public int getNumberOfContributorsWhoGotPaymentMoreThan(double moreThanThisPayment)
        {
            return contributors.Aggregate(0, (total, next) => next.getTotalPaymentOnContributions() >= Math.Abs(moreThanThisPayment) ? total + 1 : total);
        }

        public void printGroupOfPayments()
        {
            var res = contributors.GroupBy(p => p.Name)
                .Select(x => new
                {
                    Name = x.Key,
                    Surnames = from p in x select p.Surname,
                    Payments = from p in x select p.getTotalPaymentOnContributions()
                });
            Console.WriteLine("\n");
            foreach (var contributor in res)
            {
                Console.WriteLine("Name: " + contributor.Name);
                foreach (var j in contributor.Surnames)
                    Console.Write("Surname: " + j + ". ");
                Console.WriteLine();
                foreach (var y in contributor.Payments)
                    Console.WriteLine("Payment: " + y);
                Console.WriteLine("\n");
            }
        }

        public void addNewContributor(string name, string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    throw new Exception("Such contributor already exists.");
            Contributor newContributor = new Contributor(name, surname);
            contributors.Add(newContributor);
            NotifyContributorChanged?.Invoke("Contributor was added. Surname: " + surname + ", Name: " + name);
        }

        public void removeContributorByName(string surname)
        {
            Contributor contributor = getContributorBySurname(surname);
            contributors.Remove(contributor);
            List<string> contributionsOfCurrContributor = new List<string>();
            foreach (var x in contributions)
            {
                IContribution contribution = contributor.getContributionByID(x.Key);
                if (contribution != null)
                    contributions.Remove(x.Key);
            }
            NotifyContributorChanged?.Invoke("Contributor was removed. Surname: " + surname + ", Name: " + contributor.Name);
        }

        public void doContribution(string surname, IContribution typeContribution)
        {
            if (typeContribution != null)
            {
                string newContribID = typeContribution.getContributionID();

                Contributor contributor = getContributorBySurname(surname);

                if (!contributions.ContainsKey(typeContribution.getContributionID()))
                {
                    contributor.addNewContribution(typeContribution);
                    contributions.Add(typeContribution.getContributionID(), typeContribution);
                    NotifyNewContributionAdded?.Invoke("new contribution was added", typeContribution, contributor);
                }
            }
            else
            {
                throw new Exception("Contribution can't be null.");
            }
        }

        public void removeContribution(string surname, string contributionID)
        {
            Contributor contributor = getContributorBySurname(surname);
            contributor.removeContributionByID(contributionID);
            contributions.Remove(contributionID);
        }

        public void replenishContribution(string surname, string contributionID, int replenishment)
        {
            Contributor contributor = getContributorBySurname(surname);
            contributor.increaseContribution(contributionID, Math.Abs(replenishment));
        }

        public bool isInBankContributions(string contributionID)
        {
            if (contributions.ContainsKey(contributionID))
                return true;
            return false;
        }

        public Contributor getContributorBySurname(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return contributor;
            throw new Exception("No such surname among the contributors.");
        }

        public int getContributionAmount(string surname, string contributionID)
        {
            Contributor contributor = getContributorBySurname(surname);
            IContribution contribution = contributor.getContributionByID(contributionID);
            if (contribution != null)
                return contribution.getAmount();
            throw new Exception("This contributor hasn't contribution with such ID.");
        }

        public int getContributionPercent(string surname, string contributionID)
        {
            Contributor contributor = getContributorBySurname(surname);
            IContribution contribution = contributor.getContributionByID(contributionID);
            if (contribution != null)
                return contribution.getPercent();
            throw new Exception("This contributor hasn't contribution with such ID.");
        }

        public int getSumOfContributionsBySurname(string surname)
        {
            Contributor contributor = getContributorBySurname(surname);
            return contributor.getTotalSumOfContributions();
        }

        public double getTotalPaymentBySurname(string surname)
        {
            Contributor contributor = getContributorBySurname(surname);
            return contributor.getTotalPaymentOnContributions();
        }

        public void printInConsoleAllContributors()
        {
            if (contributors.Count != 0)
                Console.WriteLine("\n---------------------\nList of contributors: ");
            int counter = 1;
            foreach (Contributor x in contributors)
            {
                Console.WriteLine(counter + ". Surname: " + x.Surname);
                counter++;
            }
            if (contributors.Count != 0)
                Console.WriteLine("---------------------\n");
        }
    }
}
