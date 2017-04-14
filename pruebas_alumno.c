//Nombre: Nicolás De Giácomo
//Padron: 99702
//Corrector: Matias C.
#include "lista.h"
#include "testing.h"
#include <stdlib.h>

void pruebas_primitivas_lista_stack(){
    int a = 1;
    int b = 2;
    lista_t* lista = lista_crear();
    print_test("Lista recien creada esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    print_test("Instertar primero", lista_insertar_primero(lista, &a));
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, &b));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    print_test("Ver ultimo",lista_ver_ultimo(lista) == &b);
    print_test("Ver primero", lista_ver_primero(lista) == &a);
    lista_borrar_primero(lista);
    lista_borrar_primero(lista);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, &b));
    lista_destruir(lista, NULL);
    print_test("lista destruir", true);

}

void pruebas_primitivas_lista_heap(){
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    *a = 1;
    *b = 2;
    lista_t* lista = lista_crear();
    print_test("Lista recien creada esta vacia", lista_esta_vacia(lista));
    print_test("Lista largo es 0", lista_largo(lista) == 0);
    print_test("Instertar primero", lista_insertar_primero(lista, a));
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, b));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    lista_destruir(lista, free);
    print_test("lista destruir", true);
}

void pruebas_iterador_externo(){
    int a = 1;
    int b = 2;
    int c = 3;
    lista_t* lista = lista_crear();
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &a);

    lista_iter_t* iter = lista_iter_crear(lista);
    lista_iter_insertar(iter,&b);
    print_test("Insaertar al principio cambia el primero", lista_ver_primero(lista) == &b);
    while (lista_iter_avanzar(iter));
    print_test("Iterador esta al final",lista_iter_al_final(iter));
    lista_iter_insertar(iter,&b);
    print_test("Insertar al final cambia el ultimo", lista_ver_ultimo(lista) == &b);
    lista_iter_destruir(iter);
    iter = lista_iter_crear(lista);
    lista_iter_borrar(iter);
    print_test("Borrar al principio cambia el primero", lista_ver_primero(lista) == &a);
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);

    lista = lista_crear();
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &a);
    iter = lista_iter_crear(lista);
    lista_iter_borrar(iter);
    print_test("Lista largo es 1", lista_largo(lista) == 1);
    lista_iter_borrar(iter);
    print_test("Borrar en lista vacia es NULL", !lista_iter_borrar(iter));
    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);

    lista = lista_crear();
    lista_insertar_ultimo(lista, &a);
    lista_insertar_ultimo(lista, &b);
    lista_insertar_ultimo(lista, &c);

    iter = lista_iter_crear(lista);
    print_test("Ver actual es a", lista_iter_ver_actual(iter) == &a);
    lista_iter_avanzar(iter);
    print_test("Ver actual es b", lista_iter_ver_actual(iter) == &b);
    print_test("Borrar es b", lista_iter_borrar(iter) == &b);
    print_test("Lista largo es 2", lista_largo(lista) == 2);
    print_test("Ver actual es c", lista_iter_ver_actual(iter) == &c);
    print_test("Borrar es c", lista_iter_borrar(iter) == &c);
    print_test("Lista largo es 1", lista_largo(lista) == 1);
    print_test("Avanzar es false", !lista_iter_avanzar(iter));
    print_test("Borrar es NULL", lista_iter_borrar(iter) == NULL);
    print_test("Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    lista_iter_destruir(iter);
    print_test("El primero es a", lista_ver_primero(lista) == &a);
    print_test("El ultimo es a", lista_ver_ultimo(lista) == &a);
    print_test("Inserto b como ultimo", lista_insertar_ultimo(lista,&b));
    print_test("El ultimo es b", lista_ver_ultimo(lista) == &b);

    iter = lista_iter_crear(lista);
    print_test("No al final", !lista_iter_al_final(iter));
    print_test("Ver actual es a", lista_iter_ver_actual(iter) == &a);
    print_test("Borrar es a", lista_iter_borrar(iter) == &a);
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Iterador no al final", !lista_iter_al_final(iter));
    print_test("Ver actual es b", lista_iter_ver_actual(iter) == &b);

    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
}

bool contar_repeticiones_uno(void* dato, void* contador){
    if (*(int*)dato == 1){
        *(int*)contador +=1;
    }
    return true;
}

bool contar_con_corte(void* dato, void* contador){
    if (*(int*)contador == 4){
        return false;
    }
    *(int*)contador +=1;
    return true;
}

void pruebas_iterador_interno(){
    int a = 1;
    int b = 2;
    lista_t* lista = lista_crear();
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);

    int contador = 0;
    lista_iterar(lista, contar_repeticiones_uno, &contador);
    print_test("Contador es 3", contador == 3);


    contador = 0;
    lista_iterar(lista, contar_con_corte, &contador);
    print_test("Contador es 4", contador == 4);

    lista_destruir(lista, NULL);
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
