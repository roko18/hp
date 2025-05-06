#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;

void min_reduction(vector<int> arr, int n) {
    int min_value = INT_MAX;  
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
      if (arr[i] < min_value) {
        min_value = arr[i];  
      }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int> arr, int n) {
    int max_value = INT_MIN;  
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
      if (arr[i] > max_value) {
        max_value = arr[i]; 
      }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
      sum += arr[i];  
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
      sum += arr[i];  
    }
    double average = (double)sum / (n - 1);
    cout << "Average: " << average << endl;
}

int main(){
    int n = 100;
    vector<int> arr;
    for(int i=0;i<n;i++){
        int ele = rand()%100;
        arr.push_back(ele);
    }
    
    auto start = chrono::high_resolution_clock::now();
    max_reduction(arr, n);
    auto end = chrono::high_resolution_clock::now();
    double t = chrono::duration_cast<chrono::microseconds>(end-start).count() / 1e6;
    cout<<t<<endl;
    
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";
}