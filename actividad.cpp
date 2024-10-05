#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Definimos la estructura del pasajero
class Pasajero
{
public:
    string nombre;
    int cedula;
    int destino; // 1: Juanchaco, 2: Ladrilleros, 3: La Barra
    Pasajero *siguiente;

    // Constructor
    Pasajero(string n, int c, int d) : nombre(n), cedula(c), destino(d), siguiente(nullptr) {}
};

class GestorPasajeros
{
private:
    Pasajero *inicio;

    // Función para limpiar el buffer de entrada
    void limpiarBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    GestorPasajeros() : inicio(nullptr) {}

    // Destructor para liberar memoria
    ~GestorPasajeros()
    {
        while (inicio != nullptr)
        {
            Pasajero *temp = inicio;
            inicio = inicio->siguiente;
            delete temp;
        }
    }

    // Función para agregar un pasajero
    void agregarPasajero()
    {
        string nombre;
        int cedula, destino;

        cout << "\nIngrese el nombre del pasajero: ";
        limpiarBuffer();
        getline(cin, nombre);

        cout << "Ingrese la cédula del pasajero: ";
        while (!(cin >> cedula))
        {
            cout << "Por favor, ingrese un número válido: ";
            limpiarBuffer();
        }

        do
        {
            cout << "Ingrese el destino (1: Juanchaco, 2: Ladrilleros, 3: La Barra): ";
            while (!(cin >> destino))
            {
                cout << "Por favor, ingrese un número válido: ";
                limpiarBuffer();
            }
        } while (destino < 1 || destino > 3);

        Pasajero *nuevo = new Pasajero(nombre, cedula, destino);
        nuevo->siguiente = inicio;
        inicio = nuevo;

        cout << "Pasajero registrado exitosamente." << endl;
    }

    // Función para mostrar pasajeros
    void mostrarPasajeros() const
    {
        if (inicio == nullptr)
        {
            cout << "No hay pasajeros registrados." << endl;
            return;
        }

        cout << "\nLista de pasajeros:" << endl;
        Pasajero *actual = inicio;
        while (actual != nullptr)
        {
            cout << "Nombre: " << actual->nombre
                 << ", Cédula: " << actual->cedula
                 << ", Destino: ";
            switch (actual->destino)
            {
            case 1:
                cout << "Juanchaco";
                break;
            case 2:
                cout << "Ladrilleros";
                break;
            case 3:
                cout << "La Barra";
                break;
            }
            cout << endl;
            actual = actual->siguiente;
        }
    }

    // Función para ordenar pasajeros
    void ordenarPasajeros()
    {
        if (inicio == nullptr || inicio->siguiente == nullptr)
        {
            return;
        }

        bool intercambio;
        do
        {
            intercambio = false;
            Pasajero *actual = inicio;
            Pasajero *anterior = nullptr;

            while (actual->siguiente != nullptr)
            {
                if (actual->destino > actual->siguiente->destino ||
                    (actual->destino == actual->siguiente->destino &&
                     actual->cedula > actual->siguiente->cedula))
                {

                    Pasajero *temp = actual->siguiente;
                    actual->siguiente = temp->siguiente;
                    temp->siguiente = actual;

                    if (anterior == nullptr)
                    {
                        inicio = temp;
                    }
                    else
                    {
                        anterior->siguiente = temp;
                    }

                    anterior = temp;
                    intercambio = true;
                }
                else
                {
                    anterior = actual;
                    actual = actual->siguiente;
                }
            }
        } while (intercambio);

        cout << "Pasajeros ordenados por destino y cédula." << endl;
    }
};

int main()
{
    GestorPasajeros gestor;
    int opcion;

    do
    {
        cout << "\n1. Registrar pasajero";
        cout << "\n2. Mostrar pasajeros";
        cout << "\n3. Ordenar pasajeros";
        cout << "\n4. Salir";
        cout << "\nSeleccione una opción: ";

        while (!(cin >> opcion))
        {
            cout << "Por favor, ingrese un número válido: ";
            gestor.limpiarBuffer(hola);
        }

        switch (opcion)
        {
        case 1:
            gestor.agregarPasajero();
            break;
        case 2:
            gestor.mostrarPasajeros();
            break;
        case 3:
            gestor.ordenarPasajeros();
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
        }
    } while (opcion != 4);

    return 0;
}