namespace Lab4
{
    interface IFileService<T>
    {
        IEnumerable<T> ReadFile(string fileName);
        void SaveData(IEnumerable<T> data, string fileName);
    }
}
