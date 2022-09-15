using Lab2.Collections;

namespace Lab2.Entities
{
    public interface IContribution
    {
        ref int getAmount();
        int getPercent();
        string getContributionID();
    }

    public class FivePercentContribution : IContribution
    {
        protected string contributionID;
        protected int amount;
        private const int percent = 5;

        public FivePercentContribution(string contributionID, int deposit)
        {
            this.contributionID = contributionID;
            amount = deposit;
        }

        public ref int getAmount()
        {
            return ref amount;
        }

        public int getPercent()
        {
            return percent;
        }

        public string getContributionID()
        {
            return contributionID;
        }
    }

    public class TenPercentContribution : IContribution
    {
        protected string contributionID;
        protected int amount;
        private const int percent = 10;

        public TenPercentContribution(string contributionID, int deposit)
        {
            this.contributionID = contributionID;
            amount = deposit;
        }

        public ref int getAmount()
        {
            return ref amount;
        }

        public int getPercent()
        {
            return percent;
        }

        public string getContributionID()
        {
            return contributionID;
        }
    }

    public class Contributor
    {
        protected MyCustomCollection<IContribution> contributions = new MyCustomCollection<IContribution>();

        public string Surname { get; set; }

        public Contributor(string surname)
        {
            Surname = surname;
        }

        public void addNewContribution(IContribution contribution)
        {
            contributions.Add(contribution);
        }

        public void removeContributionByID(string ID)
        {
            IContribution contribution = getContributionByID(ID);
            if (contribution != null)
                contributions.Remove(contribution);
            else
                throw new NoSuchObjectInCollection("No contribution with such ID.");
        }

        public IContribution getContributionByID(string ID)
        {
            foreach (IContribution contribution in contributions)
                if (contribution.getContributionID() == ID)
                    return contribution;
            return null;
        }

        public int getTotalSumOfContributions()
        {
            int res = 0;
            foreach (IContribution contribution in contributions)
                res += contribution.getAmount();
            return res;
        }

        public double getTotalPaymentOnContributions()
        {
            double res = 0;
            foreach (IContribution contribution in contributions)
                res += contribution.getAmount() * contribution.getPercent() / 100.0;
            return res;
        }

        public void increaseContribution(string ID, int replenishment)
        {
            foreach (IContribution contribution in contributions)
                if (contribution.getContributionID() == ID)
                    contribution.getAmount() += Math.Abs(replenishment);
        }
    }

    public class Bank
    {
        public delegate void ContributorHandler(string action);
        public event ContributorHandler? NotifyContributorChanged;
        public delegate void NewContributionHandler(string action, IContribution newContribution, Contributor contributor);
        public event NewContributionHandler? NotifyNewContributionAdded;

        protected MyCustomCollection<Contributor> contributors = new MyCustomCollection<Contributor>();

        public void addNewContributor(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return;
            Contributor newContributor = new Contributor(surname);
            contributors.Add(newContributor);
            NotifyContributorChanged?.Invoke("Contributor was added. Surname: " + surname);
        }

        public void doContribution(string surname, IContribution typeContribution)
        {
            if (typeContribution != null)
            {
                string newContribID = typeContribution.getContributionID();

                Contributor contributor = getContributorBySurname(surname);

                IContribution currentContribution = contributor.getContributionByID(newContribID);

                if (currentContribution == null)    // contributor has no such contribution, so we can add
                {
                    contributor.addNewContribution(typeContribution);
                    NotifyNewContributionAdded?.Invoke("new contribution was added", typeContribution, contributor);
                }
            }
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

        public Contributor getContributorBySurname(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return contributor;
            throw new NoSuchObjectInCollection("No such surname among the contributors.");
        }

        public void removeContributorByName(string surname)
        {
            Contributor contributor = getContributorBySurname(surname);
            contributors.Remove(contributor);
            NotifyContributorChanged?.Invoke("Contributor was removed. Surname: " + surname);
        }

        public int getContributionAmount(string surname, string contributionID)
        {
            Contributor contributor = getContributorBySurname(surname);
            IContribution contribution = contributor.getContributionByID(contributionID);
            if (contribution != null)
                return contribution.getAmount();
            throw new NoSuchObjectInCollection("This contributor hasn't contribution with such ID.");
        }

        public int getContributionPercent(string surname, string contributionID)
        {
            Contributor contributor = getContributorBySurname(surname);
            IContribution contribution = contributor.getContributionByID(contributionID);
            if (contribution != null)
                return contribution.getPercent();
            throw new NoSuchObjectInCollection("This contributor hasn't contribution with such ID.");
        }

        public void replenishContribution(string surname, string contributionID, int replenishment)
        {
            Contributor contributor = getContributorBySurname(surname);
            contributor.increaseContribution(contributionID, Math.Abs(replenishment));
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
    }
}
