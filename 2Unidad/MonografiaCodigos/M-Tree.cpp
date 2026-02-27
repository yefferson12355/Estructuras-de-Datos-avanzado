#include <iostream>
#include <vector>

struct Entrada {
    double pivote;
    double radio_cobertura;
};

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION M-TREE ---\n";
    Entrada e = {100.0, 50.0}; // Cubre de 50 a 150
    double consulta = 160.0;
    double r_busqueda = 5.0;

    std::cout << "Consulta: " << consulta << " | Radio Busqueda: " << r_busqueda << "\n";
    if (std::abs(consulta - e.pivote) > (e.radio_cobertura + r_busqueda))
        std::cout << "Resultado: Rama PODADA (ahorro de I/O)\n";
    else
        std::cout << "Resultado: Debe explorarse el subarbol\n";
    return 0;
}