#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using namespace std::chrono;

struct Point {
    int x, y, c;
};

double cal_dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void kmeansseq(vector<Point>& points, vector<Point>& centroids, int k, int n){
    bool isChanged = true;
    while(isChanged){
        isChanged = false;

        for(int i=0;i<n;i++){
            double mindist = DBL_MAX;
            int bc = -1;
            for(int j=0;j<k;j++){
                double dist = cal_dist(points[i], centroids[j]);
                if(dist<mindist){
                    mindist = dist;
                    bc = j;
                }
            }
            if(points[i].c != bc){
                points[i].c = bc;
                isChanged = true;
            }
        }

        vector<double> sumx(k, 0), sumy(k, 0);
        vector<int> count(k, 0);

        for(int i=0;i<n;i++){
            int cluster = points[i].c;
            sumx[cluster] += points[i].x;
            sumy[cluster] += points[i].y;
            count[cluster] ++;
        }

        for(int i=0;i<k;i++){
            if(count[i]>0){
                centroids[i].x = sumx[i] / count[i];
                centroids[i].y = sumy[i] / count[i];
            }
        }
    }
}

void kmeanspar(vector<Point>& points, vector<Point>& centroids, int k, int n) {
    bool changed = true;
    while (changed) {
        changed = false;

        #pragma omp parallel for shared(points, centroids)
        for (int i = 0; i < n; i++) {
            double mindist = DBL_MAX;
            int bcluster = -1;
            for (int j = 0; j < k; j++) {
                double dist = cal_dist(points[i], centroids[j]);
                if (dist < mindist) {
                    mindist = dist;
                    bcluster = j;
                }
            }
            if (points[i].c != bcluster) {
                points[i].c = bcluster;
                #pragma omp atomic write
                changed = true;
            }
        }

        vector<double> sumx(k, 0), sumy(k, 0);
        vector<int> count(k, 0);

        #pragma omp parallel for shared(points)
        for (int i = 0; i < n; i++) {
            int c = points[i].c;
            #pragma omp atomic
            sumx[c] += points[i].x;
            #pragma omp atomic
            sumy[c] += points[i].y;
            #pragma omp atomic
            count[c]++;
        }

        #pragma omp parallel for shared(centroids)
        for (int j = 0; j < k; j++) {
            if (count[j] > 0) {
                centroids[j].x = sumx[j] / count[j];
                centroids[j].y = sumy[j] / count[j];
            }
        }
    }
}

int main(){
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    int k = 3;
    vector<Point> points(n);
    vector<Point> centroids(k);

    for (int i = 0; i < n; i++) {
        points[i].x = rand() % 1000;
        points[i].y = rand() % 1000;
        points[i].c = -1;
    }
    
    for (int i = 0; i < k; i++) {
        centroids[i] = points[rand() % n];
    }

    auto start = high_resolution_clock::now();
    kmeansseq(points, centroids, k, n);
    auto end = high_resolution_clock::now();
    cout << "Sequential k-Means time: " << duration_cast<microseconds>(end - start).count() << " ms" << endl;    
 
    // Reset centroids for parallel version
    for (int i = 0; i < k; i++) {
        centroids[i] = points[rand() % n];
    }
    for (int i = 0; i < n; i++) {
        points[i].c = -1;
    }

    start = high_resolution_clock::now();
    kmeanspar(points, centroids, k, n);
    end = high_resolution_clock::now();
    cout << "Parallel k-Means time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}

