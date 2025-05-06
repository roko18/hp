#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

float sigmoid(float z) {
    return 1 / (1 + exp(-z));
}

int main(){
    const int n = 1024;
    float x[n], y[n];

    for (int i = 0; i < n; ++i) {
        x[i] = (i + 1) / 1024;
        y[i] = (x[i] > 0.5) ? 1 : 0;
    }

    float m=0, c=0, lr=0.1, dm, dc;

    for(int epoch=0;epoch<1000;epoch++){
        dm = 0.0, dc = 0.0;
        #pragma omp parallel for reduction(+:dm, dc)
        for(int i=0;i<n;i++){
            float z = m * x[i] + c;
            float y_pred = sigmoid(z);
            float error = y_pred - y[i];

            dm +=  x[i] * error / n;
            dc +=  error / n;
        }

        m -= lr * dm;
        c -= lr * dc;

        if (epoch % 10 == 0) {
            cout << "Epoch " << epoch << ": m = " << m << ", c = " << c << endl;
        }        
    }

    cout << "Learned m: " << m << ", c: " << c << endl;


}