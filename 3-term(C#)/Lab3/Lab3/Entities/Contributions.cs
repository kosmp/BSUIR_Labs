using Lab3.Interfaces;

namespace Lab3.Entities
{
    public class FivePercentContribution : IContribution
    {
        protected string contributionID;
        protected int amount;
        protected const int percent = 5;

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
        protected const int percent = 10;

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

    public class ThirteenPercentContribution : IContribution
    {
        protected string contributionID;
        protected int amount;
        protected const int percent = 13;

        public ThirteenPercentContribution(string contributionID, int deposit)
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

    public class FifteenPercentContribution : IContribution
    {
        protected string contributionID;
        protected int amount;
        protected const int percent = 15;

        public FifteenPercentContribution(string contributionID, int deposit)
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
}
