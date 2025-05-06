#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right){
    int n1 = mid-left+1;
    int n2 = right-mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
  
    for (int i = 0; i < n1; ++i) {
      leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
      rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
      if (leftArr[i] <= rightArr[j]) {
        arr[k++] = leftArr[i++];
      } else {
        arr[k++] = rightArr[j++];
      }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }    
}

void mergeSortRecursive(vector<int>& arr, int left, int right) {
    if (left < right) {
      int mid = left + (right - left) / 2;
      mergeSortRecursive(arr, left, mid);
      mergeSortRecursive(arr, mid + 1, right);
      merge(arr, left, mid, right);
    }
}

void mergeSortParallel(vector<int>& arr, int left, int right) {
    if (left < right) {
      int mid = left + (right - left) / 2;
      #pragma omp task firstprivate(arr, left, mid)
      mergeSortParallel(arr, left, mid);
      #pragma omp task firstprivate(arr, mid + 1, right)
      mergeSortParallel(arr, mid + 1, right);
      #pragma omp taskwait
      merge(arr, left, mid, right);
    }
}

int main(){
    int n = 100000;
    vector<int> arr;
    for(int i=0;i<n;i++){
        int ele = rand()%1000000;
        arr.push_back(ele);
    }
    
    auto start = chrono::high_resolution_clock::now();
    mergeSortParallel(arr, 0, n-1);
    auto end = chrono::high_resolution_clock::now();
    double t = chrono::duration_cast<chrono::microseconds>(end-start).count() / 1e6;
    cout<<t<<endl;
    
    // for(int i=0;i<n;i++) cout<<arr[i]<<" ";
}