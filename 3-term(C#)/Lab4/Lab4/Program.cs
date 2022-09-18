using Lab4;
using System.Linq;
using System.Collections;

public class Program
{
    static void Main(string[] args)
    {
        List<Car> cars = new List<Car>();
        cars.Add(new Car("Tesla model 3", "red", 370, false));
        cars.Add(new Car("BMW X5", "yellow", 300, false));
        cars.Add(new Car("Tesla cybertruck", "blue", 200, true));
        cars.Add(new Car("Audi E-TRON", "red", 340, false));
        cars.Add(new Car("Porsche Cayene", "white", 350, false));
        
        FileService<Car> fileService = new FileService<Car>();
        try
        {
            fileService.SaveData(cars, "test.bin");
        }
        catch(ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
        }

        FileService<Car>.Rename("test.bin", "testRenamed.bin");

        List<Car> newListOfCars = new List<Car>();
        try
        {
            foreach (var i in fileService.ReadFile("testRenamed.bin"))
            {
                newListOfCars.Add(i);
            }
        }
        catch(ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
        }
        
        var sortedListOfCarsByName = newListOfCars.OrderBy(p => p, new MyCustomComparer<Car>()).Select(p => p);

        Console.WriteLine("\nOriginal:");
        foreach (var i in cars)
        {
            Console.WriteLine("ModelName: " + i.ModelName);
            Console.WriteLine("Color: " + i.Color);
            Console.WriteLine("MaxStockSpeed: " + i.MaxStockSpeed);
            Console.WriteLine("IsTruck: " + i.IsTruck.ToString() + "\n");
        }

        Console.WriteLine("\nSorted collection:");
        foreach (var i in sortedListOfCarsByName)
        {
            Console.WriteLine("ModelName: " + i.ModelName);
            Console.WriteLine("Color: " + i.Color);
            Console.WriteLine("MaxStockSpeed: " + i.MaxStockSpeed);
            Console.WriteLine("IsTruck: " + i.IsTruck.ToString() + "\n");
        }

        Console.WriteLine("\nSorted by color:");
        foreach (var i in newListOfCars.OrderBy(x => x.Color.ToLower()))
        {
            Console.WriteLine("ModelName: " + i.ModelName);
            Console.WriteLine("Color: " + i.Color);
            Console.WriteLine("MaxStockSpeed: " + i.MaxStockSpeed);
            Console.WriteLine("IsTruck: " + i.IsTruck.ToString() + "\n");
        }
    }
}