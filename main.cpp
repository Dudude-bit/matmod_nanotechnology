#include "iostream"
#include "cmath"

using namespace std;
const double PI = 3.141592653589793;

const double t = 0.01;

const unsigned int N = 101;
const double h = 1. / (N - 1);

void furier(double A[N], double B[N]) {
    double sum;
    int k, j;

    for (k = 0; k < N; k++) {
        sum = 0.;
        for (j = 0; j < N; j++) {
            sum += A[j] * sin((j * PI * k) / (N - 1.));
        }
        B[k] = sqrt(2. / (N - 1.)) * sum;
    }
}

double solver(double C_I, double P_K_I, double LAMBDA_I) {
    return (C_I + t * P_K_I) / (1. + t * LAMBDA_I);
}


double P_f(double x) {
    return x * (1. - x);
}

int main() {
    double W[N], C[N], P[N], P_K[N], CSP1[N], WSP1[N], lambda[N];

    for (int i = 0; i < N; i++) {
        W[i] = 0.;
        P[i] = P_f(i / ((double)N - 1.));
        lambda[i] = (4. / pow(h, 2.)) * pow(sin((PI * i) / (2. * ((double)N - 1.))), 2);
    }

    furier(P, P_K);

    for (int k = 1; k < N; k++) {
        furier(W, C);
    }

    for (int i = 1; i < N; i++) {
        CSP1[i] = solver(C[i], P_K[i], lambda[i]);
    }

    furier(CSP1, WSP1);

    for (int i = 1; i < N; i++) {
        W[i] = WSP1[i];
    }

    for (int i = 0; i < N; i++) {
        cout << W[i] << endl;
    }
}