#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cout << "Cuantos #s desea ingresar?";
    cin >> n;

    if (n <= 0){
        cout << "Debe de ingresar al menos un #" << endl;
        return 1;
    }

    int numero;
    int menor, mayor;

    cout << "Ingresa # 1:";
    cin >> numero;
    menor = mayor = numero;

    for (int i= 2; i <= n; i++)
    {
        cout << "Ingrese el # " << i << ":";
        cin >> numero;

        if (numero < menor)
            menor = numero;
        if (numero > mayor)
            mayor = numero;
    }
     cout << "\nEl número menor es:" << menor << endl;
    cout << "El número mayor es: " << mayor << endl;

    return 0;
}
