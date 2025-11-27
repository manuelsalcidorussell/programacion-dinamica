// Tarea 3 - Simulador de Cajero Automatico con login por NIP
// Estructuras, funciones, arreglos, punteros, excepciones y validaciones

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <stdexcept>   // runtime_error para excepciones

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Account {
    int nip;           // nip de 4 digitos  
    double balance;    // saldo
    string name;       // nombre del cliente
};

// limpia el buffer de entrada cuando hay error o basura residuo
static void clearInput() {
    cin.clear();  // quita flags de error de cin  
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta hasta fin de linea
}

// lee entero y lanza excepcion si la entrada no es numerica
static int readInt(const string& prompt) {
    cout << prompt;
    int v;
    if (!(cin >> v)) {           // si falla la conversion a entero
        clearInput();            // evita bucle infinito de cin
        throw std::runtime_error("Entrada invalida (se esperaba entero).");
    }
    clearInput();                // limpia el \n pendiente
    return v;
}

// lee monto positivo y lanza si es invalido
static double readAmount(const string& prompt) {
    cout << prompt;
    double m;
    if (!(cin >> m)) {           // falla si meten letras
        clearInput();
        throw std::runtime_error("Entrada invalida (se esperaba numero).");
    }
    clearInput();
    if (m <= 0.0) throw std::runtime_error("El monto debe ser mayor a 0.");
    return m;
}

// valida nip de 4 digitos
static bool isValidNIP(int nip) { return nip >= 1000 && nip <= 9999; }

// busca cuenta por NIP en arreglo usando punteros; lanza si no existe
static int findIndexByNip(const Account* arr, int n, int nip) {
    for (int i = 0; i < n; ++i) {
        const Account* p = arr + i;  // p apunta al elemento i (punteros)
        if (p->nip == nip) return i;
    }
    throw std::runtime_error("Cuenta no encontrada.");
}

// imprime todas las cuentas ANTES del login  nip, nombre y saldo 
static void showAllAccounts(const Account* acc, int n) {
    cout << "\n===== CUENTAS DISPONIBLES =====\n";
    cout << "NIP    Nombre                 Saldo\n";
    cout << "-------------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        const Account* p = acc + i;  // acceso via puntero
        cout << p->nip << "   "
             << p->name << "      $"
             << std::fixed << std::setprecision(2) << p->balance << "\n"; // formato 2 decimales
    }
    cout << "-------------------------------------------\n";
}

// operaciones 
static void showBalance(const Account& acc) {
    cout << "\nSaldo de " << acc.name << ": $"
         << std::fixed << std::setprecision(2) << acc.balance << "\n\n";
}

static void deposit(Account& acc, double amount) {
    acc.balance += amount;  //  estado
    cout << "Deposito ok. Nuevo saldo: $" << std::fixed << std::setprecision(2) << acc.balance << "\n";
}

// retiro con excepcion si no hay fondos
static void withdraw(Account& acc, double amount) {
    if (amount > acc.balance) throw std::runtime_error("Fondos insuficientes.");
    acc.balance -= amount;
    cout << "Retiro ok. Nuevo saldo: $" << std::fixed << std::setprecision(2) << acc.balance << "\n";
}

// transferencia usando punteros a las dos cuentas
static void transfer(Account* from, Account* to, double amount) {
    if (from == to) throw std::runtime_error("No puedes transferir a la misma cuenta.");
    if (amount <= 0.0) throw std::runtime_error("El monto debe ser mayor a 0.");
    if (amount > from->balance) throw std::runtime_error("Fondos insuficientes para transferir.");
    from->balance -= amount;  // escribe via puntero
    to->balance   += amount;  // escribe via puntero
    cout << "Transferencia ok. Tu nuevo saldo: $" << std::fixed << std::setprecision(2) << from->balance << "\n";
}

// menu principal
static void printMenu() {
    cout << "\n===== MENU =====\n"
         << "1) Consultar saldo\n"
         << "2) Depositar\n"
         << "3) Retirar\n"
         << "4) Transferir\n"
         << "5) Salir\n";
}

// login SOLO por NIP 3 intentos   Muestra cliente y retorna indice
static int loginByNip(Account* accounts, int n) {
    cout << "\n=== INICIO DE SESION ===\n";
    for (int tries = 0; tries < 3; ++tries) {
        int nip = readInt("NIP (4 digitos): ");
        if (!isValidNIP(nip)) {       // validacion basica de formato
            cout << "NIP incorrecto.\n";
            continue;                 // salto al siguiente intento
        }
        int idx = findIndexByNip(accounts, n, nip); // puede lanzar excepcion
        cout << "\nAcceso concedido.\nCliente: " << accounts[idx].name << "\n";
        return idx;
    }
    throw std::runtime_error("Demasiados intentos fallidos.");
}

int main() {

    // arreglo   con minimo 3 cuentas 
    Account accounts[3] = {
        {1234,  8500.00, "Ana Perez"},
        {4321, 12000.50, "Luis Garcia"},
        {1111,   250.75, "Maria Lopez"}
    };
    const int N = 3;

    // imprime las cuentas para que el usuario vea que NIP usar
    showAllAccounts(accounts, N);

    try {
        // login por NIP      retorna indice si acceso concedido
        int idx = loginByNip(accounts, N);
        Account* me = &accounts[idx];     // puntero a mi cuenta 

        bool running = true;              // controla el ciclo principal
        while (running) {
            printMenu();
            try {
                int op = readInt("Opcion: ");  // lectura con excepcion

                switch (op) {                   // seleccion por menu
                    case 1:
                        showBalance(*me);       // desreferencia de puntero
                        break;

                    case 2: {
                        double m = readAmount("Monto a depositar: $");
                        deposit(*me, m);
                    } break;

                    case 3: {
                        double m = readAmount("Monto a retirar: $");
                        withdraw(*me, m);      // puede lanzar excepcion
                    } break;

                    case 4: {
                        int destNip = readInt("NIP de cuenta destino: ");
                        int j = findIndexByNip(accounts, N, destNip); // excepcion si no existe
                        double m = readAmount("Monto a transferir: $");
                        transfer(me, &accounts[j], m); // pasa punteros
                    } break;

                    case 5:
                        running = false;       // fin del while
                        cout << "Gracias por usar el cajero.\n";
                        break;

                    default:
                        cout << "Opcion invalida.\n";
                }
            } catch (const std::exception& e) { // captura errores de cada operacion
                cout << "Error: " << e.what() << "\n";
            }
        }
    } catch (const std::exception& e) {        // errores de login
        cout << "Fin: " << e.what() << "\n";
    }

    return 0;
}
