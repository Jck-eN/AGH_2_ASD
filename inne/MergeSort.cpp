#include <iostream>
#include <ctime>
using namespace std;

const int MAX;

void Merge(int tab[], int p, int mid, int k){
    int left=p, right=mid+1, i=0;
    int *tmp = new int[k-p+1];
    while(left<=mid and right <= k){
        tmp[i++]=(tab[left] <= tab[right] ? tab[left++] : tab[right++]);
    }
    while(left<=mid){
        tmp[i++]=tab[left++];
    }
    while(right<=k){
        tmp[i++]=tab[right++];
    }
    for(int j=0; j<k-p+1; j++){
        tab[p+j]=tmp[j];
    }
}

void MergeSortInt(int tab[], int p, int k){
    if(p!=k){
        int q=(p+k)/2;
        MergeSortInt(tab, p, q);
        MergeSortInt(tab, q+1, k);
        Merge(tab, p, q, k);
    }
}
void MergeSort(int tab[]){
    MergeSortInt(tab, 0, MAX-1);
}



int main()
{
    
    cout << endl;
    system("pause");
    return 0;
}
