// Practica 1 - Manejo de cadenas  

#include <iostream>  // incluye iostream para imprimir y leer desde consola
#include <string>    // incluye string para usar la clase std::string que sirve para trabajar con cadenas de texto.
#include <cctype>    // incluye cctype para funciones de caracter como toupper  

using namespace std; // evita escribir std:: en cada uso de tipos y funciones de la STL

// funcion que reemplaza todas las ocurrencias de un texto "tal" por "cual" en s, sin usar arreglos
static string reemplazar_todo(string s, const string& de, const string& a) {
    size_t pos = s.find(de);                  // busca la primera aparicion del patron a reemplazar
    while (pos != string::npos) {             // ciclo: itera mientras encuentre mas ocurrencias en la cadena
        s.replace(pos, de.size(), a);         // realiza el reemplazo en la posicion encontrada
        pos = s.find(de, pos + a.size());     // continua la busqueda desde el final del ultimo reemplazo
    }
    return s;                                 // regresa la cadena modificada
}

// funcion que convierte a mayusculas incluyendo acentos, sin usar arreglos
static string a_mayusculas_es(string s) {
    s = reemplazar_todo(s, "á", "Á");
    s = reemplazar_todo(s, "é", "É");
    s = reemplazar_todo(s, "í", "Í");
    s = reemplazar_todo(s, "ó", "Ó");
    s = reemplazar_todo(s, "ú", "Ú");
    s = reemplazar_todo(s, "ñ", "Ñ");
    for (size_t i = 0; i < s.size(); ++i) {                   // ciclo: recorre ascii basico y convierte a mayuscula
        unsigned char c = static_cast<unsigned char>(s[i]);   // asegura tratamiento correcto de byte sin signo
        if (c < 128) s[i] = static_cast<char>(toupper(c));    // usa toupper para letras sin acento (ascii simple)
    }
    return s;  // devuelve el texto en mayusculas
}

// funcion que valida que una cadena tenga solo digitos y una longitud exacta L
static bool es_solo_digitos_con_longitud(const string& s, int L) {
    if ((int)s.size() != L) return false;                               // verifica longitud exacta (00 o 0000)
    for (size_t i = 0; i < s.size(); ++i) {                             // ciclo: revisa caracter por caracter
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;   // valida que cada caracter sea un digito
    }
    return true;                                                        // si pasa ambas condiciones, es valida
}

// convierte un numero de 0..99 a letras en espanol sin usar arreglos
static string dos_digitos_a_letra(int n) {
    if (n < 0 || n > 99) return to_string(n);
    if (n == 0) return "cero";
    if (n == 1) return "uno";
    if (n == 2) return "dos";
    if (n == 3) return "tres";
    if (n == 4) return "cuatro";
    if (n == 5) return "cinco";
    if (n == 6) return "seis";
    if (n == 7) return "siete";
    if (n == 8) return "ocho";
    if (n == 9) return "nueve";
    if (n == 10) return "diez";
    if (n == 11) return "once";
    if (n == 12) return "doce";
    if (n == 13) return "trece";
    if (n == 14) return "catorce";
    if (n == 15) return "quince";
    if (n == 16) return "dieciséis";
    if (n == 17) return "diecisiete";
    if (n == 18) return "dieciocho";
    if (n == 19) return "diecinueve";
    if (n == 20) return "veinte";
    if (n == 21) return "veintiuno";
    if (n == 22) return "veintidós";
    if (n == 23) return "veintitrés";
    if (n == 24) return "veinticuatro";
    if (n == 25) return "veinticinco";
    if (n == 26) return "veintiséis";
    if (n == 27) return "veintisiete";
    if (n == 28) return "veintiocho";
    if (n == 29) return "veintinueve";
    int dec = (n / 10) * 10;   // decenas base
    int uni = n % 10;          // unidades
    string base = "";
    if (dec == 30) base = "treinta";
    else if (dec == 40) base = "cuarenta";
    else if (dec == 50) base = "cincuenta";
    else if (dec == 60) base = "sesenta";
    else if (dec == 70) base = "setenta";
    else if (dec == 80) base = "ochenta";
    else if (dec == 90) base = "noventa";
    if (uni == 0) return base;
    return base + " y " + dos_digitos_a_letra(uni);  // construye “treinta y dos” etc.
}

// convierte 1..999 a letras combinando centenas, decenas y unidades
static string hasta_999_a_letra(int n) {
    if (n <= 0 || n > 999) return to_string(n);
    if (n < 100) return dos_digitos_a_letra(n);
    if (n == 100) return "cien";
    int c = n / 100;
    int r = n % 100;
    string pref = "";
    if (c == 1) pref = "ciento";
    else if (c == 2) pref = "doscientos";
    else if (c == 3) pref = "trescientos";
    else if (c == 4) pref = "cuatrocientos";
    else if (c == 5) pref = "quinientos";
    else if (c == 6) pref = "seiscientos";
    else if (c == 7) pref = "setecientos";
    else if (c == 8) pref = "ochocientos";
    else if (c == 9) pref = "novecientos";
    if (r == 0) return pref;
    return pref + " " + dos_digitos_a_letra(r);
}

// convierte numero de mes 1..12 a su nombre en letras
static string mes_a_letra(int m) {
    if (m == 1) return "enero";
    if (m == 2) return "febrero";
    if (m == 3) return "marzo";
    if (m == 4) return "abril";
    if (m == 5) return "mayo";
    if (m == 6) return "junio";
    if (m == 7) return "julio";
    if (m == 8) return "agosto";
    if (m == 9) return "septiembre";
    if (m == 10) return "octubre";
    if (m == 11) return "noviembre";
    if (m == 12) return "diciembre";
    return to_string(m);  // si no esta en 1..12 devuelve cifra
}

// convierte un año (anio) completo a letras manejando miles y centenas
static string anio_a_letra(int y) {
    if (y >= 1000 && y <= 1999) {
        int r = y - 1000;
        if (r == 0) return "mil";
        return string("mil ") + hasta_999_a_letra(r);
    }
    if (y >= 2000 && y <= 2099) {
        int r = y - 2000;
        if (r == 0) return "dos mil";
        return string("dos mil ") + hasta_999_a_letra(r);
    }
    int miles = y / 1000;
    int resto = y % 1000;
    string pref = (miles == 1) ? "mil" : (dos_digitos_a_letra(miles) + " mil");
    if (resto == 0) return pref;
    return pref + " " + hasta_999_a_letra(resto);
}

// convierte dia 1..31 a letras usando la funcion de dos digitos
static string dia_a_letra(int d) {
    if (d >= 1 && d <= 31) return dos_digitos_a_letra(d);
    return to_string(d);
}

// cuenta caracteres logicos en UTF-8 (no bytes)
static int contar_utf8(const string& s) {
    int cnt = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if ((c & 0xC0) != 0x80) ++cnt;  // cuenta solo bytes de inicio
    }
    return cnt;
}

// cuenta caracteres UTF-8 sin espacios
static int contar_utf8_sin_espacios(const string& s) {
    int cnt = 0;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        int adv = 1;
        if (c < 128) {
            if (c != ' ') ++cnt;
            adv = 1;
        } else if ((c & 0xE0) == 0xC0) { ++cnt; adv = 2; }
        else if ((c & 0xF0) == 0xE0) { ++cnt; adv = 3; }
        else if ((c & 0xF8) == 0xF0) { ++cnt; adv = 4; }
        i += adv;
    }
    return cnt;
}

// obtiene el prefijo de N caracteres logicos (no bytes) para iniciales de apellidos
static string utf8_prefijo(const string& s, int n) {
    if (n <= 0) return "";
    int cont = 0;
    size_t i = 0;
    while (i < s.size() && cont < n) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        size_t adv = 1;
        if ((c & 0x80) == 0) adv = 1;
        else if ((c & 0xE0) == 0xC0) adv = 2;
        else if ((c & 0xF0) == 0xE0) adv = 3;
        else if ((c & 0xF8) == 0xF0) adv = 4;
        i += adv;
        ++cont;
    }
    return s.substr(0, i);
}

// convierte un entero a dos digitos con cero a la izquierda para formato 00
static string dos_digitos(int n) {
    if (n >= 0 && n <= 9) return string("0") + to_string(n);
    return to_string(n);
}

int main() {                                   // punto de entrada del programa
    string nombres, ape_materno, ape_paterno;  // textos capturados
    string s_dia, s_mes, s_anio;               // dia, mes, anio en texto para validar formato
    int dia = 0, mes = 0, anio = 0;            // valores numericos basicos
    string pasatiempo;                          // preferencia de pasatiempo

    cout << "Ingrese Nombres (puede incluir segundo nombre): ";
    getline(cin, nombres);

    cout << "Ingrese Apellido materno: ";
    getline(cin, ape_materno);

    cout << "Ingrese Apellido paterno: ";
    getline(cin, ape_paterno);

    nombres = a_mayusculas_es(nombres);
    ape_materno = a_mayusculas_es(ape_materno);
    ape_paterno = a_mayusculas_es(ape_paterno);

     
    while (true) {  // ciclo: solo valida formato numerico y rangos generales
        cout << "Ingrese Mes de nacimiento (00): ";
        getline(cin, s_mes);
        if (!es_solo_digitos_con_longitud(s_mes, 2)) { cout << "Error: Mes invalido. Formato 00.\n"; continue; }
        mes = stoi(s_mes);
        if (mes < 1 || mes > 12) { cout << "Error: Mes fuera de rango (01..12).\n"; continue; }

        cout << "Ingrese Dia de nacimiento (00): ";
        getline(cin, s_dia);
        if (!es_solo_digitos_con_longitud(s_dia, 2)) { cout << "Error: Dia invalido. Formato 00.\n"; continue; }
        dia = stoi(s_dia);
        if (dia < 1 || dia > 31) { cout << "Error: Dia fuera de rango (01..31).\n"; continue; }

        cout << "Ingrese Año de nacimiento (0000): ";
        getline(cin, s_anio);
        if (!es_solo_digitos_con_longitud(s_anio, 4)) { cout << "Error: Año invalido. Formato 0000.\n"; continue; }
        anio = stoi(s_anio);
        if (anio < 1 || anio > 9999) { cout << "Error: Año fuera de rango (0001..9999).\n"; continue; }

        break;  // fecha aceptada por formato y rangos generales
    }

    cout << "¿Que pasatiempo prefieres?\n1) Escuchar musica\n2) Platicar con mis amigxs\n3) Ver series\nElige 1, 2 o 3: ";
    string op; getline(cin, op);
    if (op == "1") pasatiempo = "Escuchar música";
    else if (op == "2") pasatiempo = "Platicar con mis amigxs";
    else if (op == "3") pasatiempo = "Ver series";
    else { cout << "Error: Opcion invalida de pasatiempo.\n"; return 0; }

    string dia_2 = dos_digitos(dia);
    string mes_2 = dos_digitos(mes);
    string anio_4 = s_anio;

    string dia_letra = dia_a_letra(dia);
    string mes_letra = mes_a_letra(mes);
    string anio_letra = anio_a_letra(anio);

    string salida01 = ape_paterno + " " + ape_materno + " " + nombres + " " +
                      dia_2 + " " + mes_2 + " " + anio_4 + " " + pasatiempo;

    string salida02 = ape_paterno + " " + ape_materno + " " + nombres + " " +
                      dia_letra + " " + mes_letra + " " + anio_letra + " " + pasatiempo;

    int len01_con = contar_utf8(salida01);
    int len01_sin = contar_utf8_sin_espacios(salida01);
    int len02_con = contar_utf8(salida02);
    int len02_sin = contar_utf8_sin_espacios(salida02);

    string dos_ape_p = utf8_prefijo(ape_paterno, 2);
    string dos_ape_m = utf8_prefijo(ape_materno, 2);
    string salida05 = dos_ape_p + dos_ape_m;

    cout << "\n--- RESULTADOS ---\n";
    cout << "Salida 01: " << salida01 << "\n";
    cout << "Salida 02: " << salida02 << "\n";
    cout << "Salida 03 (conteo Salida 01 con espacios): " << len01_con << "\n";
    cout << "Salida 03.5 (conteo Salida 01 sin espacios): " << len01_sin << "\n";
    cout << "Salida 04 (conteo Salida 02 con espacios): " << len02_con << "\n";
    cout << "Salida 04.5 (conteo Salida 02 sin espacios): " << len02_sin << "\n";
    cout << "Salida 05 (2 letras de cada apellido): " << salida05 << "\n";

    cin.ignore();  // limpia el salto de línea anterior
    cin.get();     // espera Enter
 
    
    return 0;  // fin normal
}

