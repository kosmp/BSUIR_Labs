namespace Lab4
{
    public class Car
    {
        public Car(string modelName, string color, int maxStockSpeed, bool isTruck)
        {
            ModelName = modelName;
            Color = color;
            MaxStockSpeed = maxStockSpeed;
            IsTruck = isTruck;
        }

        public string ModelName { get; set; }
        public string Color { get; set; }
        public int MaxStockSpeed { get; set; }
        public bool IsTruck { get; set; }
    }
}
