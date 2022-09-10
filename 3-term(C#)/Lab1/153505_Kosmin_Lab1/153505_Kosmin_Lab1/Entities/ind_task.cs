// variant 5
namespace _153505_Kosmin_Lab1.Collections
{
    public interface IContribution
    {
        ref int getAmount();
        int getPercent();
        string getContributionID();
    }

    public class FivePercentContribution : IContribution
    {
        public string contributionID;
        public int amount;
        public const int percent = 5;

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
        public string contributionID;
        public int amount;
        public const int percent = 10;

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
        MyCustomCollection<IContribution> contributions = new MyCustomCollection<IContribution>();

        public string Surname { get; set; }

        public Contributor(string surname)
        {
            Surname = surname;
        }

        public void addNewContribution(IContribution contribution)
        {
            contributions.Add(contribution);
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
                    contribution.getAmount() += replenishment;
        }
    }

    public class Bank
    {
        protected MyCustomCollection<Contributor> contributors = new MyCustomCollection<Contributor>();

        public void addNewContributor(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return;
            contributors.Add(new Contributor(surname));
        }

        public void doContribution(string surname, IContribution typeContribution)
        {
            if (typeContribution != null)
            {
                string newContribID = typeContribution.getContributionID();

                foreach (Contributor contributor in contributors)
                {
                    if (contributor.Surname == surname)
                    {
                        IContribution currentContributor = contributor.getContributionByID(newContribID);

                        if (currentContributor == null)
                        {
                            contributor.addNewContribution(typeContribution);
                        }
                        break;
                    }
                }
            }
        }

        public int getContributionAmount(string surname, string contributionID)
        {
            foreach (Contributor contributor in contributors)
            {
                if (contributor.Surname == surname)
                {
                    IContribution contribution = contributor.getContributionByID(contributionID);
                    if (contribution != null)
                        return contribution.getAmount();
                }
            }
            return 0;
        }

        public int getContributionPercent(string surname, string contributionID)
        {
            foreach (Contributor contributor in contributors)
            {
                if (contributor.Surname == surname)
                {
                    IContribution contribution = contributor.getContributionByID(contributionID);
                    if (contribution != null)
                        return contribution.getPercent();
                }
            }
            return 0;
        }

        public void replenishContribution(string surname, string contributionID, int replenishment)
        {
            foreach (Contributor contributor in contributors)
            {
                if (contributor.Surname == surname)
                {
                    contributor.increaseContribution(contributionID, replenishment);
                    break;
                }
            }
        }

        public int getSumOfContributionsBySurname(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return contributor.getTotalSumOfContributions();
            return 0;
        }

        public double getTotalPaymentBySurname(string surname)
        {
            foreach (Contributor contributor in contributors)
                if (contributor.Surname == surname)
                    return contributor.getTotalPaymentOnContributions();
            return 0;
        }
    }
}
