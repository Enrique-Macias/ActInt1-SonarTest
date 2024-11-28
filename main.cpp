// Mauricio Lozano Zarate A00833216
// Aleksandra Stupiec A00835071
// Enrique Macías López A01641402

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Esta función busca si una secuencia maliciosa (mcode) está en la transmisión
// Regresa true o false y la posición donde está si la encuentra
bool contieneCodigo(const string &transmision, const string &mcode, size_t &posicion) {
    posicion = transmision.find(mcode);
    return posicion != string::npos;
}

// Verifica si una subcadena es un palíndromo (se lee igual al derecho y al revés)
bool esPalindromo(const string &cadena, int izquierda, int derecha) {
    while (izquierda < derecha) {
        if (cadena[izquierda] != cadena[derecha]) {
            return false; // No es palíndromo si los extremos no coinciden
        }
        izquierda++;
        derecha--;
    }
    return true;
}

// Encuentra el palíndromo más largo en la transmisión y lo regresa junto con su posición
pair<pair<int, int>, string> palindromoMasLargo(const string &transmision) {
    int n = transmision.size();
    int longitudMaxima = 1, inicio = 0;

    // Recorre todas las posibles subcadenas para ver cuál es un palíndromo
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (esPalindromo(transmision, i, j) && (j - i + 1) > longitudMaxima) {
                inicio = i;
                longitudMaxima = j - i + 1;
            }
        }
    }

    // Regresa la posición (en formato que empieza en 1) y el palíndromo
    return make_pair(make_pair(inicio + 1, inicio + longitudMaxima), transmision.substr(inicio, longitudMaxima));
}

// Encuentra la subsecuencia más larga en común entre dos transmisiones
pair<pair<int, int>, string> subsecuenciaComunMasLarga(const string &transmision1, const string &transmision2) {
    int m = transmision1.size();
    int n = transmision2.size();
    int longitudMaxima = 0, indiceFin = 0;
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0)); // Matriz de DP para guardar longitudes

    // Recorremos ambas transmisiones buscando la subsecuencia más larga común
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (transmision1[i - 1] == transmision2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Si coinciden los caracteres, extendemos la subsecuencia
                if (dp[i][j] > longitudMaxima) {
                    longitudMaxima = dp[i][j];
                    indiceFin = i; // Guardamos hasta dónde llega la subsecuencia más larga
                }
            }
        }
    }

    // Regresamos la posición inicial y final de la subsecuencia, junto con la subsecuencia
    return make_pair(make_pair(indiceFin - longitudMaxima + 1, indiceFin), transmision1.substr(indiceFin - longitudMaxima, longitudMaxima));
}

int main() {
    // Abrir archivos de las transmisiones y secuencias maliciosas
    ifstream archivoTransmision1("transmission1.txt");
    ifstream archivoTransmision2("transmission2.txt");
    ifstream archivoMcode1("mcode1.txt");
    ifstream archivoMcode2("mcode2.txt");
    ifstream archivoMcode3("mcode3.txt");

    // Si no se puede abrir alguno de los archivos, lanzamos un error
    if (!archivoTransmision1 || !archivoTransmision2 || !archivoMcode1 || !archivoMcode2 || !archivoMcode3) {
        cerr << "Error abriendo los archivos" << endl;
        return 1;
    }

    // Leer contenido de los archivos
    string transmision1((istreambuf_iterator<char>(archivoTransmision1)), istreambuf_iterator<char>());
    string transmision2((istreambuf_iterator<char>(archivoTransmision2)), istreambuf_iterator<char>());
    string mcode1((istreambuf_iterator<char>(archivoMcode1)), istreambuf_iterator<char>());
    string mcode2((istreambuf_iterator<char>(archivoMcode2)), istreambuf_iterator<char>());
    string mcode3((istreambuf_iterator<char>(archivoMcode3)), istreambuf_iterator<char>());

    // Parte 1: Verificar si el código malicioso está contenido en las transmisiones
    size_t posicion;

    // Transmisión 1
    cout << (contieneCodigo(transmision1, mcode1, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision1, mcode2, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision1, mcode3, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;

    // Transmisión 2
    cout << (contieneCodigo(transmision2, mcode1, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision2, mcode2, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;
    cout << (contieneCodigo(transmision2, mcode3, posicion) ? "true " + to_string(posicion + 1) : "false") << endl;

    // Parte 2: Encontrar el palíndromo más largo en cada archivo de transmisión
    pair<pair<int, int>, string> pal1 = palindromoMasLargo(transmision1);
    pair<pair<int, int>, string> pal2 = palindromoMasLargo(transmision2);

    cout << pal1.first.first << " " << pal1.first.second << " " << pal1.second << endl;
    cout << pal2.first.first << " " << pal2.first.second << " " << pal2.second << endl;

    // Parte 3: Encontrar la subsecuencia común más larga entre los dos archivos de transmisión
    pair<pair<int, int>, string> subseq = subsecuenciaComunMasLarga(transmision1, transmision2);
    cout << subseq.first.first << " " << subseq.first.second << " " << subseq.second << endl;

    return 0;
}
