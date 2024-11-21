#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>  // Para controlar la precisi�n en la impresi�n de n�meros decimales
using namespace std;

// Funci�n para realizar Jump Search
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

// Funci�n para intercambiar dos valores
void intercambio(float &x, float &y) {
    float aux = x;
    x = y;
    y = aux;
}

// Funci�n QuickSort
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
    
    // Usamos un vector din�mico para manejar el tama�o de manera m�s flexible
    vector<float> arr;
    
    // Abrir el archivo
    archivo.open("C://doc//numeros_aleatorios.txt", ios::in);
    if (archivo.fail()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Leer los n�meros del archivo
    while (getline(archivo, frase)) {
        // Convertir cada l�nea en un n�mero decimal (float)
        arr.push_back(stof(frase));  // Usa stof para convertir a float
    }
    archivo.close();

    // Obtener el tama�o del vector
    int n = arr.size();

    // Ordenar el arreglo
    arreglo(arr, 0, n - 1);

    // Solicitar el n�mero a buscar
    cout << "Dime qu� n�mero deseas buscar: ";
    cin >> x;

    // Iniciar el cron�metro antes de llamar a Jump Search
    auto start_time = chrono::high_resolution_clock::now();
    
    // Buscar el �ndice de 'x' usando Jump Search
    int indice = jumpSearch(arr, x, n);  // Usar el tama�o real del arreglo

    // Finalizar el cron�metro despu�s de ejecutar Jump Search
    auto end_time = chrono::high_resolution_clock::now();

    // Calcular el tiempo de ejecuci�n
    chrono::duration<double> execution_time = end_time - start_time;

    // Imprimir el �ndice del elemento y el tiempo de ejecuci�n
    if (indice != -1)
        cout << "\nEl n�mero " << x << " est� en el �ndice " << indice << endl;
    else
        cout << "\nEl n�mero " << x << " no se encuentra en el arreglo." << endl;

    // Usar fixed y setprecision para mostrar m�s decimales en el tiempo de ejecuci�n
    cout << fixed << setprecision(10); // 10 decimales
    cout << "Tiempo de ejecuci�n de Jump Search: " 
         << execution_time.count() << " segundos" << endl;

    return 0;
}




