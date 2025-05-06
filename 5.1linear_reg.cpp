#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    const int n = 1024;
    float x[n], y[n];

    for(int i=0;i<n;i++){
        x[i] = (i+1)/1024;
        y[i] = 2*x[i] + 3;
    }

    float m=0, c=0, lr=0.01, dm, dc;

    for(int epoch=0;epoch<2000;epoch++){
        dm = 0.0, dc = 0.0;
        #pragma omp parallel for reduction(+:dm, dc)
        for(int i=0;i<n;i++){
            float y_pred = m * x[i] + c;
            float error = y_pred - y[i];

            dm += 2 * x[i] * error / n;
            dc += 2 * error / n;
        }

        m -= lr * dm;
        c -= lr * dc;

        if (epoch % 10 == 0) {
            cout << "Epoch " << epoch << ": m = " << m << ", c = " << c << endl;
        }        
    }

    cout << "Learned m: " << m << ", c: " << c << endl;

    return 0;
}