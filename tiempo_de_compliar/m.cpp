#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>  // Para controlar la precisión en la impresión de números decimales
using namespace std;

// Función para realizar Jump Search
int jumpSearch(const vector<float>& arr, float x, int n) {
    int paso = sqrt(n);
    int prev = 0;

    while (arr[min(paso, n) - 1] < x) {
        prev = paso;
        paso += sqrt(n);
        if (prev >= n)
            return -1; // Elemento no encontrado
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(paso, n))
            return -1; // Elemento no encontrado
    }

    if (arr[prev] == x)
        return prev;

    return -1;
}

// Función para intercambiar dos valores
void intercambio(float &x, float &y) {
    float aux = x;
    x = y;
    y = aux;
}

// Función QuickSort
void arreglo(vector<float>& a, int primero, int ultimo) {
    int i, j, central;
    float pivote;

    central = (primero + ultimo) / 2;
    pivote = a[central];
    i = primero;
    j = ultimo;

    do {
        while (a[i] < pivote) i++;
        while (a[j] > pivote) j--;
        if (i <= j) {
            intercambio(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (primero < j) arreglo(a, primero, j);
    if (i < ultimo) arreglo(a, i, ultimo);
}

int main() {
    ifstream archivo;
    string frase;
    float x;
    
    // Usamos un vector dinámico para manejar el tamaño de manera más flexible
    vector<float> arr;
    
    // Abrir el archivo
    archivo.open("C://doc//numeros_aleatorios.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Leer los números del archivo
    while (getline(archivo, frase)) {
        // Convertir cada línea en un número decimal (float)
        arr.push_back(stof(frase));  // Usa stof para convertir a float
    }
    archivo.close();

    // Obtener el tamaño del vector
    int n = arr.size();

    // Ordenar el arreglo
    arreglo(arr, 0, n - 1);

    // Solicitar el número a buscar
    cout << "Dime qué número deseas buscar: ";
    cin >> x;

    // Iniciar el cronómetro antes de llamar a Jump Search
    auto start_time = chrono::high_resolution_clock::now();
    
    // Buscar el índice de 'x' usando Jump Search
    int indice = jumpSearch(arr, x, n);  // Usar el tamaño real del arreglo

    // Finalizar el cronómetro después de ejecutar Jump Search
    auto end_time = chrono::high_resolution_clock::now();

    // Calcular el tiempo de ejecución
    chrono::duration<double> execution_time = end_time - start_time;

    // Imprimir el índice del elemento y el tiempo de ejecución
    if (indice != -1)
        cout << "\nEl número " << x << " está en el índice " << indice << endl;
    else
        cout << "\nEl número " << x << " no se encuentra en el arreglo." << endl;

    // Usar fixed y setprecision para mostrar más decimales en el tiempo de ejecución
    cout << fixed << setprecision(10); // 10 decimales
    cout << "Tiempo de ejecución de Jump Search: " 
         << execution_time.count() << " segundos" << endl;

    return 0;
}




