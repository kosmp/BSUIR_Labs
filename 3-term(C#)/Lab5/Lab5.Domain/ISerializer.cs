using System.Collections;

namespace Lab5.Domain
{
    public interface ISerializer
    {
        IEnumerable<Airport> DeSerializeByLINQ(string fileName);
        IEnumerable<Airport> DeSerializeXML(string fileName);
        IEnumerable<Airport> DeSerializeJSON(string fileName);
        void SerializeByLINQ(IEnumerable<Airport> xxx, string fileName);
        void SerializeXML(IEnumerable<Airport> xxx, string fileName);
        void SerializeJSON(IEnumerable<Airport> xxx, string fileName);
    }
}
