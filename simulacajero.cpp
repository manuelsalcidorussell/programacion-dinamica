// tarea 3 - Simulador de Cajero Automatico
// programa que simula un cajero automatico con una sola cuenta fija
// Acepta cualquier NIP entero de 4 digitos

// librerias
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

struct Account {
    double balance;     // saldo actual de la cuenta
    std::string name;   // nombre del cliente
};

// Funcion para limpiar la entrada si el usuario mete letras u otro dato incorrecto
static void clearInput() {
    cin.clear();  // limpia estado de error de cin
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // descarta basura pendiente
}

// Funcion que valida si un NIP es de 4 digitos  
static bool isValidNIP(int nip) {
    return (nip >= 1000 && nip <= 9999);  // rango que asegura 4 digitos
}

// Funcion que lee montos positivos para retirar o depositar
static double readAmount(const std::string& prompt) {
    double m;
    while (true) {                     // ciclo hasta que el usuario ponga un numero valido
        cout << prompt;
        if (cin >> m) {                // intenta leer el numero
            clearInput();              // limpia basura despues de la lectura
            if (m > 0.0) return m;    // solo acepta valores mayores a 0
            cout << "El monto debe ser mayor a 0.\n";
        } else {
            cout << "Entrada invalida.\n";  
            clearInput();              // si escribe letras limpia todo y repite
        }
    }
}

// Funcion para mostrar saldo con 2 decimales
static void showBalance(const Account& acc) {
    cout << "\nSaldo actual: $"
         << std::fixed << std::setprecision(2) << acc.balance
         << "\n\n";
}

// Funcion para retirar dinero del saldo con validacion
static bool withdraw(Account& acc, double amount) {
    if (amount > acc.balance) {        // valida fondos suficientes
        cout << "Fondos insuficientes.\n";
        return false;
    }
    acc.balance -= amount;             // resta monto al saldo
    cout << "Retiro exitoso. Nuevo saldo: $"
         << std::fixed << std::setprecision(2) << acc.balance << "\n";
    return true;
}

// Funcion para depositar dinero al saldo
static bool deposit(Account& acc, double amount) {
    acc.balance += amount;             // suma monto al saldo
    cout << "Deposito exitoso. Nuevo saldo: $"
         << std::fixed << std::setprecision(2) << acc.balance << "\n";
    return true;
}

// Funcion que imprime el menu del cajero
static void printMenu() {
    cout << "\n===== MENU =====\n"
         << "1) Consultar saldo\n"
         << "2) Retirar\n"
         << "3) Depositar\n"
         << "4) Salir\n";
}

int main() {

    // mi cuenta unica para este simulador 5 milloncitos
    Account acc = {5000000.00, "Feliz Afortunado de la UAS"};

    // ciclo de login con 3 intentos maximos
    for (int tries = 0; tries < 3; ++tries) {
        int nip;
        cout << "Ingresa tu NIP (4 digitos): ";

        if (!(cin >> nip)) {           // si escriben letras o algo raro
            cout << "NIP incorrecto.\n";
            clearInput();              // limpia la entrada
            continue;                  // va al siguiente intento
        }
        clearInput();                  // limpia salto de linea

        if (isValidNIP(nip)) {         // si es de 4 digitos, permite acceso
            cout << "\nAcceso concedido.\n";
            cout << "Cliente: " << acc.name << "\n";
            break;                     // sale del ciclo de login
        }

        cout << "NIP incorrecto.\n";
        if (tries == 2) {             // tercer intento fallido
            cout << "Demasiados intentos. Fin.\n";
            return 0;
        }
    }

    bool running = true;               // controla el ciclo del menu

    while (running) {                  // ciclo principal del cajero
        printMenu();

        int op;
        cout << "Opcion: ";
        if (!(cin >> op)) {            // si la opcion no es numero
            clearInput();
            continue;                  // vuelve a mostrar menu
        }
        clearInput();

        switch (op) {

            case 1:                    // consultar saldo
                showBalance(acc);
                break;

            case 2: {                  // retirar
                double m = readAmount("Monto a retirar: $");
                withdraw(acc, m);
            } break;

            case 3: {                  // depositar
                double m = readAmount("Monto a depositar: $");
                deposit(acc, m);
            } break;

            case 4:                    // salir
                running = false;       // cambia condicion del ciclo
                cout << "Gracias por usar el cajero.\n";
                break;

            default:                   // opcion invalida
                cout << "Opcion invalida.\n";
        }
    }

    return 0;  
}
