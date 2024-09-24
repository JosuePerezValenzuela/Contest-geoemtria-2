#include <bits/stdc++.h>

using namespace std;

struct Punto {
    int x, y;
};

bool estaDentro(const vector<Punto>& poligono, const Punto& p) {
    int cruces = 0;
    for (size_t i = 0; i < poligono.size(); ++i) {
        Punto p1 = poligono[i];
        Punto p2 = poligono[(i + 1) % poligono.size()];

        if (p1.y == p2.y) {
            if (p.y == p1.y && min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x)) {
                return true;
            }
            continue;
        }
        if (p.y < min(p1.y, p2.y) || p.y > max(p1.y, p2.y)){
            continue;
        }

        double x_interseccion = p1.x + (p.y - p1.y) * (p2.x - p1.x) / (double)(p2.y - p1.y);
        if (x_interseccion == p.x){
            return true;
        }
        if (x_interseccion > p.x){
            ++cruces;
        }
    }
    return (cruces % 2) == 1;
}

int main() {
    int n;
    while(cin >> n && n != 0){
        vector<Punto> poligono(n);
        for (int i = 0; i < n; ++i) {
            cin >> poligono[i].x >> poligono[i].y;
        }
        Punto p;
        cin >> p.x >> p.y;
        if (estaDentro(poligono, p)) {
            cout << 'T';
        } else {
            cout << 'F';
        }
        cout << endl;
    }
    return 0;
}