using Lab5.Domain;
using System.Xml.Linq;
using System.Xml.Serialization;
using System.Text.Json;

namespace _Serializer
{
    public class Serializer : ISerializer
    {
        public IEnumerable<Airport> DeSerializeByLINQ(string fileName)
        {
            var airports = XDocument.Load(fileName)
                .Element("Airports")?
                .Elements("airport")
                .Select(p => new Airport
                {
                    Name = p.Attribute("Name")?.Value,
                    City = p.Element("City")?.Value,
                    RunwayLength = (double)(p.Element("RunwayLength")),
                    RunwayWidth = (double)(p.Element("RunwayWidth")),
                    NumberOfRunways = (int)(p.Element("NumberOfRunways"))
                });

            if (airports != null)
            {
                foreach (var airport in airports)
                {
                    yield return airport;
                }
            }
        }

        public IEnumerable<Airport> DeSerializeJSON(string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.Open))
            {
                IEnumerable<Airport>? airports = JsonSerializer.Deserialize<IEnumerable<Airport>>(fs);

                if (airports != null)
                {
                    foreach (var item in airports)
                        yield return item;
                }
            }
        }

        public IEnumerable<Airport> DeSerializeXML(string fileName)
        {
            XmlSerializer reader = new XmlSerializer(typeof(Airport[]));
            using (FileStream fs = new FileStream(fileName, FileMode.Open))
            {
                Airport[]? airports = reader.Deserialize(fs) as Airport[];
                if (airports != null)
                {
                    foreach (var airport in airports)
                        yield return airport;
                }
            }
        }

        public void SerializeByLINQ(IEnumerable<Airport> xxx, string fileName)
        {
            XDocument doc = new XDocument();
            XElement airports = new XElement("Airports");

            foreach (var item in xxx)
            {
                XElement airport = new XElement("airport");
                airport.Add(new XAttribute("Name", item.Name));
                airport.Add(new XElement("City", item.City));
                airport.Add(new XElement("RunwayLength", item.RunwayLength));
                airport.Add(new XElement("RunwayWidth", item.RunwayWidth));
                airport.Add(new XElement("NumberOfRunways", item.NumberOfRunways));
                airports.Add(airport);
            }

            doc.Add(airports);
            doc.Save(fileName);
        }

        public void SerializeJSON(IEnumerable<Airport> xxx, string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fs, xxx);
            }
        }

        public void SerializeXML(IEnumerable<Airport> xxx, string fileName)
        {
            Airport[] airports = new Airport[xxx.Count()];
            int i = 0;
            foreach (Airport airport in xxx)
            {
                airports[i] = airport;
                i++;
            }

            XmlSerializer writer = new XmlSerializer(typeof(Airport[]));
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                writer.Serialize(fs, airports);
            }
        }
    }
}