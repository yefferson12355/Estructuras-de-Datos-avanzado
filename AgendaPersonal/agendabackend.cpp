#include "agendabackend.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

AgendaBackend::AgendaBackend() {}

AgendaBackend::~AgendaBackend() {}

void AgendaBackend::registrarContacto(Contacto c) {
    // Inserta ordenado alfabéticamente por apellido paterno
    misContactos.push_ordered(c);
}

int AgendaBackend::generarNuevoId() {
    // El nuevo ID es el mayor existente + 1
    return misContactos.obtenerMayorId() + 1;
}

void AgendaBackend::verAgenda() {
    misContactos.mostrar();
}

void AgendaBackend::borrarPrimero() { misContactos.pop_front(); }
void AgendaBackend::borrarUltimo() { misContactos.pop_end(); }

// --- NUEVA FUNCIÓN: BUSCAR POR ID ---
void AgendaBackend::buscarContacto(int id) {
    // Llamamos a la función que creamos en lista.cpp
    Contacto* encontrado = misContactos.buscarPorId(id);

    if (encontrado != nullptr) {
        cout << "\n===============================" << endl;
        cout << "      CONTACTO ENCONTRADO      " << endl;
        cout << "===============================" << endl;
        cout << "ID:        " << encontrado->id << endl;
        cout << "Nombre:    " << encontrado->nombres << " " 
                                << encontrado->paterno << " " 
                                << encontrado->materno << endl;
        cout << "Telefono:  " << encontrado->telefono << endl;
        cout << "Correo:    " << encontrado->correo << endl;
        cout << "Direccion: " << encontrado->direccion << endl;
        cout << "Edad:      " << encontrado->edad << endl;
        cout << "Nacimiento:" << encontrado->FechaNacimiento << endl;
        cout << "===============================\n" << endl;
    } else {
        cout << "\n[!] No se encontro ningun contacto con el ID: " << id << endl;
    }
}

void AgendaBackend::guardarEnTexto() {
    ofstream archivo(nombreArchivo); // Modo escritura (sobrescribe)
    
    if (archivo.is_open()) {
        auto actual = misContactos.getInicio();
        while (actual != nullptr) {
            // Guardamos TODOS los datos separados por '|'
            archivo << actual->dato.id << "|"
                    << actual->dato.nombres << "|"
                    << actual->dato.paterno << "|"
                    << actual->dato.materno << "|"
                    << actual->dato.telefono << "|"
                    << actual->dato.correo << "|"      // Nuevo campo
                    << actual->dato.direccion << "|"   // Nuevo campo
                    << actual->dato.edad << "|"        // Nuevo campo
                    << actual->dato.FechaNacimiento << "\n";
            actual = actual->siguiente;
        }
        archivo.close();
        cout << "[Sistema] Agenda guardada correctamente (Datos completos)." << endl;
    } else {
        cout << "[Error] No se pudo crear/abrir el archivo para guardar." << endl;
    }
}

void AgendaBackend::cargarDesdeTexto() {
    ifstream archivo(nombreArchivo); // Modo lectura
    
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string segmento;
            Contacto c;
            
            // Leemos en el MISMO ORDEN en que guardamos
            try {
                if(getline(ss, segmento, '|')) c.id = stoi(segmento);
                if(getline(ss, segmento, '|')) c.nombres = segmento;
                if(getline(ss, segmento, '|')) c.paterno = segmento;
                if(getline(ss, segmento, '|')) c.materno = segmento;
                if(getline(ss, segmento, '|')) c.telefono = segmento;
                
                // Nuevos campos
                if(getline(ss, segmento, '|')) c.correo = segmento;
                if(getline(ss, segmento, '|')) c.direccion = segmento;
                
                if(getline(ss, segmento, '|')) {
                    // Verificamos que no esté vacío para evitar error al convertir a int
                    if (!segmento.empty()) c.edad = stoi(segmento);
                    else c.edad = 0;
                }
                
                if(getline(ss, segmento, '|')) c.FechaNacimiento = segmento;

                // Lo mandamos a la lista
                misContactos.push_ordered(c);

            } catch (...) {
                cout << "[Alerta] Hubo un error leyendo una linea del archivo." << endl;
            }
        }
        archivo.close();
        cout << "[Sistema] Datos cargados exitosamente." << endl;
    } else {
        cout << "[Info] No se encontro archivo previo. Se creara uno nuevo al guardar." << endl;
    }
}