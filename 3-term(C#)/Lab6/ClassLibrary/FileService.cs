using System.Text.Json;

namespace ClassLibrary
{
    public class FileService<T> : IFileService<T>
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.Open))
            {
                IEnumerable<T>? objects = JsonSerializer.Deserialize<IEnumerable<T>>(fs);
                if (objects != null)
                {
                    foreach (var item in objects)
                        yield return item;
                }
            }
        }
        
        public void SaveData(IEnumerable<T> data, string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.Create))
            {
                var options = new JsonSerializerOptions { WriteIndented = true };
                JsonSerializer.Serialize(fs, data, options);
            }
        }
    }
}