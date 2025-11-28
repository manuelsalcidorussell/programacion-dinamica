// tarea 4- Gestor de inventario para una tienda
// Inventario con arreglos, estructuras, funciones, ordenamiento, punteros y excepciones

#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>     // manejo de excepciones
#include <limits>        // std::numeric_limits para limpiar buffer
using namespace std;

// ESTRUCTURA DEL PRODUCTO
struct Producto {
    int id;
    string nombre;
    double precio;
    int cantidad;
};

const int MAX_INVENTARIO = 100;

// LIMPIAR LINEA DE ENTRADA para evitar errores al meter letras donde van números
static void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// LISTAR PRODUCTOS
// Recorre con punteros el arreglo inventario
void listarProductos(const Producto* inventario, int total) {
    if (total == 0) { 
        cout << "Sin productos.\n"; 
        return; 
    }

    cout << "\nID    " << left << setw(22) << "Nombre"
         << right << setw(10) << "Precio" << setw(12) << "Cantidad" << "\n";
    cout << "-----------------------------------------------------\n";

    for (const Producto* p = inventario; p < inventario + total; ++p) {
        cout << left << setw(6) << p->id
             << setw(22) << p->nombre
             << right << setw(10) << fixed << setprecision(2) << p->precio
             << setw(12) << p->cantidad << "\n";
    }
    cout << "\n";
}

// AGREGAR PRODUCTO
void agregarProducto(Producto* inventario, int& total) {
    if (total >= MAX_INVENTARIO) {
        cout << "Inventario lleno.\n";
        return;
    }

    Producto nuevo;

    cout << "ID: ";
    cin >> nuevo.id; 
    limpiarEntrada();

    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Precio: ";
    cin >> nuevo.precio;

    cout << "Cantidad: ";
    cin >> nuevo.cantidad;
    limpiarEntrada();

    *(inventario + total) = nuevo;   // escritura vía puntero
    ++total;

    cout << "Producto agregado.\n";
}

// BUSCAR POR ID  —  FUNCIÓN INTERNA LANZA EXCEPCIÓN SI NO ENCUENTRA
int buscarIndicePorId(const Producto* inventario, int total, int idBuscado) {
    for (int i = 0; i < total; ++i)
        if ((inventario + i)->id == idBuscado)
            return i;

    throw runtime_error("ID no encontrado");
}

// BUSCAR POR NOMBRE — FUNCIÓN INTERNA LANZA EXCEPCIÓN SI NO ENCUENTRA
int buscarIndicePorNombre(const Producto* inventario, int total, const string& texto) {
    for (int i = 0; i < total; ++i)
        if ((inventario + i)->nombre.find(texto) != string::npos)
            return i;

    throw runtime_error("Nombre no encontrado");
}

// WRAPPER CON MANEJO DE EXCEPCIÓN: BUSCAR POR ID
void buscarPorId(const Producto* inventario, int total) {
    int idBuscado;

    cout << "ID a buscar: ";
    cin >> idBuscado;
    limpiarEntrada();

    try {
        int indice = buscarIndicePorId(inventario, total, idBuscado);
        const Producto& p = *(inventario + indice);

        cout << "Encontrado: [" << p.id << "] " << p.nombre
             << "  $" << fixed << setprecision(2) << p.precio
             << "  Cantidad: " << p.cantidad << "\n";

    } catch (const exception& error) {
        cout << error.what() << "\n";
    }
}

// WRAPPER: BUSCAR POR NOMBRE CON try/catch
void buscarPorNombre(const Producto* inventario, int total) {
    string texto;

    cout << "Nombre contiene: ";
    getline(cin, texto);

    try {
        int indice = buscarIndicePorNombre(inventario, total, texto);
        const Producto& p = *(inventario + indice);

        cout << "Encontrado: [" << p.id << "] " << p.nombre
             << "  $" << fixed << setprecision(2) << p.precio
             << "  Cantidad: " << p.cantidad << "\n";

    } catch (const exception& error) {
        cout << error.what() << "\n";
    }
}

// EDITAR CANTIDAD — modifica directamente vía puntero
void editarCantidad(Producto* inventario, int total) {
    int idBuscado;

    cout << "ID a modificar cantidad: ";
    cin >> idBuscado;
    limpiarEntrada();

    try {
        int indice = buscarIndicePorId(inventario, total, idBuscado);

        cout << "Nueva cantidad: ";
        cin >> (inventario + indice)->cantidad;   // modificación por puntero
        limpiarEntrada();

        cout << "Actualizado.\n";

    } catch (const exception& error) {
        cout << error.what() << "\n";
    }
}

// INTERCAMBIO DE DOS PRODUCTOS (pswap) usando punteros
static inline void intercambio(Producto* a, Producto* b) {
    Producto temp = *a;
    *a = *b;
    *b = temp;
}

// ORDENAMIENTO BURBUJA
// campo: 1 = precio, 2 = cantidad
// asc = true (ascendente), false (descendente)
void ordenarBurbuja(Producto* inventario, int total, int campo, bool asc = true) {
    if (total < 2) return;

    for (int pasada = 0; pasada < total - 1; ++pasada) {
        for (int i = 0; i < total - 1 - pasada; ++i) {

            Producto* A = inventario + i;
            Producto* B = inventario + i + 1;

            bool comparar = (campo == 1)
                ? (A->precio > B->precio)
                : (A->cantidad > B->cantidad);

            if (!asc) comparar = !comparar;

            if (comparar)
                intercambio(A, B);
        }
    }

    cout << "Ordenado (burbuja).\n";
}

// ORDENAMIENTO POR SELECCIÓN
void ordenarSeleccion(Producto* inventario, int total, int campo, bool asc = true) {
    if (total < 2) return;

    for (int i = 0; i < total - 1; ++i) {
        int mejor = i;

        for (int j = i + 1; j < total; ++j) {
            const Producto* A = inventario + mejor;
            const Producto* B = inventario + j;

            bool tomar = (campo == 1)
                ? (asc ? (B->precio < A->precio) : (B->precio > A->precio))
                : (asc ? (B->cantidad < A->cantidad) : (B->cantidad > A->cantidad));

            if (tomar)
                mejor = j;
        }

        if (mejor != i)
            intercambio(inventario + i, inventario + mejor);
    }

    cout << "Ordenado (seleccion).\n";
}

// MENu
void mostrarMenu() {
    cout << "\n===== MENU =====\n"
         << "1) Listar productos\n"
         << "2) Agregar producto\n"
         << "3) Buscar por ID\n"
         << "4) Buscar por nombre\n"
         << "5) Editar cantidad\n"
         << "6) Ordenar por precio (burbuja)\n"
         << "7) Ordenar por cantidad (seleccion)\n"
         << "8) Salir\n";
}

// MAIN
int main() {
    Producto inventario[MAX_INVENTARIO];
    int total = 0;

    // 10 registros iniciales para cumplir requisitos
    inventario[total++] = {1001, "lapiz ",      4.50,  120};
    inventario[total++] = {1002, "cuaderno ",  29.90,   60};
    inventario[total++] = {1003, "usb 32GB",    119.00,   25};
    inventario[total++] = {1004, "mouse optico", 89.00,   40};
    inventario[total++] = {1005, "teclado",     199.00,   35};
    inventario[total++] = {1006, "monitor 24", 2899.00,   12};
    inventario[total++] = {1007, "audifonos",   349.00,   50};
    inventario[total++] = {1008, "bocina",      499.00,   22};
    inventario[total++] = {1009, "cable hdmi",   99.00,  150};
    inventario[total++] = {1010, "silla gamer",3999.00,   10};

    bool ejecutando = true;

    while (ejecutando) {
        mostrarMenu();

        int opcion;
        cout << "OPCION : ";
        cin >> opcion;
        limpiarEntrada();

        switch (opcion) {
            case 1: listarProductos(inventario, total); break;
            case 2: agregarProducto(inventario, total); break;
            case 3: buscarPorId(inventario, total); break;
            case 4: buscarPorNombre(inventario, total); break;
            case 5: editarCantidad(inventario, total); break;

            case 6: {
                int dir;
                cout << "1=ascendente, 2=descendente: ";
                cin >> dir;
                limpiarEntrada();

                ordenarBurbuja(inventario, total, /*precio*/ 1, dir == 1);
            } break;

            case 7: {
                int dir;
                cout << "1=ascendente, 2=descendente: ";
                cin >> dir;
                limpiarEntrada();

                ordenarSeleccion(inventario, total, /*cantidad*/ 2, dir == 1);
            } break;

            case 8:
                ejecutando = false;
                cout << "Fin.\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
