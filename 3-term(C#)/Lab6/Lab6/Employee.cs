namespace Lab6
{
    [Serializable]
    public class Employee
    {
        public Employee() { }
        public Employee(string name, int age, bool certifiedWorker)
        {
            Name = name;
            Age = age;
            CertifiedWorker = certifiedWorker;
        }
        public string Name { get; set; }
        public int Age { get; set; }
        public bool CertifiedWorker { get; set; }
    }
}
