using Lab6;
using System.Reflection;
using static System.Net.Mime.MediaTypeNames;

public class Program
{
    static void Main(string[] args)
    {
        List<Employee> list = new List<Employee>();
        list.Add(new Employee("Egor", 17, false));
        list.Add(new Employee("Valentin", 19, false));
        list.Add(new Employee("Pavel", 18, true));
        list.Add(new Employee("Vadim", 20, true));
        list.Add(new Employee("Denis", 16, false));
        
        Assembly assembly = Assembly.LoadFrom("D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab6\\ClassLibrary\\obj\\Debug\\net6.0\\ClassLibrary.dll");

        Type[] typeArgs = { typeof(Employee) };
        Type? fileService = assembly.GetType("ClassLibrary.FileService`1").MakeGenericType(typeArgs);
        ConstructorInfo? constructor = fileService?.GetConstructor(new Type[] { });
        object obj = constructor.Invoke(new object[] { });

        MethodInfo? SaveData = fileService.GetMethod("SaveData", new Type[] { typeof(IEnumerable<Employee>), typeof(string) });
        
        SaveData?.Invoke(obj, new object[2] { list, "test.json" });

        MethodInfo? ReadFile = fileService.GetMethod("ReadFile", new Type[] { typeof(string) });
        var resFromFile = ReadFile?.Invoke(obj, new object[1] { "test.json" });

        IEnumerable<Employee> res = resFromFile as IEnumerable<Employee>;
        Console.WriteLine("Reading from file:");
        foreach (var item in res)
        {
            Console.WriteLine("Name: " + item.Name);
            Console.WriteLine("Age: " + item.Age);
            Console.WriteLine("IsCertified: " + item.CertifiedWorker + "\n");
        }
    }
}