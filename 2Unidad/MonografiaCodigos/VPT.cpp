#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T>
struct NodoVPT {
    T vp; 
    double mediana;
    NodoVPT *izq, *der;
    NodoVPT(T v) : vp(v), mediana(0), izq(nullptr), der(nullptr) {}
};

double dist(double a, double b) { return std::abs(a - b); }

NodoVPT<double>* construirVPT(std::vector<double> datos) {
    if (datos.empty()) return nullptr;
    double vp = datos.back();
    datos.pop_back();
    NodoVPT<double>* nodo = new NodoVPT<double>(vp);
    if (datos.empty()) return nodo;

    std::vector<double> dists;
    for (double d : datos) dists.push_back(dist(vp, d));
    std::sort(dists.begin(), dists.end());
    double mediana = dists[dists.size() / 2];
    nodo->mediana = mediana;

    std::vector<double> izq, der;
    for (double d : datos) {
        if (dist(vp, d) < mediana) izq.push_back(d);
        else der.push_back(d);
    }
    nodo->izq = construirVPT(izq);
    nodo->der = construirVPT(der);
    return nodo;
}

void mostrar(NodoVPT<double>* n, int nivel = 0) {
    if (!n) return;
    for(int i=0; i<nivel; i++) std::cout << "  ";
    std::cout << "VP: " << n->vp << " (M: " << n->mediana << ")\n";
    mostrar(n->izq, nivel + 2);
    mostrar(n->der, nivel + 2);
}

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION VPT ---\n";
    std::vector<double> d = {1.5, 9.2, 4.3, 12.0, 5.0};
    NodoVPT<double>* raiz = construirVPT(d);
    mostrar(raiz);
    return 0;
}