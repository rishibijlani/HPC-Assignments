#include "bits/stdc++.h"
#include "omp.h"
#define max 123456
using namespace std;
using namespace std::chrono;

int main()
{
  vector<long long> v1(max);

  for(long long i=0; i<max; i++)
  {
    v1.push_back(rand()%100);
  }

  auto start = high_resolution_clock::now();

  vector<long long> v2(max);
  #pragma omp parallel for
  for(long long i=0; i<max; i++)
  {
    v2.push_back(rand()%100);
  }

  #pragma omp parallel
  std::transform (v1.begin(), v1.end(), v2.begin(), v2.begin(), plus<long long>());

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);

  //cout<<"time taken is: "<<duration.count()<<" ms"<<endl;
  return EXIT_SUCCESS;
}
