#include "bits/stdc++.h"
#include "omp.h"
#define max 100000
//#define intt unsigned long long int
using namespace std;
using namespace std::chrono;

int sequential()
{
  auto start = high_resolution_clock::now();
  //int a[max], b[max], c[max];

  unique_ptr<int[]> a(new int[max]);
  unique_ptr<int[]> b(new int[max]);
  unique_ptr<int[]> c(new int[max]);

  for (int i=0; i<max; i++)
  {
    a[i] = rand()%100;
  }

  for (int i=0; i<max; i++)
  {
    b[i] = rand()%100;
  }

  for (int i=0; i<max; i++)
  {
    c[i] = a[i]+b[i];
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  return duration.count();
}



int parallel()
{
  //int a[max], b[max], c[max];

  auto start = high_resolution_clock::now();

  unique_ptr<int[]> a(new int[max]);
  unique_ptr<int[]> b(new int[max]);
  unique_ptr<int[]> c(new int[max]);


  #pragma omp parallel for
  for (int i=0; i<max; i++)
  {
    a[i] = rand()%100;
  }

  //auto start = high_resolution_clock::now();
  //int i;
  #pragma omp parallel for
  //#pragma omp parallel for shared (a,b,c) private(i) schedule(static)
  for (int i=0; i<max; i++)
  {
    //a[i] = rand()%420;
    b[i] = rand()%100;
  }

  int *ptr1 = &a[0], *ptr2=&b[0], *ptr3=&c[0];

  #pragma omp parallel for
  for(int i=0; i<max; i++)
  {
    *ptr3 = *ptr1 + *ptr2;
    ptr1++, ptr2++, ptr3++;
    //c[i] = a[i] + b[i];
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  return duration.count();
}

int main()
{
  auto x=sequential(), y=parallel();
  float z = (float)x/(float)y;
  cout<<"Time taken for sequential is: "<<x<<" microseconds"<<endl;
  cout<<"Time taken for parallel is: "<<parallel()<<" microseconds"<<endl;
  cout<<"Speedup is: "<<z<<endl;
}
