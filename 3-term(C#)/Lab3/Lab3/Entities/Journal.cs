namespace Lab3.Entities
{
    public class Journal
    {
        public string JournalTitle { get; set; }

        protected List<string> eventList = new List<string>();
        public int countOfEvents = 0;

        public Journal(string journalTitle)
        {
            JournalTitle = journalTitle;
        }

        public void RegNewActions(string infoAboutAction)
        {
            eventList.Add(infoAboutAction);
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
            Console.WriteLine($"\nEvent list from {JournalTitle} journal:");
            int counter = 1;
            foreach (var x in eventList)
            {
                Console.WriteLine(counter + ". Event: " + x);
                counter++;
            }

            if (eventList.Count > 0)
                Console.WriteLine("\n");
        }
    }
}
