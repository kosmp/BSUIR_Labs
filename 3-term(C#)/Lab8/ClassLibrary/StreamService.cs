using System;
using System.Collections;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json;
using JsonSerializer = System.Text.Json.JsonSerializer;

namespace ClassLibrary
{
    public class StreamService<T>
    {
        private IProgress<int> progressbar1 = new MyProgress<int>(percent => Console.Write($"\rThread: {Thread.CurrentThread.ManagedThreadId} Writing to stream: {(int)percent}%"));
        private IProgress<int> progressbar2 = new MyProgress<int>(percent => Console.Write($"\rThread: {Thread.CurrentThread.ManagedThreadId} Copying to stream: {(int)percent}%"));

        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data)
        {
            Console.WriteLine($"\nWriting started. ThreadID: {Thread.CurrentThread.ManagedThreadId}");

            int count = 0;
            await stream.WriteAsync(Encoding.ASCII.GetBytes("["));
            foreach (var item in data)
            {
                if (count != 0) await stream.WriteAsync(Encoding.ASCII.GetBytes(","));
                count++;
                progressbar1.Report(count * 100 / data.Count());
                await JsonSerializer.SerializeAsync(stream, item);
            }
            await stream.WriteAsync(Encoding.ASCII.GetBytes("]"));

            stream.Position = 0;
            Console.WriteLine($"\nWriting finished. ThreadID: {Thread.CurrentThread.ManagedThreadId}\n");
        }

        public async Task CopyFromStreamAsync(Stream stream, string fileName)
        {
            Console.WriteLine($"\nСopying started. ThreadID: {Thread.CurrentThread.ManagedThreadId}");
            var buffer = new byte[100];
            var streamLen = stream.Length;
            var currNumOfBytes = 0;
            await using (Stream fs = new FileStream(fileName, FileMode.Create))
            {
                int read;
                while ((read = await stream.ReadAsync(buffer, 0, buffer.Length)) > 0)
                {
                    currNumOfBytes += read;
                    await Task.Delay(1);
                    await fs.WriteAsync(buffer, 0, read);
                    progressbar2.Report((int)(currNumOfBytes * 100 / streamLen));
                }       
            }
            Console.WriteLine($"\nCopying finished. ThreadID: {Thread.CurrentThread.ManagedThreadId}\n");
        }

        public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
        {
            Console.WriteLine($"GetStatisticsAsync running on a thread with ThreadID: {Thread.CurrentThread.ManagedThreadId}");
            int count = 0;
            using (FileStream fs = new FileStream(fileName, FileMode.Open))
            {
                var cars = await JsonSerializer.DeserializeAsync<T[]>(fs);

                if (cars != null)
                {
                    foreach (var car in cars)
                        if (filter(car))
                            count++;
                }
            }
            return count;
        }
    }
}
