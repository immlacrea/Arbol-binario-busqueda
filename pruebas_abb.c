#include <stdbool.h>
#include <stdio.h>
#include "testing.h"
#include "abb.h"
#include "string.h"

//Funcion para comparar cadenas
int comparar(void* clave1, void* clave2) {
    return strcmp( (char*)clave1, (char*)clave2);
}

//Pruebas para un abb vacio
static void prueba_abb_vacio(void) {
    printf("INICIO DE PRUEBAS CON ABB VACIAO\n");

    //Clave para las pruebas
    char* A = "a";

    //Declaro el abb a utilizar
    abb_t* abb = abb_crear(strcmp, NULL);

    //Inicio de pruebas
    print_test("Se creo un abb nuevo", abb != NULL);

    //Pruebo que la abb nueva esta vacia
    print_test("El abb esta vacio", abb_cantidad(abb) == 0);

    //Obtener en un abb vacio es NULL
    print_test("Obtener un dato es NULL", abb_obtener(abb, A) == NULL);

    //Pruebo que pertenece en un abb vacio es falso
    print_test("Pertenece devuelve falso", !abb_pertenece(abb, A));

    //Pruebo que borrar el primero de la abb devuelve NULL
    //print_test("Borrar primero devuelve NULL", abb_borrar_primero(abb) == NULL);

    //Destruccion de la abb
    abb_destruir(abb);
    print_test("Se destruyo el abb", true);
}
/*
//Pruebas de agregar y sacar en el primer elemento
static void prueba_primer_elemento(void) {
    printf("INICIO DE PRUEBAS DE MANEJO DE PRIMER ELEMENTO DE LA LISTA\n");
    
    //Defino la lista
    lista_t* lista = lista_crear();
    
    //Declaro las variables para pruebas
    int a = 1;
    int b = 2;
    char c = 'c';

    //Agrego el elemento NULL
    print_test("Se agrego el elemento NULL", lista_insertar_primero(lista, NULL));
    print_test("El primero es NULL", lista_ver_primero(lista) == NULL);
    //Agrego elementos a lista
    print_test("Se agrego el valor 1", lista_insertar_primero(lista, &a));
    print_test("El primero es 1", *(int*)lista_ver_primero(lista) == a);
    print_test("Se agrego el valor 2", lista_insertar_primero(lista, &b));
    print_test("El primero es 2", *(int*)lista_ver_primero(lista) == b);
    print_test("Se agrego el valor c", lista_insertar_primero(lista, &c));
    print_test("El primero es c", *(char*)lista_ver_primero(lista) == c);
    print_test("El largo es cuatro", lista_largo(lista) == 4);

    //Quita de elementos
    print_test("Se borro el primer elemento, es c",  lista_borrar_primero(lista) == &c);
    print_test("El nuevo primero es b", lista_ver_primero(lista) == &b);
    print_test("Se borro el primer elemento, es b",  lista_borrar_primero(lista) == &b);
    print_test("El nuevo primero es a", lista_ver_primero(lista) == &a);
    print_test("Se borro el primer elemento, es a",  lista_borrar_primero(lista) == &a);
    print_test("El nuevo primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Se borro el primer elemento, es NULL",  lista_borrar_primero(lista) == NULL);

    //Comportamiento de lista al vaciarla
    print_test("La lista quedo vacia", lista_esta_vacia(lista));
    print_test("Borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("El largo es cero", lista_largo(lista) == 0);
    print_test("Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);

    //Destruyo la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}

//Pruebas de agregar y sacar en el ultimo elemento
static void prueba_ultimo_elemento(void) {
    printf("INICIO DE PRUEBAS DE MANEJO DEL ULTIMO ELEMENTO DE LA LISTA\n");
    
    //Defino la lista
    lista_t* lista = lista_crear();
    
    //Declaro las variables para pruebas
    int a = 1;
    int b = 2;
    char c = 'c';

    //Agrego el elemento NULL
    print_test("Se agrego el elemento NULL", lista_insertar_ultimo(lista, NULL));
    print_test("El ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    //Agrego elementos a lista
    print_test("Se agrego el valor 1", lista_insertar_ultimo(lista, &a));
    print_test("El ultimo es 1", *(int*)lista_ver_ultimo(lista) == a);
    print_test("Se agrego el valor 2", lista_insertar_ultimo(lista, &b));
    print_test("El ultimo es 2", *(int*)lista_ver_ultimo(lista) == b);
    print_test("Se agrego el valor c", lista_insertar_ultimo(lista, &c));
    print_test("El ultimo es c", *(char*)lista_ver_ultimo(lista) == c);
    print_test("El largo es cuatro", lista_largo(lista) == 4);

    //Quita de elementos
    for (int i=0; i<4; i++) {
        lista_borrar_primero(lista);
    }

    //Comportamiento de lista al vaciarla
    print_test("Se borraron todos los elementos", lista_esta_vacia(lista));
    print_test("El largo es cero", lista_largo(lista) == 0);
    print_test("Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);

    //Destruyo la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}

//Pruebas de manejo de un gran volumen de datos
static void prueba_muchos_elementos() {
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    //Creo la lista
    lista_t* lista = lista_crear();

    //Defino la cantidad de elementos a agregar
    size_t tam_max = 1000;

    //Prueba de encolar todos los elementos
    size_t i;
    size_t vector[tam_max];
    bool ok = true;
    bool ok2 = true;
    bool ok3 = true;
    for (i=0; i<tam_max; i++) {
        vector[i] = i;
        ok &= lista_insertar_primero(lista, &vector[i]);
        ok2 &= (lista_ver_primero(lista) == &vector[i]);
        ok3 &= (lista_ver_ultimo(lista) == &vector[0]);
    }
    print_test("Los elementos se agregaron de primeros", ok);
    print_test("El primer elemento es el ultimo agregado", ok2);
    print_test("El ultimo elemento se mantuvo", ok3);
    
    //Prueba de sacar elementos hasta vaciar
    ok = true;
    for (i=tam_max; i>0; i--) {
        ok &= (lista_borrar_primero(lista) == &vector[i-1]);
    }
    print_test("Todos los elementos se quitaron", ok);
    print_test("Siempre se borro el primero", ok);

    //Prueba de lista vaciada
    print_test("La lista quedo vacia", lista_esta_vacia(lista));

    //Destruccion de la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}

//Pruebas de destruccion de datos con funcion FREE
static void prueba_destruccion_con_free() {
    printf("INICIO DE PRUEBAS CON FUNCION DE DESTRUCCION FREE\n");

    //Creo la lista
    lista_t* lista = lista_crear();

    //Inicializacion de punteros de prueba
    int* puntero1 = malloc(sizeof(int));
    int* puntero2 = malloc(sizeof(int));
    int* puntero3 = malloc(sizeof(int));

    //Agregar los datos a la lista
    lista_insertar_primero(lista, puntero1);
    lista_insertar_primero(lista, puntero2);
    lista_insertar_primero(lista, puntero3);
    print_test("Se agregaron los elementos", !lista_esta_vacia(lista));

    //Destruccion de la lista
    lista_destruir(lista, free);
    print_test("Se destruyo la lista con exito", true);
}

//Pruebas de destruccion de datos PILA
static void prueba_destruccion_con_pila() {
    printf("INICIO DE PRUEBAS DE DESTRUCCION CON PILAS\n");

    //Creo la lista
    lista_t* lista = lista_crear();

    //Inicializacion de punteros de prueba
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();

    //Agregar los datos a la lista
    lista_insertar_primero(lista, pila1);
    lista_insertar_primero(lista, pila2);
    lista_insertar_primero(lista, pila3);
    print_test("Se agregaron las pilas", !lista_esta_vacia(lista));


    //Destruccion de la lista
    lista_destruir(lista, pila_destruir_wrapper);
    print_test("Se destruyo la lista con exito", true);
}

//Pruebas de iterador interno
static void prueba_iterador_interno(void) {
    printf("INICIO DE PRUEBAS DE ITERADOR INTERNO\n");
    
    //Defino la lista
    lista_t* lista = lista_crear();
    
    //Declaro las variables para pruebas y agrego a la lista
    int a = 5;
    int vector[a]; 
    for (int i = 0; i<6; i++) {
        vector[i] = i;
        lista_insertar_ultimo(lista, &vector[i]);
    }
    print_test("Se agregaron todos los elementos", lista_largo(lista) == 6);
    
    //Prueba de corte de iterador
    bool ok = true;
    lista_iterar(lista, menor_de_3, &ok);
    print_test("EL iterdor corta cuando debe", !ok);

    //Prueba recorrido total del iterador
    int rta = 15;
    int suma = 0;
    lista_iterar(lista, sumar, &suma);
    print_test("El iterador recorre bien toda la lista", suma==rta);  

    //Destruyo la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}

//Pruebas de iterador externo con lista vacia
static void prueba_iterador_externo_lista_vacia(void) {
    printf("INICIO DE PRUEBAS DE ITERADOR EXTERNO CON LISTA VACIA\n");
    
    //Defino la lista
    lista_t* lista = lista_crear();
    
    //Creo el iterador
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("El iterador se creo con exito", iter!=NULL);
    
    //Prueba del iterador
    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("No se puede avanzar", !lista_iter_avanzar(iter));
    print_test("El actual del iterador es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("No se puede borrar", lista_iter_borrar(iter) == NULL);  

    //Destruyo el iterador
    lista_iter_destruir(iter);
    print_test("Se destruyo el iterador con exito", true);

    //Destruyo la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}

//Pruebas de iterador externo insertar y borrar
static void prueba_iterador_externo_insertar_borrar(void) {
    printf("INICIO DE PRUEBAS DE ITERADOR EXTERNO INSERTAR Y BORRAR\n");
    
    //Defino la lista
    lista_t* lista = lista_crear();
    
    //Creo el iterador
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("El iterador se creo con exito", iter!=NULL);
    
    //Prueba de insertar primero y ultimo
    int tam_max = 5;
    int vector[tam_max];
    bool ok = true;
    for (int i=0; i<tam_max; i++) { //lista: 4-3-2-1-0
        vector[i] = i;
        ok &= (lista_iter_insertar(iter, &vector[i]) && *(int*)lista_ver_primero(lista) == vector[i]);
    }
    print_test("Se agregaron todos los elementos", ok);
    print_test("Insertar al principio modifica el primero de la lista", ok);
    print_test("Insertar al final modifica el final de la lista", *(int*)lista_ver_ultimo(lista) == vector[0]);
    
    //Pruebas de borrar primero, ultimo y medio, e insertar medio
    int medio = 8;
    bool ok_primero = true;
    ok = true;
    for (int j = 4; j>1; j--) {
        ok_primero &= *(int*)lista_ver_primero(lista) == vector[j];
        ok &= *(int*)lista_iter_borrar(iter) == vector[j];
    }
    //lista: 1-0
    print_test("Borrar el primero cambia el primero de la lista", ok_primero);
    lista_iter_avanzar(iter); //actual: 0
    lista_iter_insertar(iter, &medio); //lista: 1-8-0
    print_test("Agregar en el medio lo hace en la posicion correcta", *(int*)lista_ver_ultimo(lista)==0 && *(int*)lista_ver_primero(lista)==1);
    lista_iter_borrar(iter);  //actual: 0
    lista_iter_borrar(iter);
    print_test("Borrar en el medio quita el elemento", lista_ver_ultimo(lista)==lista_ver_primero(lista));
    print_test("Borrar el ultimo cambia el ultimo de la lista", lista_ver_ultimo(lista)==lista_ver_primero(lista));

    //Destruyo el iterador
    lista_iter_destruir(iter);
    print_test("Se destruyo el iterador con exito", true);

    //Destruyo la lista
    lista_destruir(lista, NULL);
    print_test("Se destruyo la lista", true);
}
*/
void pruebas_abb_estudiante() {
    /*Ejecuta las pruebas*/
    prueba_abb_vacio();
    //prueba_primer_elemento();
    //prueba_ultimo_elemento();
    //prueba_muchos_elementos();
    //prueba_destruccion_con_free();
    //prueba_destruccion_con_pila();
    //prueba_iterador_interno();
    //prueba_iterador_externo_lista_vacia();
    //prueba_iterador_externo_insertar_borrar();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif