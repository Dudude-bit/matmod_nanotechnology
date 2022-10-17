#include "math.h"
#include "iostream"

using namespace std;


float F(float x) {
    return (10 - x) * x * exp(-pow(x, 0.5));
}

long double g(float i, float k, float N) {
    return sqrt(2 / N) * sin((M_PI / N) * i * k);
}

int main() {
    int N = 8;
    float a = 0, b = 10;
    long double A[N][N], A_T[N][N], f[N], x[N], Y[N], E[N], D[N];
    long double sum = 0;
    float h = (b - a) / N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            A[i][j] = g(i, j, N);
            A_T[j][i] = A[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        x[i] = i * h;
    }

    for (int i = 0; i < N; i++) {
        f[i] = F(x[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            Y[i] += A[i][j] * f[j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            E[i] += A_T[i][j] * Y[j];
        }
    }

    for (int i = 0; i < N; i++) {
        D[i] = E[i] - f[i];
    }

    for (int j = 0; j < N; j++) {
        sum += A[5][j] * A[5][j];
    }
    cout << sum;
}