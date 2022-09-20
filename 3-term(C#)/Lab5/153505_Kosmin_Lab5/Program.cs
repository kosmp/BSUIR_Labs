using Lab5.Domain;
using _Serializer;
using System.Collections;

public class Program
{
    static void Main(string[] args)
    {
        List<Airport> airports = new List<Airport>();
        airports.Add(new Airport("Fvf", "Minsk", 1200, 300, 5));
        airports.Add(new Airport("Vbf", "Brest", 1000, 280, 3));
        airports.Add(new Airport("Bfd", "Moscow", 1300, 320, 5));
        airports.Add(new Airport("Mbf", "Gomel", 1400, 300, 4));
        airports.Add(new Airport("Dgf", "Vitebsk", 1250, 310, 5));

        Serializer serializer = new Serializer();

        serializer.SerializeXML(airports, "D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testXML.xml");
        IEnumerable<Airport> listOfDeSerializedXML = serializer.DeSerializeXML("D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testXML.xml");
        Console.WriteLine("\nListOfDeSerializedXML: ");
        foreach (Airport airport in listOfDeSerializedXML)
        {
            Console.WriteLine("Name: " + airport.Name);
            Console.WriteLine("City: " + airport.City);
            Console.WriteLine("RunwayLength: " + airport.RunwayLength);
            Console.WriteLine("RunwayWidth: " + airport.RunwayWidth);
            Console.WriteLine("NumberOfRunways: " + airport.NumberOfRunways);
        }

        serializer.SerializeByLINQ(airports, "D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testXMLLINQ.xml");
        IEnumerable<Airport> listOfDeSerializedXMLLINQ = serializer.DeSerializeByLINQ("D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testXMLLINQ.xml");
        Console.WriteLine("\nListOfDeSerializedXMLLINQ: ");
        foreach (Airport airport in listOfDeSerializedXMLLINQ)
        {
            Console.WriteLine("Name: " + airport.Name);
            Console.WriteLine("City: " + airport.City);
            Console.WriteLine("RunwayLength: " + airport.RunwayLength);
            Console.WriteLine("RunwayWidth: " + airport.RunwayWidth);
            Console.WriteLine("NumberOfRunways: " + airport.NumberOfRunways);
        }

        serializer.SerializeJSON(airports, "D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testJSON.json");
        IEnumerable<Airport> listOfDeSerializedJSON = serializer.DeSerializeJSON("D:\\BSUIR\\BSUIR_Labs\\3-term(C#)\\Lab5\\testJSON.json");
        Console.WriteLine("\nListOfDeSerializedJSON: ");
        foreach (Airport airport in listOfDeSerializedJSON)
        {
            Console.WriteLine("Name: " + airport.Name);
            Console.WriteLine("City: " + airport.City);
            Console.WriteLine("RunwayLength: " + airport.RunwayLength);
            Console.WriteLine("RunwayWidth: " + airport.RunwayWidth);
            Console.WriteLine("NumberOfRunways: " + airport.NumberOfRunways);
        }
    }
}