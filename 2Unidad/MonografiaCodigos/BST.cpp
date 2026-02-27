#include <iostream>
#include <vector>
#include <cmath>

struct NodoBST {
    double p_izq, p_der;
    std::vector<double> grupo_izq, grupo_der;
    NodoBST(double p1, double p2) : p_izq(p1), p_der(p2) {}
};

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION BST ---\n";
    std::vector<double> puntos = {2.0, 15.0, 4.0, 12.0, 7.0};
    NodoBST nodo(puntos[0], puntos[1]);

    for(size_t i = 2; i < puntos.size(); i++) {
        if(std::abs(puntos[i] - nodo.p_izq) < std::abs(puntos[i] - nodo.p_der))
            nodo.grupo_izq.push_back(puntos[i]);
        else
            nodo.grupo_der.push_back(puntos[i]);
    }

    std::cout << "Pivote Izq (" << nodo.p_izq << ") tiene: ";
    for(double x : nodo.grupo_izq) std::cout << x << " ";
    std::cout << "\nPivote Der (" << nodo.p_der << ") tiene: ";
    for(double x : nodo.grupo_der) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}