using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System.IO;


namespace BurstThreads
{

    class Calculator
    {
        const int NumNumbers = 800000;
        public void Process()
        {
            Stopwatch watch = new Stopwatch();
            int[] primes = new int[NumNumbers];
            watch.Start();
            int found_primes = 0;
            for (int i = 2; i < NumNumbers; i++)
            {
                bool is_prime = true;
                for (int j = 0; j < found_primes / 2; j++)
                    if ((i % primes[j]) == 0)
                    {
                        is_prime = false;
                        break;
                    }
                if (!is_prime)
                    continue;
                primes[found_primes++] = i;
            }
            watch.Stop();
            Console.WriteLine("Calculator thread (thread " + Thread.CurrentThread.ManagedThreadId + ") finished after " + watch.Elapsed);

        }

    }


    class Writer
    {
        const int NumChunks = 1000;
        public void Process()
        {
            Stopwatch watch = new Stopwatch();

            string path = Path.GetTempFileName();

            try
            {
                FileStream fileStream = new FileStream(path, FileMode.Truncate);
                Debug.Assert(fileStream.CanWrite);

                byte[] chunk = new byte[1000000];
                for (int i = 0; i < chunk.Count(); i++)
                    chunk[i] = (byte)i;

                watch.Start();

                fileStream.SetLength(0);
                for (int i = 0; i < NumChunks; i++)
                {
                    fileStream.Write(chunk, 0, chunk.Count());
                    fileStream.Flush();
                }

                watch.Stop();
                Console.WriteLine("Writer thread (thread " + Thread.CurrentThread.ManagedThreadId + ") finished after " + watch.Elapsed);

                fileStream.Close();
                File.Delete(path);
            }
            catch (IOException except)
            {
                Console.WriteLine(except.ToString());
            }
        }

    }


    class Program
    {
        static void Main(string[] args)
        {
            Calculator[] calc = new Calculator[8];
            Writer[] io = new Writer[1];





            Thread[] threads = new Thread[calc.Count() + io.Count()];

            for (int i = 0; i < calc.Count(); i++)
            {
                calc[i] = new Calculator();
                Thread thread = new Thread(new ThreadStart(calc[i].Process));
                thread.Start();
                threads[i] = thread;
            }
            for (int i = 0; i < io.Count(); i++)
            {
                io[i] = new Writer();
                Thread thread = new Thread(new ThreadStart(io[i].Process));
                thread.Start();
                threads[i + calc.Count()] = thread;
            }


            for (int i = 0; i < threads.Count(); i++)
            {
                threads[i].Join();
            }


        }
    }
}
