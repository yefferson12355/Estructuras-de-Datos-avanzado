#include <iostream>
#include <map>
#include <vector>
#include <cmath>

template <typename T>
class NodoBKT {
public:
    T valor;
    std::map<int, NodoBKT*> hijos; 

    NodoBKT(T v) : valor(v) {}
};

template <typename T>
class BKTree {
private:
    NodoBKT<T>* raiz;
    int calcularDistancia(int a, int b) { return std::abs(a - b); }

public:
    BKTree() : raiz(nullptr) {}

    void insertar(T nuevo_valor) {
        if (!raiz) {
            raiz = new NodoBKT<T>(nuevo_valor);
            return;
        }
        NodoBKT<T>* actual = raiz;
        while (true) {
            int dist = calcularDistancia(actual->valor, nuevo_valor);
            if (dist == 0) return; 
            if (actual->hijos.count(dist)) {
                actual = actual->hijos[dist];
            } else {
                actual->hijos[dist] = new NodoBKT<T>(nuevo_valor);
                break;
            }
        }
    }

    void imprimir(NodoBKT<T>* nodo, int nivel = 0) {
        if (!nodo) return;
        for (int i = 0; i < nivel; i++) std::cout << "  ";
        std::cout << "|-- Valor: " << nodo->valor << std::endl;
        for (auto const& [dist, hijo] : nodo->hijos) {
            for (int i = 0; i < nivel + 1; i++) std::cout << "  ";
            std::cout << "[Distancia: " << dist << "]" << std::endl;
            imprimir(hijo, nivel + 2);
        }
    }
    NodoBKT<T>* getRaiz() { return raiz; }
};

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION BKT ---\n";
    BKTree<int> arbol;
    std::vector<int> valores = {10, 12, 15, 8, 5};
    for(int v : valores) arbol.insertar(v);
    arbol.imprimir(arbol.getRaiz());
    return 0;
}