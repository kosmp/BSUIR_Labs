using System;

namespace Lab5
{
    public class Contribution
    {
        public Contribution()
        {
            percent = 5;
            amount = 10;
        }
        private int percent;
        private int amount;
        public int Percent
        {
            get { return percent; }
            set { percent = value; }
        }
        public int Amount
        {
            get { return amount; }
            set { amount = value; }
        }

    }
}
