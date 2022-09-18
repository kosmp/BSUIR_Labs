using System.IO;

namespace Lab4
{
    public class FileService<T> where T : Car
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
            {
                while (reader.PeekChar() > -1)
                {
                    string modelName = reader.ReadString();
                    string color = reader.ReadString();
                    int maxStockSpeed = reader.ReadInt32();
                    bool isTruck = reader.ReadBoolean();
                    Car readCar = new Car(modelName, color, maxStockSpeed, isTruck);
                    yield return readCar as T;
                }
            }
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            if (File.Exists(fileName))
                File.Delete(fileName);

            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.OpenOrCreate)))
            {
                foreach (T item in data)
                {
                    writer.Write(item.ModelName);
                    writer.Write(item.Color);
                    writer.Write(item.MaxStockSpeed);
                    writer.Write(item.IsTruck);
                }
            }
        }

        public static void Rename(string OldPath, string NewPath)
        {
            if (File.Exists(NewPath))
                File.Delete(NewPath);
            File.Move(OldPath, NewPath);
        }
    }
}
