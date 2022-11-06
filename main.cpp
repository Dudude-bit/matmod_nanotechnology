#include "iostream"
#include "fstream"
#include "cmath"

using namespace std;

const long double E_0 = 0.0000000001;
const double t = 0.01;
const unsigned int N = 101;
const double h = 1. / (N - 1);

void writeToFile(double arr[N], double s, const string& fileName) {
    ofstream file(fileName);

    for (int i = 0; i < N; i++) {
        file << arr[i] << endl;
    }
    file << "Number of iterations: " << s;
}

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

double P_f(double x, double time) {
    return (x*x*x - 4*x*x + 3*x)*exp(1.-time);
}

void solver(const double C[N], double CSP1[N], const double lambda[N], const double P_K[N]) {
    for (int i = 1; i < N; i++) {
        CSP1[i] = (C[i] + t * P_K[i]) / (1. + t * lambda[i]);
    }
}

double MaxByAbsV(double arr[N]) {
    double max_v = abs(arr[0]);

    for (int i = 1; i < N; i++) {
        max_v = max(max_v, abs(arr[i]));
    }

    return max_v;
}

int main() {
    long double E;
    double P[N], P_K[N], W[N], lambda[N], C[N], CSP1[N], WSP1[N];
    int s = 0;

    for (int i = 0; i < N; i++) {
        W[i] = 0.;
        lambda[i] = (4. / (h*h)) * pow(sin((M_PI * i) * h / 2.), 2.);
    }

    do {
        for (int i = 0; i < N; i++) {
            P[i] = P_f(i * h, s * t);
        }
        furier(P, P_K);

        furier(W, C);

        solver(C, CSP1, lambda, P_K);

        furier(CSP1, WSP1);

        swap(W, WSP1);

        s++;

        E = (abs((MaxByAbsV(WSP1) - MaxByAbsV(W))) * 2) / (MaxByAbsV(WSP1) + MaxByAbsV(W));
    } while (E_0 < E);

    writeToFile(W, s, "../file.txt");
}