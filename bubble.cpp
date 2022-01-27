#include "bits/stdc++.h"
#include "omp.h"
#define max 100000
using namespace std;
using namespace std::chrono;

int sequential()
{
  int a[max];
  auto start = high_resolution_clock::now();

  for(int i=0 ; i<max; i++)
      a[i]=rand()%100;

  for(int i=0; i < max-1; i++)
    for(int j=0; j<max-i-1; j++)
      if(a[j]>a[j+1])
        swap(a[j],a[j+1]);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  return duration.count();
}

int parallel()
{
  int a[max];
  auto start = high_resolution_clock::now();

  #pragma omp parallel for
  for(int i=0; i<max; i++)
    a[i]=rand()%100;

  #pragma omp parallel for
  for(int i=0; i<max-1; i++)
  {
    for(int j=0; j<max-1-i; j++)
    {
      if(a[j]>a[j+1])
      swap(a[j], a[j+1]);
    }
  }
  cout<<"threads: "<<omp_get_max_threads()<<endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  return duration.count();
}

int main()
{
  auto x=sequential(), y=parallel();
  float z = (float)x/(float)y;
  cout<<"Time for sequential is: "<<x<<" ms"<<endl;
  cout<<"Time for parallel is: "<<y<<" ms"<<endl;
  cout<<"Speedup is: "<<z<<" ms"<<endl;
}
