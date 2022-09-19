namespace Lab5.Domain
{
    [Serializable]
    public class Runway
    {
        public double RunwayLength { get; set; } = 1000;
        public double RunwayWidth { get; set; } = 200;
        public int NumberOfRunways { get; set; } = 1;

        public Runway () { }

        public Runway (double runwayLength, double runwayWidth, int numberOfRunways)
        {
            RunwayLength = runwayLength;
            RunwayWidth = runwayWidth;
            NumberOfRunways = numberOfRunways;
        }
    }
}
