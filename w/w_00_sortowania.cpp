//00. SORTOWANIA PROSTE
//_________________________

#include <iostream>
#include <ctime>
using namespace std;

const int MAX = 1000000;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//Sortowanie przez wstawianie
void InsertionSort(int t[])
{
    for (int i = 1; i < MAX; i++)
    {
        int x = t[i]; // x - wartość porównywana
        int j = i - 1;
        while (t[j] > x && j >= 0)
        {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = x;
    }
}

//Sortowanie przez wybieranie
void SelectionSort(int t[])
{
    for (int i = 0; i < MAX; i++)
    {
        int k = i;
        for (int j = i + 1; j < MAX; j++)
        {
            if (t[j] < t[k])
                k = j;
        }
        swap(t[i], t[k]);
    }
}

//Sortowanie bąbelkowe
void BubbleSort(int t[])
{
    for (int n = MAX; n > 0; n--)
    {
        for (int i = 0; i < n; i++)
        {
            if (t[i] > t[i + 1])
            {
                swap(t[i], t[i + 1]);
            }
        }
    }
}
int main()
    {
        cout << endl;
        system("pause");
        return 0;
    }
