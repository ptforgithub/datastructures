using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BubbleSort
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = { 50, 60, 40, 30, 55, 25, 5, 9, 35, 6 };
            int countSecondSort = 4;
            int[] b = new int[countSecondSort];

            Task t = BubbleSort(a, CompareAscending, 
                (e, index) => {
                    if (index >= countSecondSort)
                        return;
                    b[index] = e;
                    for (int i=index; i>0; i--)
                    {
                        if (b[i] > b[i-1])
                        {
                            int temp = b[i];
                            b[i] = b[i - 1];
                            b[i - 1] = temp;
                        }
                    }
                });
            t.Wait();

            Print(a);
            for (int i=0; i<countSecondSort; i++)
            {
                a[i] = b[i];
            }
            Print(a);
        }

        static void Print(int []a)
        {
            for (int i = 0; i < a.Length; i++)
            {
                Debug.Write(string.Format("{0}, ", a[i]));
            }
            Debug.WriteLine("");
        }

        static async Task BubbleSort(int [] a, Func<int, int, bool> Compare, Action<int, int> SecondFunc)
        {
            await Task.Run(() =>
            {
                int len = a.Length;
                for (int i = 0; i < len - 1; i++)
                {
                    for (int j = i + 1; j < len; j++)
                    {
                        if (Compare(a[i], a[j]))
                        {
                            int t = a[i];
                            a[i] = a[j];
                            a[j] = t;
                        }
                    }
                    SecondFunc(a[i], i);
                }
            });
        }

        static bool CompareAscending(int a, int b)
        {
            return a > b;
        }

        static bool CompareDescending(int a, int b)
        {
            return a < b;
        }

        static void Swap(ref int a, ref int b)
        {
            int t = a;
            a = b;
            b = t;
        }
    }
}
