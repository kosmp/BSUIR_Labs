using Lab3.Interfaces;

namespace Lab3.Entities
{
    public class Contributor
    {
        protected List<IContribution> contributions = new List<IContribution>();

        public string Surname { get; set; }
        public string Name { get; set; }

        public Contributor(string name, string surname)
        {
            Name = name;
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
                throw new Exception("No contribution with such ID.");
        }

        public IContribution? getContributionByID(string ID)
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
}
