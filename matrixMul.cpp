#include "bits/stdc++.h"
#include "omp.h"
#define N 800
using namespace std;
using namespace std::chrono;

int sequential()
{
    int a[N][N], b[N][N], c[N][N];
    auto start = high_resolution_clock::now();

    for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)
      {
        a[i][j] = rand()%100;
      }
    }

    for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)
      {
        b[i][j] = rand()%100;
      }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

int parallel()
{
  int a[N][N], b[N][N], c[N][N];

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    for (int j=0; j<N; j++)
    {
      a[i][j]=rand()%100;
    }
  }

  auto start = high_resolution_clock::now();

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    for (int j =0; j<N; j++)
    {
      b[i][j]=rand()%100;
    }
  }

  #pragma omp parallel for
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      c[i][j] = 0;
      for (int k=0; k<N; k++)
      {
        c[i][j] += a[i][k]*b[k][j];
      }
    }
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  return duration.count();
}

int main()
{
  auto x=sequential(), y=parallel();
  float z = (float)x/(float)y;
  cout<<"Time for sequential is: "<<x<<" microseconds"<<endl;
  cout<<"Time taken for parallel is: "<<y<<" microseconds"<<endl;
  cout<<"Speedup is: "<<z<<endl;
}
