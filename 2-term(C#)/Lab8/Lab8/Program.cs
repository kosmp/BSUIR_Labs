using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab8
{
    public interface IContribution
    {
        int getAmount();
    }

    public class CommonContribution : IContribution
    {
        public int amount;

        public CommonContribution(int _amount)
        {
            amount = _amount;
        }

        public int getAmount()
        {
            return amount;
        }
    }

    public class BonusContribution : IContribution
    {
        public int amount;
        public int bonus;

        public BonusContribution(int _amount, int _bonus)
        {
            amount= _amount;
            bonus= _bonus;
        }

        public int getAmount()
        {
            return amount + bonus;
        }
    }

    public class Contributor
    {
        IContribution typeContrib;

        public string Name { get; set; }

        public Contributor(string name, IContribution typeContrib)
        {
            Name = name;
            this.typeContrib = typeContrib;
        }

        public int getAmount()
        {
            return typeContrib.getAmount();
        }
    }

    public class Bank
    {
        protected List<Contributor> contributors = new List<Contributor>();
        
        public void addCommonContributor(string name, int amount)
        {
            contributors.Add(new Contributor(name, new CommonContribution(amount)));
        }

        public void addBonusContributor(string name, int amount, int bonus)
        {
            contributors.Add(new Contributor(name, new BonusContribution(amount, bonus)));
        }

        public int getSumContributions()
        {
            int res = 0;
            foreach (Contributor cont in contributors)
            {
                res += cont.getAmount();
            }

            return res;
        }
    }
    

    public class Program
    {
        static void Main(string[] args)
        {
            Bank belarusBank = new Bank();
            belarusBank.addCommonContributor("Egor", 30);
            belarusBank.addBonusContributor("Pavel", 200, 50);

            Console.WriteLine(belarusBank.getSumContributions());
        }
    }
}
