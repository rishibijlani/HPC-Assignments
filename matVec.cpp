#include "bits/stdc++.h"
#include "omp.h"
#define N 1000
using namespace std;
using namespace std::chrono;

int sequential()
{
  int a[N][N], b[N], c[N];
  auto start = high_resolution_clock::now();

  for(int i=0; i<N; i++)
  {
    b[i]=rand()%100;
    for (int j=0; j<N; j++)
    {
      a[i][j]=rand()%100;
    }
  }

  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      c[i] += a[i][j]*b[j];
    }
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  return duration.count();
}

int parallel()
{
  int a[N][N], b[N], c[N];

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      a[i][j]=rand()%100;
    }
  }

  auto start = high_resolution_clock::now();

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    b[i]=rand()%100;
  }

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      c[i] += a[i][j]*b[j];
    }
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  return duration.count();
}

int main()
{
  auto x=sequential(), y=parallel();
  float z=(float)x/(float)y;
  cout<<"Time for sequential is: "<<x<<" microseconds"<<endl;
  cout<<"Time for parallel is: "<<y<<" microseconds"<<endl;
  cout<<"Speedup is: "<<z<<endl;
  return EXIT_SUCCESS;
}
