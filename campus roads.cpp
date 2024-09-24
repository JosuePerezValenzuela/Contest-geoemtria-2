#include <bits/stdc++.h>

using namespace std;

struct Punto {
    double x, y;
};

double distancia(const Punto& p1, const Punto& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Punto interpolar(const Punto& p1, const Punto& p2, double t) {
    return {p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y)};
}

int main() {
    int N;
    cin >> N;
    for (int carretera = 1; carretera <= N; ++carretera) {
        int K, T;
        cin >> K >> T;
        vector<Punto> puntos(K);
        for (int i = 0; i < K; ++i) {
            cin >> puntos[i].x >> puntos[i].y;
        }

        double longitudTotal = 0;
        vector<double> longitudes(K - 1);
        for (int i = 0; i < K - 1; ++i) {
            longitudes[i] = distancia(puntos[i], puntos[i + 1]);
            longitudTotal += longitudes[i];
        }

        double intervalo = longitudTotal / (T - 1);
        cout << "Road #" << carretera << ":\n";
        double acumulado = 0;
        int segmento = 0;
        for (int t = 0; t < T; ++t) {
            while (segmento < K - 1 && acumulado + longitudes[segmento] < t * intervalo) {
                acumulado += longitudes[segmento++];
            }

            double restante = t * intervalo - acumulado;
            Punto arbol;
            if (segmento < K - 1) {
                arbol = interpolar(puntos[segmento], puntos[segmento + 1], restante / longitudes[segmento]);
            } else {
                arbol = puntos[K - 1];
            }
            cout << fixed << setprecision(2) << arbol.x << " " << arbol.y << "\n";
        }
        cout << endl;
    }
    return 0;
}