#include <iostream>
#include <string>
using namespace std;

struct Alumno {
    string nombre;
    int edad;
    float promedio;
};

int main() {
    const int TAM = 3amy;
    Alumno grupo[TAM];  // Arreglo de una estructura definida por el usuario

    cout << "=== Captura los datos del alumno ===" << endl;

    for (int i = 0; i < TAM; i++) {
        cout << "\nAlumno " << i + 1 << ":" << endl;
        cout << "Nombre: ";
        getline(cin >> ws, grupo[i].nombre);
        cout << "Edad: ";
        cin >> grupo[i].edad;
        cout << "Promedio: ";
        cin >> grupo[i].promedio;
    }

    cout << "\n=== Listado de alumnos ===" << endl;
    for (int i = 0; i < TAM; i++) {
        cout << "\nAlumno " << i + 1 << "." << endl;
        cout << "Nombre: " << grupo[i].nombre << endl;
        cout << "Edad: " << grupo[i].edad << endl;
        cout << "Promedio: " << grupo[i].promedio << endl;
    }

    // 🔹 Pausa al final del programa
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();

    return 0;
}
