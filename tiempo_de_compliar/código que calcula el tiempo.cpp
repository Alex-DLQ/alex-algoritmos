#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <limits>
using namespace std;

// Jump Search
int jumpSearch(const vector<float>& arr, float x, int n) {
    int paso = sqrt(n), prev = 0;

    while (arr[min(paso, n) - 1] < x) {
        prev = paso;
        paso += sqrt(n);
        if (prev >= n) return -1;
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(paso, n)) return -1;
    }

    return arr[prev] == x ? prev : -1;
}

// QuickSort
void quickSort(vector<float>& arr, int primero, int ultimo) {
    if (primero >= ultimo) return;
    int i = primero, j = ultimo;
    float pivote = arr[(primero + ultimo) / 2];
    while (i <= j) {
        while (arr[i] < pivote) i++;
        while (arr[j] > pivote) j--;
        if (i <= j) swap(arr[i], arr[j]), i++, j--;
    }
    quickSort(arr, primero, j);
    quickSort(arr, i, ultimo);
}

int main() {
    // Abrir el archivo
    ifstream archivo("C://doc//numeros_aleatorios.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<float> arr;
    for (string linea; getline(archivo, linea); arr.push_back(stof(linea)));
    archivo.close();

    // Ordenar el vector
    quickSort(arr, 0, arr.size() - 1);

    // Solicitar la cantidad de números a buscar
    int n;
    cout << "Cuantos numeros deseas buscar? ";
    cin >> n;

    vector<float> numeros_a_buscar(n);
    cout << "Introduce " << n << " numeros a buscar:\n";
    for (int i = 0; i < n; ++i) {
        cin >> numeros_a_buscar[i];
    }

    // Inicializar variables para tiempos mínimo y máximo
    double tiempo_minimo = numeric_limits<double>::max();
    double tiempo_maximo = numeric_limits<double>::lowest();
    float num_minimo = 0, num_maximo = 0;

    int repeticiones = 1000; // Repetir cada búsqueda para calcular tiempos promedio

    for (int i = 0; i < n; ++i) {
        float x = numeros_a_buscar[i];
        double total_tiempo = 0;

        for (int j = 0; j < repeticiones; ++j) {
            auto start_time = chrono::high_resolution_clock::now();
            jumpSearch(arr, x, arr.size());
            auto end_time = chrono::high_resolution_clock::now();

            chrono::duration<double, std::micro> execution_time_micro = end_time - start_time;
            total_tiempo += execution_time_micro.count();
        }

        // Calcular tiempo promedio
        double tiempo_promedio = total_tiempo / repeticiones;

        // Actualizar tiempos mínimos y máximos
        if (tiempo_promedio < tiempo_minimo) {
            tiempo_minimo = tiempo_promedio;
            num_minimo = x;
        }
        if (tiempo_promedio > tiempo_maximo) {
            tiempo_maximo = tiempo_promedio;
            num_maximo = x;
        }

        // Mostrar resultados para cada número
        cout << "\nNumero " << fixed << setprecision(0) << x << " encontrado con tiempo de ejecucion promedio: "
             << fixed << setprecision(10)
             << tiempo_promedio << " microsegundos" << endl;
    }

    // Mostrar resultados finales
    cout << "\nNumero con el menor tiempo de busqueda: " << fixed << setprecision(0) << num_minimo
         << " con tiempo de " << fixed << setprecision(10) << tiempo_minimo << " microsegundos" << endl;

    cout << "Numero con el mayor tiempo de busqueda: " << fixed << setprecision(0) << num_maximo
         << " con tiempo de " << fixed << setprecision(10) << tiempo_maximo << " microsegundos" << endl;

    return 0;
}

