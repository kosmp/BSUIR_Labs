using System;
using System.Collections.Generic;

namespace Lab5
{
    public class Contributor
    {
        private enum Status
        {
            contributed,
            not_contributed
        }

        private Status current = new Status();

        private string name;

        public string getName
        {
            get { return name; }
        }

        private Contribution contribution;

        public Contribution GetContribution()
        {
            return contribution;
        }

        public Contributor(string newName)
        {
            name = newName;
            current = Status.not_contributed;
        }

        public void addContribution(List<Contribution> copyOfContributions)
        {
            if (contribution == null)
            {
                contribution = new Contribution();
                copyOfContributions.Add(contribution);
                current = Status.contributed;
            }
        }
    }
}
