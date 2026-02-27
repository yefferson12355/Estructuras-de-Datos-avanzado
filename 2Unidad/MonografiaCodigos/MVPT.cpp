#include <iostream>
#include <vector>

int main() {
    std::cout << "--- UNA PUNO: DEMOSTRACION MVPT ---\n";
    double vp1 = 10, vp2 = 100;
    double test = 15;

    std::cout << "Punto " << test << " analizado con VP1=" << vp1 << " y VP2=" << vp2 << std::endl;
    std::cout << "Region: " << (std::abs(test-vp1) < 20 ? "Cerca VP1" : "Lejos VP1");
    std::cout << " y " << (std::abs(test-vp2) < 20 ? "Cerca VP2" : "Lejos VP2") << std::endl;
    return 0;
}