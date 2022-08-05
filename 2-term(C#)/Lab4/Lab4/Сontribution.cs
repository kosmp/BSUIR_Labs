using System;

namespace Lab4
{
    public class Сontribution
    {
        public Сontribution()
        {
            amount = 400;
            percent = 5;
        }
       
        private int amount;
        private int percent;

        public void incAmountBy10()
        {
            amount += 10;
        }

        public void decAmountBy10()
        {
            if (amount >= 10) amount -= 10;
            if (amount < 10) amount = 0;
        }

        public int GetAmount
        {
            get { return amount; }
        }

        public int GetPercent
        {
            get { return percent; }
        }
    }
}

