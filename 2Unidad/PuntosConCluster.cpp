#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <limits>
#include <algorithm>

using namespace std;

struct Punto {
    double x, y;
    int cluster = -1;
};

struct Centroide {
    double x, y;
};

class KMeans {
private:
    vector<Punto> puntos;
    vector<Centroide> centroides;
    int K;

    double distancia(const Punto& p, const Centroide& c) {
        return hypot(p.x - c.x, p.y - c.y);
    }

    void inicializarCentroides() {
        centroides.clear();
        vector<int> indices(puntos.size());
        for (size_t i = 0; i < puntos.size(); ++i)
            indices[i] = i;

        shuffle(indices.begin(), indices.end(), mt19937(random_device{}()));

        for (int i = 0; i < K; ++i) {
            centroides.push_back({puntos[indices[i]].x, puntos[indices[i]].y});
        }
    }

public:
    KMeans(int k = 2) : K(k) {}

    void agregarPunto(double x, double y) {
        puntos.push_back({x, y});
        cout << ">> Punto agregado correctamente.\n";
    }

    void cambiarK(int nuevoK) {
        if (nuevoK > 0 && nuevoK <= (int)puntos.size()) {
            K = nuevoK;
            cout << ">> K actualizado a " << K << endl;
        } else {
            cout << ">> K inválido.\n";
        }
    }

    void ejecutar() {
        if (puntos.size() < (size_t)K) {
            cout << "No hay suficientes puntos para ejecutar K-Means.\n";
            return;
        }

        inicializarCentroides();

        bool convergio = false;
        int iteraciones = 0;

        while (!convergio && iteraciones < 100) {
            convergio = true;

            // ASIGNACIÓN
            for (auto& p : puntos) {
                double minDist = numeric_limits<double>::max();
                int mejorCluster = 0;

                for (int i = 0; i < K; ++i) {
                    double d = distancia(p, centroides[i]);
                    if (d < minDist) {
                        minDist = d;
                        mejorCluster = i;
                    }
                }

                if (p.cluster != mejorCluster) {
                    p.cluster = mejorCluster;
                    convergio = false;
                }
            }

            // ACTUALIZACIÓN
            vector<double> sumX(K, 0), sumY(K, 0);
            vector<int> conteo(K, 0);

            for (const auto& p : puntos) {
                sumX[p.cluster] += p.x;
                sumY[p.cluster] += p.y;
                conteo[p.cluster]++;
            }

            for (int i = 0; i < K; ++i) {
                if (conteo[i] > 0) {
                    centroides[i].x = sumX[i] / conteo[i];
                    centroides[i].y = sumY[i] / conteo[i];
                }
            }

            iteraciones++;
        }

        cout << ">> K-Means convergió en " << iteraciones << " iteraciones.\n";
    }

    void mostrarEstado() {
        cout << "\nPUNTOS:\n";
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < puntos.size(); ++i) {
            cout << "P" << i 
                 << " (" << puntos[i].x << ", " << puntos[i].y << ")"
                 << " -> Cluster " << puntos[i].cluster << endl;
        }

        cout << "\nCENTROIDES:\n";
        for (int i = 0; i < K; ++i) {
            cout << "Cluster " << i 
                 << " Centro: (" << centroides[i].x 
                 << ", " << centroides[i].y << ")\n";
        }
    }
};

void pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    KMeans sistema(2);
    int opcion;

    do {
        cout << "\n==== K-MEANS PROFESIONAL ====\n";
        cout << "1. Agregar punto\n";
        cout << "2. Ejecutar K-Means\n";
        cout << "3. Cambiar K\n";
        cout << "4. Mostrar estado\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double x, y;
                cout << "X: ";
                cin >> x;
                cout << "Y: ";
                cin >> y;
                sistema.agregarPunto(x, y);
                break;
            }
            case 2:
                sistema.ejecutar();
                pausa();
                break;
            case 3: {
                int k;
                cout << "Nuevo K: ";
                cin >> k;
                sistema.cambiarK(k);
                break;
            }
            case 4:
                sistema.mostrarEstado();
                pausa();
                break;
        }

    } while (opcion != 0);

    return 0;
}
