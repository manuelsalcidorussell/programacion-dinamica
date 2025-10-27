#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// ------------------------------ VARIABLES GLOBALES ------------------------------

char tablero[3][3] = { {'1', '2', '3'},
                       {'4', '5', '6'},
                       {'7', '8', '9'} };

string nombreJugador1, nombreJugador2;
bool modoContraCPU = false;

// ------------------------------ FUNCIONES ------------------------------

// Dibuja el tablero actual en pantalla
void mostrarTablero() {
    cout << "\n\t--- JUEGO DEL GATO ---\n\n";
    cout << nombreJugador1 << " (X)  -  " << nombreJugador2 << " (O)\n";
    cout << "Gana quien complete 3 en línea (fila, columna o diagonal)\n\n";

    for (int fila = 0; fila < 3; fila++) {
        cout << "     |     |     \n";
        cout << "  " << tablero[fila][0] << "  |  " << tablero[fila][1] << "  |  " << tablero[fila][2] << "\n";
        if (fila < 2)
            cout << "_____|_____|_____\n";
    }
    cout << endl;
}

// Reinicia el tablero con los números originales
void reiniciarTablero() {
    char numero = '1';
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            tablero[fila][col] = numero++;
        }
    }
}

// Revisa si un jugador ganó
bool hayGanador(char simbolo) {
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == simbolo && tablero[i][1] == simbolo && tablero[i][2] == simbolo) return true;
        if (tablero[0][i] == simbolo && tablero[1][i] == simbolo && tablero[2][i] == simbolo) return true;
    }
    if (tablero[0][0] == simbolo && tablero[1][1] == simbolo && tablero[2][2] == simbolo) return true;
    if (tablero[0][2] == simbolo && tablero[1][1] == simbolo && tablero[2][0] == simbolo) return true;
    return false;
}

// Revisa si el tablero está lleno (empate)
bool tableroLleno() {
    for (int fila = 0; fila < 3; fila++)
        for (int col = 0; col < 3; col++)
            if (tablero[fila][col] != 'X' && tablero[fila][col] != 'O')
                return false;
    return true;
}

// Coloca una jugada en el tablero
bool colocarJugada(int posicion, char simbolo) {
    if (posicion < 1 || posicion > 9)
        return false;

    int fila = (posicion - 1) / 3;
    int col = (posicion - 1) % 3;

    if (tablero[fila][col] == 'X' || tablero[fila][col] == 'O')
        return false;

    tablero[fila][col] = simbolo;
    return true;
}

// Jugada de la CPU (elige una posición aleatoria libre)
void jugadaCPU() {
    vector<int> posicionesLibres;
    for (int i = 1; i <= 9; i++) {
        int fila = (i - 1) / 3;
        int col = (i - 1) % 3;
        if (tablero[fila][col] != 'X' && tablero[fila][col] != 'O')
            posicionesLibres.push_back(i);
    }

    if (!posicionesLibres.empty()) {
        srand(time(0));
        int eleccion = posicionesLibres[rand() % posicionesLibres.size()];
        colocarJugada(eleccion, 'O');
        cout << "\nLa CPU jugó en la posición " << eleccion << ".\n";
    }
}

// ------------------------------ FLUJO PRINCIPAL ------------------------------

void jugarPartida() {
    reiniciarTablero();
    mostrarTablero();

    char simboloActual = 'X';

    while (true) {
        int posicionElegida;

        if (simboloActual == 'X' || !modoContraCPU) {
            cout << "\nTurno de " << (simboloActual == 'X' ? nombreJugador1 : nombreJugador2)
                 << " (" << simboloActual << "). Elige una posición (1-9): ";

            while (!(cin >> posicionElegida)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Ingresa un número entre 1 y 9: ";
            }

            if (!colocarJugada(posicionElegida, simboloActual)) {
                cout << "Esa posición no es válida o ya está ocupada. Intenta otra.\n";
                continue;
            }
        } else {
            jugadaCPU();
        }

        mostrarTablero();

        if (hayGanador(simboloActual)) {
            cout << "\n¡Gana " << (simboloActual == 'X' ? nombreJugador1 : nombreJugador2) << "!\n";
            break;
        }

        if (tableroLleno()) {
            cout << "\nEmpate. No quedan posiciones disponibles.\n";
            break;
        }

        simboloActual = (simboloActual == 'X') ? 'O' : 'X';
    }
}

// ------------------------------ MENÚ ------------------------------

int main() {
    int opcionMenu = 0;

    while (true) {
        cout << "\n===== MENÚ PRINCIPAL =====\n";
        cout << "1) Jugar 1 vs 1\n";
        cout << "2) Jugar contra CPU\n";
        cout << "3) Salir\n";
        cout << "Selecciona una opción: ";

        cin >> opcionMenu;

        if (opcionMenu == 3) {
            cout << "Gracias por jugar. ¡Hasta pronto!\n";
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer

        cout << "\nNombre del jugador 1 (X): ";
        getline(cin, nombreJugador1);

        if (opcionMenu == 1) {
            cout << "Nombre del jugador 2 (O): ";
            getline(cin, nombreJugador2);
            modoContraCPU = false;
        } else {
            nombreJugador2 = "CPU";
            modoContraCPU = true;
        }

        jugarPartida();
    }

    return 0;
}
