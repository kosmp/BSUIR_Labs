namespace Lab4
{
    public class MyCustomComparer<T> : IComparer<T> where T : Car
    {
        public int Compare(T? x, T? y)
        {
            if (x == null || y == null)
                throw new ArgumentNullException(nameof(x) + ", " + nameof(y));

            return String.Compare(x.ModelName, y.ModelName, StringComparison.Ordinal);
        }
    }
}
