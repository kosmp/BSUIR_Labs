namespace ClassLibrary
{
    public interface IFileService<T>
    {
        public IEnumerable<T> ReadFile(string fileName);
        public void SaveData(IEnumerable<T> data, string fileName);
    }
}
