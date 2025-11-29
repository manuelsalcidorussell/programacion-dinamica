//tarea 5- Calculadora científica
//Diseñar una calculadora que realice operaciones básicas y avanzadas (factorial, potencia, raíz).
#include <iostream>
#include <cmath>           
#include <stdexcept>       
#include <limits>          

using std::cout;
using std::cin;
using std::endl;

// Limpia la entrada cuando se mete algo incorrecto
void limpiarEntrada() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Lee un numero generico
template <typename T>
T leer(const char* mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) return valor;
        cout << "Entrada invalida intenta de nuevo" << endl;
        limpiarEntrada();
    }
}

// Funciones basicas  
int suma(int a, int b = 0) { return a + b; }
double suma(double a, double b = 0.0) { return a + b; }

int resta(int a, int b = 0) { return a - b; }
double resta(double a, double b = 0.0) { return a - b; }

int multiplicar(int a, int b = 1) { return a * b; }
double multiplicar(double a, double b = 1.0) { return a * b; }

// División con excepcion si b es cero
int dividir(int a, int b = 1) {
    if (b == 0) throw std::invalid_argument("No se puede dividir entre cero");
    return a / b;
}

double dividir(double a, double b = 1.0) {
    if (b == 0.0) throw std::invalid_argument("No se puede dividir entre cero");
    return a / b;
}

// Factorial recursivo
unsigned long long factorial(int n) {
    if (n < 0) throw std::invalid_argument("No existe factorial de negativo");
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

// Potencia con parametro por omision exp = 2
double potencia(double base, int exp = 2) {
    return std::pow(base, exp);
}

// Raiz cuadrada con exepcion si el numero es negativo
double raiz(double x) {
    if (x < 0) throw std::domain_error("No existe raiz cuadrada real de negativo");
    return std::sqrt(x);
}

// menu
void mostrarMenu() {
    cout << "\nCalculadora:" << endl;
    cout << "1 Suma" << endl;
    cout << "2 Resta" << endl;
    cout << "3 Multiplicacion" << endl;
    cout << "4 Division" << endl;
    cout << "5 Factorial" << endl;
    cout << "6 Potencia" << endl;
    cout << "7 Raiz cuadrada" << endl;
    cout << "0 Salir" << endl;
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        opcion = leer<int>("Opcion : ");

        try {
            switch (opcion) {

                case 1: {
                    cout << "Suma" << endl;
                    double a = leer<double>("valor de a: ");
                    double b = leer<double>("valor de b: ");
                    cout << "Resultado : " << suma(a, b) << endl;
                    break;
                }

                case 2: {
                    cout << "Resta" << endl;
                    double a = leer<double>("valor de a: ");
                    double b = leer<double>("valor de b: ");
                    cout << "Resultado: " << resta(a, b) << endl;
                    break;
                }

                case 3: {
                    cout << "Multiplicacion" << endl;
                    double a = leer<double>("valor de a: ");
                    double b = leer<double>("valor de b: ");
                    cout << "Resultado: " << multiplicar(a, b) << endl;
                    break;
                }

                case 4: {
                    cout << "Division" << endl;
                    double a = leer<double>("valor de a: ");
                    double b = leer<double>("valor de b: ");
                    cout << "Resultado: " << dividir(a, b) << endl;
                    break;
                }

                case 5: {
                    cout << "Factorial" << endl;
                    int n = leer<int>("Numero entero: ");
                    cout << "Resultado: " << factorial(n) << endl;
                    break;
                }

                case 6: {
                    cout << "Potencia" << endl;
                    double base = leer<double>("Base: ");
                    int exp = leer<int>("Exponente: ");
                    cout << "Resultado: " << potencia(base, exp) << endl;
                    break;
                }

                case 7: {
                    cout << "Raiz cuadrada" << endl;
                    double x = leer<double>("Numero: ");
                    cout << "Resultado: " << raiz(x) << endl;
                    break;
                }

                case 0:
                    cout << "Saliendo" << endl;
                    break;

                default:
                    cout << "Opcion no valida" << endl;
            }
        }
        catch (const std::exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 0);

    return 0;
}