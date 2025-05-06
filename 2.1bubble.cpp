#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;

void seq_sort(vector<int> &arr){
    int n = arr.size();
    for(int i=0;i<n-1;i++){
        bool swapped = false;
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void par_sort(vector<int> &arr){
    int n = arr.size();
    for(int i=0;i<n-1;i++){
        bool swapped = false;
        #pragma omp parallel for num_threads(4)
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        #pragma omp barrier
        if(!swapped) break;
    }
}

int main(){
    int n = 100;
    vector<int> arr;
    for(int i=0;i<n;i++){
        int ele = rand()%100;
        arr.push_back(ele);
    }
    
    auto start = chrono::high_resolution_clock::now();
    par_sort(arr);
    auto end = chrono::high_resolution_clock::now();
    double t = chrono::duration_cast<chrono::microseconds>(end-start).count() / 1e6;
    cout<<t<<endl;
    
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";
}