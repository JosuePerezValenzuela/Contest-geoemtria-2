#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

vector<Point> convexHull(vector<Point> puntos) {
    int n = puntos.size();
    if (n < 3){
        return puntos;
    }

    sort(puntos.begin(), puntos.end());
    vector<Point> hull;
    for (int fase = 0; fase < 2; ++fase) {
        auto inicio = hull.size();
        for (const auto& p : puntos){
            while (hull.size() >= inicio + 2 && 
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

double areaPoly(const vector<Point>& puntos) {
    int n = puntos.size();
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += puntos[i].x * puntos[j].y - puntos[j].x * puntos[i].y;
    }
    return fabs(area) / 2.0;
}

Point calculateCentroid(const vector<Point>& puntos) {
    int n = puntos.size();
    double cx = 0.0, cy = 0.0;
    double area = areaPoly(puntos);
    double factor = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        factor = puntos[i].x * puntos[j].y - puntos[j].x * puntos[i].y;
        cx += (puntos[i].x + puntos[j].x) * factor;
        cy += (puntos[i].y + puntos[j].y) * factor;
    }
    factor = 1 / (6.0 * area);
    cx *= factor;
    cy *= factor;
    return {cx, cy};
}

Point findCenterOfMass(vector<Point> puntos) {
    vector<Point> hull = convexHull(puntos);
    return calculateCentroid(hull);
}

int main() {
    cout << fixed << setprecision(3);
    int n;
    while(cin >> n && n >= 3){
        vector<Point> puntos(n);
        for (int i = 0; i < n; i++) {
             cin >> puntos[i].x >> puntos[i].y;
        }
        Point centroid = findCenterOfMass(puntos);
         cout << centroid.x << " " << centroid.y <<  endl;
    }
    return 0;
}