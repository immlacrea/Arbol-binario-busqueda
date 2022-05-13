#include <stdbool.h>
#include <stdio.h>
#include "testing.h"
#include "abb.h"
#include "string.h"


//Pruebas para un abb vacio
static void prueba_abb_vacio(void) {
    printf("INICIO DE PRUEBAS CON ABB VACIO\n");

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

void pruebas_abb_estudiante() {
    /*Ejecuta las pruebas*/
    prueba_abb_vacio();
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