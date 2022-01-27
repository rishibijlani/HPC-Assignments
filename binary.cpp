#include "bits/stdc++.h"
#include "omp.h"
#define max 10000
using namespace std;
using namespace std::chrono;


int sequential(int arr[], int left, int right, int x)
{
  auto start = high_resolution_clock::now();
  if(right>=left)
  {
    int mid = left + (right-left) /2;
    if(arr[mid]==x)
    {
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop-start);
      //return arr[mid];
      return duration.count();
      //return 'c';
    }

    if (arr[mid]>x)
      return sequential(arr, left, mid-1, x);
      //return 'g';

    return sequential(arr, mid+1, right, x);
    //return '2g';
  }
  return -1;
  //return 'f';
}

int main()
{
  int a[max];
  for(int i=0; i<max; i++)
    a[i]=rand()%100;
  sort(a, a+max);
  //for(int i=0; i<max; i++)
  //cout<<i<<"\t";
  int x=rand()%100;
  cout<<x<<endl;
  cout<<"Time taken for sequential is: "<<sequential(a, 0, max-1, x)<<endl;

}
