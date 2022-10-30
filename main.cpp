#include "iostream"
#include "cmath"

using namespace std;

const long double t = 1 / 20;

const unsigned int N = 101;

void furier(long double A[N], long double B[N]) {
    long double sum;
    int k, j;

    for (k = 0; k < N; k++) {
        sum = 0.;
        for (j = 0; j < N; j++) {
            sum += A[j] * sin((j * M_PI * k) / (N - 1));
        }
        B[k] = sqrt(2. / (N - 1.)) * sum;
    }
}


long double P_f(long double x) {
    return x * (1. - x);
}

int main() {
//    int S = 0;
    long double W[N], C[N], P[N], P_K[N], CSP1[N], WSP1[N], lambda[N];

    for (int i = 0; i < N; i++) {
        W[i] = 0.;
        C[i] = 0.;
        P[i] = P_f((i / ((long double) N - 1.)));
        lambda[i] = (4. / pow((long double) N - 1., 2.)) * sin((M_PI * (long double) N) / (2. * ((long double) N - 1.)));
    }

    furier(P, P_K);

    for (int k = 1; k < N; k++) {
        furier(W, C);
    }

    for (int i = 1; i < N; i++) {
        CSP1[i] = (C[i] + t * P_K[i]) / (1. + t * lambda[i]);
    }

    furier(CSP1, WSP1);

    for (int i = 1; i < N; i++) {
        W[i] = WSP1[i];
    }

    for (int i = 0; i < N; i++) {
        cout << W[i] << endl;
    }
}