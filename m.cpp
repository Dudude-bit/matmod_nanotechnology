#include "iostream"
#include "cmath"

using namespace std;

const long double E_0 = 0.01;
const double t = 0.01;
const unsigned int N = 101;
const double h = 1. / (N - 1);

void furier(double A[N], double B[N]) {
    double sum;
    int k, j;

    for (k = 0; k < N; k++) {
        sum = 0.;
        for (j = 0; j < N; j++) {
            sum += A[j] * sin((j * M_PI * k) / (N - 1.));
        }
        B[k] = sqrt(2. / (N - 1.)) * sum;
    }
}

double P_f(double x) {
    return x * (1. - x);
}

void solver(double C[N], double CSP1[N], double lambda[N], double P_K[N]) {
    for (int i = 1; i < N; i++) {
        CSP1[i] = (C[i] + t * P_K[i]) / (1. + t * lambda[i]);
    }
}

int main() {
    long double E;
    double P[N], P_K[N], W[N], lambda[N], C[N], CSP1[N], WSP1[N], max_el_wsp, max_el_ws;
    int s = 0;

    do {
        for (int i = 0; i < N; i++) {
            W[i] = 0.;
            P[i] = P_f(i / ((double) N - 1.));
            lambda[i] = (4. / pow(h, 2.)) * pow(sin((M_PI * i) / (2. * ((double) N - 1.))), 2);
        }
        furier(P, P_K);
        furier(W, C);

        solver(C, CSP1, lambda, P_K);

        furier(CSP1, WSP1);

        swap(W, WSP1);

        s++;

        max_el_wsp = *max_element(WSP1, WSP1 + N);
        max_el_ws = *max_element(W, W + N);

        E = ((abs(max_el_wsp - max_el_ws)) * 2) / (abs(max_el_wsp) + abs(max_el_ws));

    } while (E_0 < E);
}