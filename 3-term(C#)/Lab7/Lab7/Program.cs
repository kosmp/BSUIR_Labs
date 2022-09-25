using Lab7;

public class Program
{
    static void Main(string[] args)
    {
        TestClass test1 = new TestClass();
        Console.CursorVisible = false;

        List<string> listOfResults = new List<string>();
        test1.NotifyEnd += (result, time) =>
        {
            listOfResults.Add("Thread ID: " + Thread.CurrentThread.ManagedThreadId + " Result of calc: " + result + " Time: " + time + " CurrentThreadName: " + Thread.CurrentThread.Name);
        };

        (int id, int progress)[] progressArr = new (int id, int progress)[5] { (0, 0), (0, 0), (0, 0), (0, 0), (0, 0) };
        test1.NotifyInProcess += (currProgress, currThreadID) =>
        {
            bool idIsInArr = false;
            for (int i = 0; i < 5; i++)
            {
                if (progressArr[i].id == currThreadID)
                {
                    progressArr[i].progress = currProgress;
                    idIsInArr = true;
                    break;
                }
            }

            if (idIsInArr == false)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (progressArr[i].id == 0)
                    {
                        progressArr[i].id = currThreadID;
                        progressArr[i].progress = currProgress;
                        break;
                    }
                }
            }

            Console.Clear();
            for (int i = 0; i < 5; i++)
            {
                for (int k = 0; k <= progressArr[i].progress; k++) // draws all 5 as much as they were ready
                {
                    if (k == 0)
                    {
                        Console.Write("\nThread:" + progressArr[i].id + " [");
                        Console.Write($"{k}%");
                        Console.SetCursorPosition(Console.CursorLeft - 2, Console.CursorTop);
                    }
                    else if (k == 100)
                    {
                        Console.SetCursorPosition(Console.CursorLeft - 1, Console.CursorTop);
                        Console.Write("=]");
                        Console.Write($"{progressArr[i].progress}%");
                    }
                    else if (k != 100)
                    {
                        Console.Write($"=>{k}%");
                        string sCurrProgress = k.ToString();
                        Console.SetCursorPosition(Console.CursorLeft - sCurrProgress.Length - 2, Console.CursorTop);
                    }
                }
            }

            int finalCounter = 0;
            for (int i = 0; i < 5; i++)
            {
                if (progressArr[i].progress == 100)
                    finalCounter++;
            }

            if (finalCounter == 5)
            {
                Console.Write("\n");
                foreach (var item in listOfResults)
                    Console.WriteLine(item.ToString());
            }
        };

        Thread thread1 = new Thread(new ThreadStart(test1.calculateSinIntegral));
        thread1.Name = "FirstThread";
        thread1.Priority = ThreadPriority.Lowest;
        thread1.Start();

        Thread thread2 = new Thread(new ThreadStart(test1.calculateSinIntegral));
        thread2.Name = "SecondThread";
        thread2.Priority = ThreadPriority.Highest;
        thread2.Start();

        Thread thread3 = new Thread(new ThreadStart(test1.calculateSinIntegral));
        thread3.Name = "ThirdThread";
        thread3.Start();

        Thread thread4 = new Thread(new ThreadStart(test1.calculateSinIntegral));
        thread4.Name = "FourthThread";
        thread4.Start();

        Thread thread5 = new Thread(new ThreadStart(test1.calculateSinIntegral));
        thread5.Name = "FifthThread";
        thread5.Start();

        // if one by one
        //test1.NotifyInProcess += (progress, threadID) =>
        //{
        //    if (progress == 1)
        //    {
        //        Console.Write("\nThread:" + threadID + " [");
        //    }

        //    if (progress != 100)
        //    {
        //        Console.Write("=>");
        //        int startPos = Console.CursorLeft;
        //        Console.SetCursorPosition(Console.CursorLeft, Console.CursorTop);
        //        Console.Write($"{progress}%");
        //        Console.SetCursorPosition(startPos - 1, Console.CursorTop);
        //    }
        //    else
        //    {
        //        Console.Write($"]{progress}%\n");
        //    }
        //};
    }
}