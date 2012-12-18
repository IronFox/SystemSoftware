/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package threads;

import com.sun.org.apache.xml.internal.resolver.helpers.Debug;
import java.io.Console;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;

/**
 *
 * @author ironfox
 */
public class Threads {

    
    static class Calculator extends Thread
    {
        static int NumNumbers = 600000;
        @Override
        public void run()
        {
            int[] primes = new int[NumNumbers];
            long started = System.nanoTime();
            int found_primes = 0;
            for (int i = 2; i < NumNumbers; i++)
            {
                boolean is_prime = true;
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
            long elapsed = System.nanoTime() - started;
            System.out.println("Calculator thread (thread " + Thread.currentThread().getId() + ") finished after " + (float)elapsed/1000/1000/1000 + " seconds");
        }
    }
    

    static class Writer extends Thread
    {
        static int NumChunks = 200;
        @Override
        public void run()
        {
            File temp;
            FileWriter fileoutput;
            try
            {
                temp = File.createTempFile("temp",".txt");
                fileoutput = new FileWriter(temp);

                char[] chunk = new char[1000000];
                for (int i = 0; i < chunk.length; i++)
                    chunk[i] = (char)i;

                long started = System.nanoTime();
                for (int i = 0; i < NumChunks; i++)
                {
                    fileoutput.write(chunk, 0, chunk.length);
                    fileoutput.flush();
                }

                long elapsed = System.nanoTime() - started;
                System.out.println("Writer thread (thread " + Thread.currentThread().getId() + ") finished after " + (float)elapsed/1000/1000/1000 + " seconds");
                fileoutput.close();
                temp.delete();
            }
            catch (IOException ex)
            {
                System.out.println(ex);
            }
        }
    }
    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException
    {
        
        Calculator[] calc = new Calculator[8];
        Writer[] io = new Writer[1];

        for (int i = 0; i < calc.length; i++)
        {
            calc[i] = new Calculator();
            calc[i].start();
        }
        for (int i = 0; i < io.length; i++)
        {
            io[i] = new Writer();
            io[i].start();
        }

        for (int i = 0; i < calc.length; i++)
        {
            calc[i].join();
        }
        for (int i = 0; i < io.length; i++)
        {
            io[i].join();
        }

    }
}
