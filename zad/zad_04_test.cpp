#include <iostream>
using namespace std;

int Partition(int t[], int p, int &r, int med){
    int i, j;
    i=p-1;
    for(j=p; j<=r; j++){
        if(t[j]<med){
            i++;
            swap(t[j], t[i]);
        }
    }
    int l=i;
    for(int k=i+1; k<=r; k++){ //Ponowne partition dla równych i większych
        if(t[k]==med){
            l++;
            swap(t[k], t[l]);
        }
    }
    r=l+1;      //bigger_index (reference)
    return i+1; // equal_index
}

int MedianFromSelectionSort(int t[], int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        int min = i;
        for (int j = i + 1; j <=r; j++)
        {
            if (t[j] < t[min])
                min = j;
        }
        swap(t[i], t[min]);
    }
    return t[(r+l)/2];
}
int main()
{
    
    int t[10] = {10, 2, 3, 4, 5, 5, 9, 8, 5, 1};
    int n=9;
    int equal =  MedianFromSelectionSort(t, 5, 9);
    cout << equal <<endl;
    system("pause");
    return 0;
}
