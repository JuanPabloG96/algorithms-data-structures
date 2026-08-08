#include "data_structures/Vector.hpp"

#include <cassert>
#include <iostream>
#include <string>

// Clase auxiliar para rastrear construcciones, copias, movimientos y
// destrucciones
struct ElementoPrueba
{
    std::string nombre;

    ElementoPrueba() : nombre("Por defecto")
    {
        std::cout << "  [Construido por defecto]\n";
    }

    ElementoPrueba(std::string n) : nombre(std::move(n))
    {
        std::cout << "  [Construido con valor: " << nombre << "]\n";
    }

    ElementoPrueba(const ElementoPrueba& otro) : nombre(otro.nombre)
    {
        std::cout << "  [Copiado: " << nombre << "]\n";
    }

    ElementoPrueba(ElementoPrueba&& otro) noexcept
        : nombre(std::move(otro.nombre))
    {
        std::cout << "  [Movido: " << nombre << "]\n";
    }

    ~ElementoPrueba()
    {
        std::cout << "  [Destruido: "
                  << (nombre.empty() ? "Objeto movido" : nombre) << "]\n";
    }

    ElementoPrueba& operator=(const ElementoPrueba& otro)
    {
        nombre = otro.nombre;
        std::cout << "  [Asignacion por copia: " << nombre << "]\n";
        return *this;
    }

    ElementoPrueba& operator=(ElementoPrueba&& otro) noexcept
    {
        nombre = std::move(otro.nombre);
        std::cout << "  [Asignacion por movimiento: " << nombre << "]\n";
        return *this;
    }
};

void probarInsercionYRealloc()
{
    std::cout << "========================================\n";
    std::cout << "1. PRUEBA DE pushBack Y REALLOCATE\n";
    std::cout << "========================================\n";

    Vector<int> vec;
    std::cout << "Capacidad inicial: " << vec.Capacity()
              << " | Size: " << vec.Size() << "\n";

    vec.pushBack(10);
    vec.pushBack(20);
    std::cout << "Capacidad tras 2 elementos: " << vec.Capacity()
              << " | Size: " << vec.Size() << "\n";

    // Debe disparar reallocate a capacidad 4
    vec.pushBack(30);
    std::cout << "Capacidad tras 3 elementos: " << vec.Capacity()
              << " | Size: " << vec.Size() << "\n";

    std::cout << "Contenido del vector: ";
    for (size_t i = 0; i < vec.Size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n\n";
}

void probarCicloDeVidaObjetos()
{
    std::cout << "========================================\n";
    std::cout << "2. PRUEBA DE CICLO DE VIDA (Move vs Copy)\n";
    std::cout << "========================================\n";

    Vector<ElementoPrueba> vec;

    std::cout << "-- Insercion por lvalue (Copia) --\n";
    ElementoPrueba p1("ElementoA");
    vec.pushBack(p1);

    std::cout << "\n-- Insercion por rvalue (Movimiento) --\n";
    vec.pushBack(ElementoPrueba("ElementoB"));

    std::cout << "\n-- Realloc provocado por un 3er elemento --\n";
    vec.pushBack(ElementoPrueba("ElementoC"));

    std::cout << "\n-- Eliminando ultimo elemento con popBack --\n";
    vec.popBack();

    std::cout << "\n-- Limpieza al salir de ambito --\n";
}

void probarCopiaYMovimientoVector()
{
    std::cout << "========================================\n";
    std::cout << "3. PRUEBA DE COPIA Y MOVIMIENTO DE VECTOR\n";
    std::cout << "========================================\n";

    Vector<std::string> original;
    original.pushBack("C++");
    original.pushBack("Data Structures");

    std::cout << "-- Constructor de Copia --\n";
    Vector<std::string> copia = original;
    std::cout << "Copia[0]: " << copia[0] << " | Original[0]: " << original[0]
              << "\n";

    std::cout << "\n-- Constructor de Movimiento --\n";
    Vector<std::string> movido = std::move(original);
    std::cout << "Movido Size: " << movido.Size() << "\n";
    std::cout << "Original despues de move - Size: " << original.Size()
              << " | Data: "
              << (original.Data() == nullptr ? "nullptr" : "Valido") << "\n\n";
}

void probarIteradoresYExcepciones()
{
    std::cout << "========================================\n";
    std::cout << "4. PRUEBA DE ITERADORES Y EXCEPCIONES\n";
    std::cout << "========================================\n";

    Vector<int> vec;
    vec.pushBack(100);
    vec.pushBack(200);
    vec.pushBack(300);

    std::cout << "Uso de Range-based for loop (begin/end):\n";
    for (const auto& val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << "\n\nFront: " << vec.front() << " | Back: " << vec.back()
              << "\n";

    std::cout << "\nProbando at() dentro de limites: " << vec.at(1) << "\n";

    std::cout << "Probando at() fuera de limites (debe lanzar excepcion):\n";
    try
    {
        vec.at(10) = 500;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Excepcion capturada con exito: " << e.what() << "\n";
    }
    std::cout << "\n";
}

int main()
{
    probarInsercionYRealloc();
    probarCicloDeVidaObjetos();
    probarCopiaYMovimientoVector();
    probarIteradoresYExcepciones();

    std::cout << "========================================\n";
    std::cout << "TODAS LAS PRUEBAS COMPLETADAS\n";
    std::cout << "========================================\n";

    return 0;
}
