#include "bits/stdc++.h"
//#include "iostream"
#define max 10000
using namespace std;
using namespace std::chrono;

int seqKaato(int a[max], int l, int r)
{
  if(l<r)
  {
    if(r-l>=32)
    {
      int mid=(l+r)/2;
      seqKaato(a, l, mid);
      seqKaato(a, mid+1, r);
      inplace_merge(a[0]+l, a[0]+mid+1, a[0]+r+1);
    }
    else
    sort(a[0]+1, a[0]+r+1);
  }
  //auto stop=high_resolution_clock::now();
  //return (int)stop;
  return EXIT_SUCCESS;
}


int seqMerge()
{
  int a[max];

  auto start = high_resolution_clock::now();
  for(int i=0; i<max; i++)
    a[i]=rand()%100;
  seqKaato(a, 0, max-1);
  auto stop=high_resolution_clock::now();
  auto duration=duration_cast<microseconds>(stop-start);
  return duration.count();
}

int main()
{
  cout<<"Time taken for sequential is: "<<seqMerge()<<" ms"<<endl;
}
