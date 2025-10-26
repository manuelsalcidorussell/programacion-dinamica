#include <iostream>
#include <string>
using namespace std;

// Tablero del juego
char tablero[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Función para dibujar el tablero en consola (con nombres)
void dibujarTablero(const string& jugador1, const string& jugador2) {
    cout << "\n\t--- Juego del Gato ---\n\n";
    cout << jugador1 << " (X)  -  " << jugador2 << " (O)\n";
    cout << "Gana quien complete 3 en linea (fila, columna o diagonal)\n\n";

    cout << "     |     |     " << endl;
    cout << "  " << tablero[0][0] << "  |  " << tablero[0][1] << "  |  " << tablero[0][2] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << tablero[1][0] << "  |  " << tablero[1][1] << "  |  " << tablero[1][2] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << tablero[2][0] << "  |  " << tablero[2][1] << "  |  " << tablero[2][2] << endl;
    cout << "     |     |     " << endl << endl;
}

int main() {
    string jugador1, jugador2;

    cout << "Nombre del jugador 1 (X): ";
    getline(cin >> ws, jugador1);  // ws consume espacios/saltos previos

    cout << "Nombre del jugador 2 (O): ";
    getline(cin >> ws, jugador2);

    dibujarTablero(jugador1, jugador2); // Muestra el tablero con nombres y regla
    return 0;
}
