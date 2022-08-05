using System;
using System.Collections.Generic;

namespace Lab5
{
    public class Bank
    {
        private List<Contributor> contributors = new List<Contributor>();
        private List<Contribution> contributions;
        private string bankName = "Unknown";

        public List<Contributor> GetContributors
        {
            get { return contributors; }
        }      

        public string GetBankName
        {
            get { return bankName; }
        }

        public Bank(string nameOfBank)
        {
            bankName = nameOfBank;
            contributions = new List<Contribution>();
        }

        public void addContributor(string newName)
        {
            contributors.Add(new Contributor(newName));
        }

        public void doContribution(string forName)
        {
            Contributor temp = contributors.Find(item => item.getName == forName);
            if (temp != null)
                temp.addContribution(contributions);
        }

        public void incAmountInContrib(int incAmount, string name)
        {
            Contributor temp = contributors.Find(item => item.getName == name);
            if (temp.GetContribution() != null)
                temp.GetContribution().Amount = temp.GetContribution().Amount + incAmount;
        }

        public string getInfoAboutContributor(string name)
        {
            string info;
            info = "Contributor: " + name + '\n';
            Contributor currContributor = contributors.Find(item => item.getName == name);
            if (currContributor != null)
            {
                info += "Amount: " + currContributor.GetContribution().Amount + '\n';
                info += "Percent: " + currContributor.GetContribution().Percent;
            }
            else
                return "No such contributor";
            return info;
        }

        public double getTotalAmountOfPayments()
        {
            double res = 0;
            for (int i = 0; i < contributions.Count; i++)
                res += contributions[i].Amount * Convert.ToDouble(contributions[i].Percent) / 100;
            return res;
        }
    }
}
