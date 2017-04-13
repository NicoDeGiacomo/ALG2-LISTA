#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

void pruebas_primitivas_lista_stack(){
    int a = 1;
    int b = 2;
    lista_t lista = lista_crear();
    print_test("Lista recien creada esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    print_test("Instertar primero", lista_insertar_primero(lista, &a));
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, &b));
    print_test("Lista no esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    print_test("Borrar primero", lista_borrar_primero(lista) == &a);
    print_test("Borrar primero", lista_borrar_primero(lista) == &b);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    lista_destruir(lista, NULL);
    print_test("lista destruir", true);
}

void pruebas_primitivas_lista_heap(){
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    *a = 1;
    *b = 2;
    lista_t lista = lista_crear();
    print_test("Lista recien creada esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    print_test("Instertar primero", lista_insertar_primero(lista, a));
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, b));
    print_test("Lista no esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    lista_destruir(lista, free);
    print_test("lista destruir", true);
}

void pruebas_iterador_externo(){
    int a = 1;
    int b = 2;
    lista_t lista = lista_crear();
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &a);

    lista_iter_t iter = lista_iter_crear(lista);
    lista_iter_avanzar(iter);
    lista_iter_insertar(iter,&b);
    print_test("Lista largo es 3", lista_largo(lista) == 3);
    lista_iter_destruir(iter);
    print_test("Borrar primero", lista_borrar_primero(lista) == &a);
    print_test("Borrar primero", lista_borrar_primero(lista) == &b);
    print_test("Borrar primero", lista_borrar_primero(lista) == &a);

    iter = lista_iter_crear(lista);
    lista_iter_avanzar(iter);
    lista_iter_borrar(iter);
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    lista_iter_destruir(iter);
    print_test("Borrar primero", lista_borrar_primero(lista) == &a);
    print_test("Borrar primero", lista_borrar_primero(lista) == &a);

    lista_destruir(lista,NULL);
}

bool contar_repeticiones_uno(void* dato, void* contador){
    if (*(int*)dato == 1){
        *(int*)contador ++;
    }
    return true;
}

void pruebas_iterador_interno(){
    int a = 1;
    int b = 2;
    lista_t lista = lista_crear();
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);

    int contador = 0;
    lista_iterar(lista, contar_repeticiones_uno, &contador);
    print_test("Contador es 3", contador == 3);
    lista_destruir(lista);
}

void pruebas_primitivas_lista(){
    pruebas_primitivas_lista_stack();
    pruebas_primitivas_lista_heap();
}

void pruebas_lista_alumno(){
    pruebas_primitivas_lista();
    pruebas_iterador_externo();
    pruebas_iterador_interno();
}
