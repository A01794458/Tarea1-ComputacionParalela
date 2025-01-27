// Tarea1-ComputacionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
//#include "pch.h" 
// En mi VisualStudio no me aceptó esta línea, pero al parecer es un tema de configuración de encabezado de precompilado y no afecta al proyecto en sí
// Microsoft Visual Studio Community 2022 (64 bits) - Current
// Versión 17.9.6
// https://learn.microsoft.com/es-es/cpp/build/compare-inclusion-methods?view=msvc-170
// https://learn.microsoft.com/es-es/cpp/build/creating-precompiled-header-files?view=msvc-170

#include <iostream>
#include <omp.h>
#include <random>

#define N 10000
#define chunk 2
int mostrar = 10;

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << "..." << std::endl;
}

int main()
{
    std::cout << "Suma de arreglos en paralelo\n";
    
    std::cout << "Verificando directivas OMP.\n";    
    #ifdef _OPENMP
        std::cout << "OMP funcionando correctamente." << std::endl;
    #endif
    
    
    
    float a[N], b[N], c[N];
    int i;

    std::random_device rd;
    //Use the Mersenne Twister engine
    //https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 1000);
    int rn = distr(gen);

    std::cout << "Los arreglos son de 1 000 valores que son generados con números aleatorios. Por favor ingresa cuántos valores quieres mostrar, un valor entre 10 y 1000.\n";
    std::cin >> mostrar;
    
    for (i = 0; i < N; i++)
    {
        rn = distr(gen);
        a[i] = rn * 10.0;
        rn = distr(gen);
        b[i] = (rn * 20.0);
    }


    std::cout << "Los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    int pedazos = chunk;
    int tid;
    

    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i)\
    schedule(static,pedazos)

   

    for (i = 0; i < N; i++)
    {
        
        tid = omp_get_thread_num();
        if (i <= mostrar)
        {
            std::cout << "Hilo " << tid << " abierto. Posición: " << i << std::endl;
        }
        c[i] = a[i] + b[i];
        if (i <= mostrar)
        {
            std::cout << "Hilo " << tid << " cerrado." << std::endl;
        }
    }
   

    
    std::cout << "Los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
