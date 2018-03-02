using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace InsertionSortCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = { 50, 40, 30, 60, 35, 45, 9, 33, 5, 25 };
            Task t = InsertionSort(a);
            foreach (var e in a)
            {
                // Chances are, this gets printed un-sorted, or even half-sorted
                // Strange part is .. if you remove these two commented lines
                // it affects how to program behaves
                Debug.Write(string.Format("{0}, ", e));
            }
            Debug.WriteLine(".");
            t.Wait();
            // But for sure after t.Wait() this wil be sorted
            foreach (var e in a) 
            {
                Debug.Write(string.Format("{0}, ", e));
            }
        }

        static async Task InsertionSort(int []a)
        {
            // There is a slightly different variant which is more efficient
            // https://en.wikipedia.org/wiki/Insertion_sort

            await Task.Run(() =>
            {
                int len = a.Length;
                for (int i = 0; i < len; i++)
                {
                    for (int j = i; j > 0; j--)
                    {
                        if (a[j] > a[j - 1])
                        {
                            int temp = a[j];
                            a[j] = a[j - 1];
                            a[j - 1] = temp;
                        }
                    }
                }
            });
        }
    }
}
