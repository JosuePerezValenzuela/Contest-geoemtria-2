#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

double areaPoligono(const vector<Point>& puntos) {
    int n = puntos.size();
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += puntos[i].x * puntos[j].y - puntos[j].x * puntos[i].y;
    }
    return fabs(area) / 2.0;
}

vector<Point> convexHull(vector<Point> puntos) {
    int n = puntos.size();
    if (n < 3){
        return puntos;
    }

    sort(puntos.begin(), puntos.end());
    vector<Point> hull;

    for (int fase = 0; fase < 2; ++fase) {
        auto ini = hull.size();
        for (const auto& p : puntos) {
            while (hull.size() >= ini + 2 && 
                   (hull[hull.size() - 2].x * (hull.back().y - p.y) + 
                    hull.back().x * (p.y - hull[hull.size() - 2].y) + 
                    p.x * (hull[hull.size() - 2].y - hull.back().y)) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(puntos.begin(), puntos.end());
    }
    return hull;
}

int main() {
    cout << fixed << setprecision(2);
    int tileNumber = 1;
    int n;
    while(cin >> n && n != 0){
        vector<Point> puntos(n);
        for (int i = 0; i < n; ++i) {
            cin >> puntos[i].x >> puntos[i].y;
        }
        double area = areaPoligono(puntos);
        vector<Point> hull = convexHull(puntos);
        double areaContenedor = areaPoligono(hull);
        double espacioPerdido = ((areaContenedor - area) / areaContenedor) * 100.0;
        cout << "Tile #" << tileNumber++ << endl;
        cout << "Wasted Space = " << espacioPerdido << " %" << endl << endl;
    }
    return 0;
}
