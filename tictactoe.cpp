#include <iostream>
#include <string>
using namespace std;

// Tablero del juego
char tablero[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Función para dibujar el tablero en consola
void dibujarTablero(const string& jugador1, const string& jugador2) {
    cout << "\n\t--- Juego del Gato ---\n\n";
    cout << jugador1 << " (X)  -  " << jugador2 << " (O)\n";
    cout << "Gana quien complete 3 en línea (fila, columna o diagonal)\n\n";

    cout << "     |     |     " << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  " << tablero[i][0] << "  |  " << tablero[i][1] << "  |  " << tablero[i][2] << endl;
        if (i < 2) cout << "_____|_____|_____" << endl << "     |     |     " << endl;
    }
    cout << endl;
}

// Función para realizar un turno
void turnoJugador(char marca) {
    int eleccion;
    cout << "Elige una posición (1-9): ";
    cin >> eleccion;

    bool movimientoValido = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == '0' + eleccion) {
                tablero[i][j] = marca;
                movimientoValido = true;
                break;
            }
        }
    }

    if (!movimientoValido)
        cout << "Posición inválida o ya ocupada. Intenta otra.\n";
}

int main() {
    string jugador1, jugador2;
    cout << "Nombre del jugador 1 (X): ";
    getline(cin, jugador1);
    cout << "Nombre del jugador 2 (O): ";
    getline(cin, jugador2);

    dibujarTablero(jugador1, jugador2);

    // Primer turno de ejemplo
    turnoJugador('X');
    dibujarTablero(jugador1, jugador2);

    turnoJugador('O');
    dibujarTablero(jugador1, jugador2);

    return 0;
}
