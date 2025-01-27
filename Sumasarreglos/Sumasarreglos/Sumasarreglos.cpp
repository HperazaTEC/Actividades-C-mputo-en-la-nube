#include <iostream>    
#include <cstdlib>     
#include <ctime>     
#include <omp.h>      


void imprimeArreglo(const int* arreglo, int n);

int main() {
    // Semilla aleatoria 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // ========== Primera configuración ==========
    // Config 1: N = 1000, CHUNK = 100

    int N1 = 1000;
    int CHUNK1 = 100;
    const int MOSTRAR = 10; 

    // Crear los arreglos
    int* a1 = new int[N1];
    int* b1 = new int[N1];
    int* c1 = new int[N1];

    // Llenar los arreglos
    for (int i = 0; i < N1; i++) {
        a1[i] = i * 2;
        b1[i] = i * 3;
    }

    std::cout << "\n=== Primera ejecucion: N = " << N1
        << ", CHUNK = " << CHUNK1 << " ===\n";

    std::cout << "Algunos valores de A1:\n";
    imprimeArreglo(a1, MOSTRAR);
    std::cout << "Algunos valores de B1:\n";
    imprimeArreglo(b1, MOSTRAR);

    // Paralelizar la suma
#pragma omp parallel for schedule(static, CHUNK1) shared(a1, b1, c1)
    for (int i = 0; i < N1; i++) {
        c1[i] = a1[i] + b1[i];
    }

    //  resultados de C1
    std::cout << "Algunos valores de C1 (suma de A1 y B1):\n";
    imprimeArreglo(c1, MOSTRAR);

    // Liberar la memoria
    delete[] a1;
    delete[] b1;
    delete[] c1;


    // ========== Segunda configuración ==========
    // 
    // Config 2: N = 5000, CHUNK = 200
    int N2 = 5000;
    int CHUNK2 = 200;

    // Crear arreglos dinámicamente para la 2da ejecución
    int* a2 = new int[N2];
    int* b2 = new int[N2];
    int* c2 = new int[N2];

    // Llenar los arreglos 
    for (int i = 0; i < N2; i++) {
        a2[i] = rand() % 100; // aleatorio entre 0 y 99
        b2[i] = rand() % 100; // aleatorio entre 0 y 99
    }

    std::cout << "\n=== Segunda ejecucion: N = " << N2
        << ", CHUNK = " << CHUNK2 << " ===\n";

    std::cout << "Algunos valores de A2:\n";
    imprimeArreglo(a2, MOSTRAR);
    std::cout << "Algunos valores de B2:\n";
    imprimeArreglo(b2, MOSTRAR);

    // Paralelizar la suma
#pragma omp parallel for schedule(static, CHUNK2) shared(a2, b2, c2)
    for (int i = 0; i < N2; i++) {
        c2[i] = a2[i] + b2[i];
    }

    std::cout << "Algunos valores de C2 (suma de A2 y B2):\n";
    imprimeArreglo(c2, MOSTRAR);

    delete[] a2;
    delete[] b2;
    delete[] c2;

    // Mensaje final
    std::cout << "\nEjecutamos DOS configuraciones distintas de suma paralela.\n";
    return 0;
}

void imprimeArreglo(const int* arreglo, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arreglo[i] << " ";
    }
    std::cout << std::endl;
}
