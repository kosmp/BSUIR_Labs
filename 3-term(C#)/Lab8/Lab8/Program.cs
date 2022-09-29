using ClassLibrary;
using System.Text.Json;

public class Program
{
    static async Task Main(string[] args)
    {
        StreamService<Car> service = new StreamService<Car>();
        MemoryStream mStream = new MemoryStream();
        
        Car[] cars = new Car[1000];
        for (int i = 1; i <= 1000; i++)
        {
            bool x = false;
            if (i > 40 && i < 160)
                x = true;
            cars[i - 1] = new Car(i, LoremNET.Lorem.Words(1), x);
        }

        var task1 = service.WriteToStreamAsync(mStream, cars);

        await Task.Delay(200);  // for sync work according to condition

        var task2 = service.CopyFromStreamAsync(mStream, "test.json");

        task1.Wait();
        task2.Wait();

        Task<int> getStatiscticsTask = service.GetStatisticsAsync("test.json", x => x.NeedInspectionInThisYear == true);
        int numOfCars = await getStatiscticsTask;

        Console.WriteLine("GetStatisticsAsync result: " + numOfCars);
    }
}