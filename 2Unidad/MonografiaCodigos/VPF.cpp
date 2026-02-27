#include <iostream>
#include <vector>

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION VPF ---\n";
    double vp = 50.0;
    double r_int = 10.0, r_ext = 15.0; // Margen de exclusion
    std::vector<double> datos = {55.0, 62.0, 42.0, 90.0};

    for(double d : datos) {
        double distancia = std::abs(d - vp);
        if(distancia < r_int) std::cout << d << ": Rama INTERNA\n";
        else if(distancia > r_ext) std::cout << d << ": Rama EXTERNA\n";
        else std::cout << d << ": !!! EXCLUIDO AL BOSQUE !!!\n";
    }
    return 0;
}