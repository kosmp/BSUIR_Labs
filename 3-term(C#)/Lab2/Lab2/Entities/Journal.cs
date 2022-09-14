using Lab2.Collections;

namespace Lab2.Entities
{
    public class Journal
    {
        protected Bank currentBank;
        protected MyCustomCollection<Tuple<string, Contributor>> eventList = new MyCustomCollection<Tuple<string, Contributor>>();
        public int countOfEvents = 0;

        public Journal(ref Bank bank)
        {
            currentBank = bank;
            currentBank.NotifyContributorChanged += RegNewAction;
        }

        public void RegNewAction(string action, Contributor contributor)
        {
            eventList.Add(new Tuple<string, Contributor>(action, contributor));
            countOfEvents++;
        }

        public void clearJournal()
        {
            foreach (var x in eventList)
                eventList.Remove(x);
            countOfEvents = 0;
        }

        public void printEventList()
        {
            if (eventList.Count > 0)
                Console.WriteLine("\n-----------------------\nEvent list from journal(Contributors which were added or removed): ");
            int counter = 1;
            foreach (var x in eventList)
            {
                Console.WriteLine(counter + ". Event: " + x.Item1 + ". Surname: " + x.Item2.Surname);
                counter++;
            }

            if (eventList.Count > 0)
                Console.WriteLine("-----------------------\n");
        }
    }
}
