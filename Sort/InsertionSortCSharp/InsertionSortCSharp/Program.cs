using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InsertionSortCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = { 50, 40, 30, 60, 35, 45, 9, 33, 5, 25 };
            InsertionSort(a);
            foreach (var e in a) 
            {
                Debug.WriteLine(e);
            }
        }

        static void InsertionSort(int []a)
        {
            // There is a slightly different variant which is more efficient
            // https://en.wikipedia.org/wiki/Insertion_sort
            int len = a.Length;
            for (int i=0; i<len; i++)
            {
                for (int j = i; j > 0; j--)
                {
                    if (a[j] > a[j-1])
                    {
                        int temp = a[j];
                        a[j] = a[j-1];
                        a[j-1] = temp;
                    }
                }
            }
        }
    }
}
