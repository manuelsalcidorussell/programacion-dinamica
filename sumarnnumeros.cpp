#include <iostream>

//funciones

int main()
{
    int n;
    int suma = 0;
    std::cout << "Ingrese un número entero positivo:";
    std::cin >> n;

    if (n < 0)
    {
        std::cout << "El número debe de ser positivo" << std::endl;
        return 1;
    }

    for (int i = 1; i <= n; i++)
    {
        suma += i;
    }

    std::cout << "La sumatoria de los " << n << " primeros números naturales es:"
              << suma << std::endl;

    return 0;
}
