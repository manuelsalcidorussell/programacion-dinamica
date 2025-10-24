#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double radio, longitud, area;

    cout << "Ingrese el radio de la circunferencia: ";
    cin >> radio;

    longitud = 2 * M_PI * radio;
    area = M_PI * pow(radio, 2);

    cout << "\nRespuestas del mini examen" << endl;
    cout << "Longitud de la circunferencia: " << longitud << endl;
    cout << "Area de la circunferencia: " << area << endl;

    return 0;
}
