#include "bits/stdc++.h"
#define max 10000
using namespace std;
using namespace std::chrono;

int sequential()
{
  int a[max];
  auto start = high_resolution_clock::now();

  for(int i=0; i<max; i++)
    a[i]=rand()%100;

  //auto breakShit(int[], int l, int r)
  auto breakShit = [=](int[], int l, int r)
  {
    if(l<r)
    {
      if(r-l>=32)
      {
        int mid=(l+r)/2;
        breakShit(a[], l, mid);
        breakShit(a[], mid+1, r);
        inplace_merge(a[0]+l, a[0]+mid+1, a[0]+r+1);
      }
      else
      {
        sort(a[0]+l, a[0]+r+1);
      }
    }
    return EXIT_SUCCESS;
  };

  auto mergeSort = [=](int[])
  {
    breakShit(a[], 0, max-1)
    return 0;
  };

  mergeSort(a[]);

  return a[0];
}

int main()
{
  cout<<": "sequential()<<endl;
}
