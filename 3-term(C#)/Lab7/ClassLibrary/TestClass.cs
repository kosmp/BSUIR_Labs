using System.Diagnostics;

namespace ClassLibrary
{
    public class TestClass
    {
        static Semaphore sem = new Semaphore(2, 2);
        static Mutex mtx = new Mutex();

        public delegate void CulcHandler(double computedIntegral, string funcExecutionTime);
        public event CulcHandler NotifyEnd;
        public delegate void ProcessHandler(int progress, int threadID);
        public event ProcessHandler NotifyInProcess;

        public void calculateSinIntegral()
        {
            sem.WaitOne();
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            double h = 0.00000001;  // step
            double res = 0;
            for (double i = 0; i < 1.00000001; i += 0.00000001)
            {
                res += h * Math.Sin(i);
                for (int k = 1; k <= 100000; k++) ;  // from condition

                int t = Convert.ToInt32(i * 100000000);
                if (t != 0 && (t % 1000000 == 0 || t % 100000000 == 0)) // checking if i is two digit int
                {
                    mtx.WaitOne();
                    NotifyInProcess?.Invoke(Convert.ToInt32(i * 100), Thread.CurrentThread.ManagedThreadId);
                    mtx.ReleaseMutex();
                }
                else if (t == 0)
                {
                    mtx.WaitOne();
                    NotifyInProcess?.Invoke(Convert.ToInt32(0), Thread.CurrentThread.ManagedThreadId);
                    mtx.ReleaseMutex();
                }
            }
            stopWatch.Stop();
            TimeSpan ts = stopWatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}", ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds / 10);
            NotifyEnd?.Invoke(res, elapsedTime);
            sem.Release();
        }
    }
}