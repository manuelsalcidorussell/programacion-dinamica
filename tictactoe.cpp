#include <iostream>
using namespace std;

// Tablero del juego
char tablero[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Función para dibujar el tablero en consola
void dibujarTablero() {
    cout << "\n\t--- Juego del Gato ---\n\n";
    cout << "Jugador 1 (X)  -  Jugador 2 (O)" << endl << endl;
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
    dibujarTablero(); // Llama a la función para mostrar el tablero
    return 0;
}
