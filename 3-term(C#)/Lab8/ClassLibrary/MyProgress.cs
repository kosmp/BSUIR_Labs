namespace ClassLibrary
{
    public class MyProgress<T> : IProgress<T>
    {
        private Action<T> action;

        public MyProgress(Action<T> action)
        {
            this.action = action;
        }   

        public void Report(T value)
        {
            action.Invoke(value);
        }
    }
}
