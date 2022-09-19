namespace Lab5.Domain
{
    [Serializable]
    public class Airport : Runway
    {
        public string Name { get; set; } = "Undefined";
        public string City { get; set; } = "Undefined";

        public Airport() : base() { }

        public Airport(string name, string city, double runwayLength, double runwayWidth, int numberOfRunways)
            : base(Math.Abs(runwayLength), Math.Abs(runwayWidth), Math.Abs(numberOfRunways))
        {
            Name = name;
            City = city;
        }
    }
}
