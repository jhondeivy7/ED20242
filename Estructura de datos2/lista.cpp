#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct Estudiante
{
    char nombre[50];
    int codigo_estudiantil;
    float nota;
    struct Estudiante *next;
} Estudiante;

Estudiante *crear_nodo(char *nombre, int codigo_estudiantil, float nota)
{
    Estudiante *nuevo_nodo = (Estudiante *)malloc(sizeof(Estudiante));
    strcpy(nuevo_nodo->nombre, nombre);
    nuevo_nodo->codigo_estudiantil = codigo_estudiantil;
    nuevo_nodo->nota = nota;
    nuevo_nodo->next = NULL;
    return nuevo_nodo;
}

void agregar_estudiante(Estudiante **cabeza, char *nombre, int codigo_estudiantil, float nota)
{
    Estudiante *nuevo_nodo = crear_nodo(nombre, codigo_estudiantil, nota);
    if (*cabeza == NULL)
    {
        *cabeza = nuevo_nodo;
    }
    else
    {
        Estudiante *actual = *cabeza;
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        actual->next = nuevo_nodo;
    }
}

void ordenar_por_codigo_estudiantil(Estudiante **cabeza)
{
    int swapped;
    Estudiante *actual;
    Estudiante *siguiente;
    do
    {
        swapped = 0;
        actual = *cabeza;
        while (actual->next != NULL)
        {
            siguiente = actual->next;
            if (actual->codigo_estudiantil > siguiente->codigo_estudiantil)
            {
                // Intercambiar nodos
                char temp_nombre[50];
                int temp_codigo_estudiantil;
                float temp_nota;
                strcpy(temp_nombre, actual->nombre);
                temp_codigo_estudiantil = actual->codigo_estudiantil;
                temp_nota = actual->nota;
                strcpy(actual->nombre, siguiente->nombre);
                actual->codigo_estudiantil = siguiente->codigo_estudiantil;
                actual->nota = siguiente->nota;
                strcpy(siguiente->nombre, temp_nombre);
                siguiente->codigo_estudiantil = temp_codigo_estudiantil;
                siguiente->nota = temp_nota;
                swapped = 1;
            }
            actual = actual->next;
        }
    } while (swapped);
}

void ordenar_por_nota(Estudiante **cabeza)
{
    int swapped;
    Estudiante *actual;
    Estudiante *siguiente;
    do
    {
        swapped = 0;
        actual = *cabeza;
        while (actual->next != NULL)
        {
            siguiente = actual->next;
            if (actual->nota < siguiente->nota)
            {
                // Intercambiar nodos
                char temp_nombre[50];
                int temp_codigo_estudiantil;
                float temp_nota;
                strcpy(temp_nombre, actual->nombre);
                temp_codigo_estudiantil = actual->codigo_estudiantil;
                temp_nota = actual->nota;
                strcpy(actual->nombre, siguiente->nombre);
                actual->codigo_estudiantil = siguiente->codigo_estudiantil;
                actual->nota = siguiente->nota;
                strcpy(siguiente->nombre, temp_nombre);
                siguiente->codigo_estudiantil = temp_codigo_estudiantil;
                siguiente->nota = temp_nota;
                swapped = 1;
            }
            actual = actual->next;
        }
    } while (swapped);
}

float mayor_nota(Estudiante *cabeza)
{
    float mayor = -1;
    Estudiante *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->nota > mayor)
        {
            mayor = actual->nota;
        }
        actual = actual->next;
    }
    return mayor;
}

float menor_nota(Estudiante *cabeza)
{
    float menor = FLT_MAX;
    Estudiante *actual = cabeza;
    while (actual != NULL)
    {
        if (actual->nota < menor)
        {
            menor = actual->nota;
        }
        actual = actual->next;
    }
    return menor;
}

float promedio_notas(Estudiante *cabeza)
{
    float suma = 0;
    int contador = 0;
    Estudiante *actual = cabeza;
    while (actual != NULL)
    {
        suma += actual->nota;
        contador++;
        actual = actual->next;
    }
    return suma / contador;
}

void mostrar_estudiantes(Estudiante *cabeza)
{
    Estudiante *actual = cabeza;
    while (actual != NULL)
    {
        printf("Nombre: %s, Código Estudiantil: %d, Nota: %.2f\n", actual->nombre, actual->codigo_estudiantil, actual->nota);
        actual = actual->next;
    }
}

int main()
{
    Estudiante *cabeza = NULL;
    int opcion;
    char nombre[50];
    int codigo_estudiantil;
    float nota;

    do
    {
        printf("Menú:\n");
        printf("1. Ingresar datos de estudiantes\n");
        printf("2. Ordenar y mostrar la lista de estudiantes\n");
        printf("3. Mostrar la mayor nota, menor nota y promedio del curso\n");
        printf("4. Salir del programa\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el nombre del estudiante: ");
            scanf("%s", nombre);
            printf("Ingrese el código estudiantil: ");
            scanf("%d", &codigo_estudiantil);
            printf("Ingrese la nota: ");
            scanf("%f", &nota);
            agregar_estudiante(&cabeza, nombre, codigo_estudiantil, nota);
            break;
        case 2:
            printf("Ordenar por:\n");
            printf("1. Código Estudiantil\n");
            printf("2. Nota\n");
            printf("Ingrese su opción: ");
            scanf("%d", &opcion);
            if (opcion == 1)
            {
                ordenar_por_codigo_estudiantil(&cabeza);
            }
            else if (opcion == 2)
            {
                ordenar_por_nota(&cabeza);
            }
            mostrar_estudiantes(cabeza);
            break;
        case 3:
            printf("Mayor nota: %.2f\n", mayor_nota(cabeza));
            printf("Menor nota: %.2f\n", menor_nota(cabeza));
            printf("Promedio de notas: %.2f\n", promedio_notas(cabeza));
            break;
        case 4:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción inválida. Por favor, inténtelo de nuevo.\n");
            break;
        }
    } while (opcion != 4);

    return 0;
}