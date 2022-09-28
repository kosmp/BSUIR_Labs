namespace ClassLibrary
{
    [Serializable]
    public class Car
    {
        public Car()
        {
            Id = 0;
            Name = "Undefined";
            NeedInspectionInThisYear = false;
        }

        public Car(int id, string name, bool needInspectionInThisYear)
        {
            Id = id;
            Name = name;
            NeedInspectionInThisYear = needInspectionInThisYear;
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public bool NeedInspectionInThisYear { get; set; }
    }
}
