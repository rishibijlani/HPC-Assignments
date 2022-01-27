#include "bits/stdc++.h"
#include "omp.h"
#define max 25431

using namespace std;
using namespace std::chrono;

void divergeSort(vector<int>& v, int left, int right)
{
  if(left<right)
  {
    int mid = (left+right)/2;
    divergeSort(v, left, mid);
    divergeSort(v, mid+1, right);
    inplace_merge(v.begin()+left, v.begin()+mid+1, v.begin()+right+1);
  }
}

void mergeSort(vector<int>& v)
{
  divergeSort(v, 0, v.size()-1);
}


void paraDivSort(vector<int>& v, int left, int right)
{
  if(left<right)
  {
    if(right - left >= 32)
    {
      int mid = (left+right)/2;
      #pragma omp taskgroup
      {
        #pragma omp task shared(v)
        paraDivSort(v, left, mid);
        //#pragma omp task shared(v) untied if(right-left >= (1<<14))
        paraDivSort(v, mid+1, right);
        //#pragma omp taskyield
      }
    inplace_merge(v.begin()+left, v.begin()+mid+1, v.begin()+right+1);
    }
  else{
  sort(v.begin()+left, v.begin()+right+1);}
  }
}
void paraMerSort(vector<int>& v)
{
  #pragma omp parallel
  #pragma omp single
  paraDivSort(v, 0, v.size()-1);
}


int main()
{
  //vector<int> vect{10, 20, 05, 15, 25};
  vector<int> vect(max);
  for(int i : vect)
  vect.push_back(rand()%100);
  auto start = high_resolution_clock::now();
  mergeSort(vect);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  int x = duration.count();
  cout<<"Time taken for sequential exec is: "<<duration.count()<<" ms"<<endl;

  auto start2 = high_resolution_clock::now();
  paraMerSort(vect);
  auto stop2 = high_resolution_clock::now();
  auto duration2 = duration_cast<microseconds>(stop2 - start2);
  int y=duration2.count();
  cout<<"Time taken for parallel exec is: "<<y<<" ms"<<endl;

  float z = (float)x/(float)y;
  cout<<"Speedup: "<<z<<endl;
  return 0;
}
