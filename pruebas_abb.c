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

    //Pruebo que borrar en abb vacio devuelve NULL
    print_test("Borrar devuelve NULL", abb_borrar(abb, A) == NULL);

    //Destruccion de la abb
    abb_destruir(abb);
    print_test("Se destruyo el abb", true);
}

//Pruebas de guardar y obtener varios elementos
static void prueba_abb_guardar_obtener(void) {
    printf("INICIO DE PRUEBAS DE GUARDAR Y OBTENER\n");

    //Claves para las pruebas
    char* A = "a", *B = "b", *C = "c", *D = "d", *E = "e", *F = "f";
    char* datoA = "homero", *datoB = "marge", *datoC = "lisa";
    char* datoD = "bart", *datoE = "abraham", *datoF = "maggie";

    char* G = "g"; 
    char* datoH = "milhouse";

    //Declaro el abb a utilizar
    abb_t* abb = abb_crear(strcmp, NULL);

    //Prueba de creacion
    print_test("Se creo el abb con exito", abb != NULL);

    //Pruebas de guardado
    bool ok = true;
    ok &= abb_guardar(abb, D, datoD) && abb_guardar(abb, B, datoB) && abb_guardar(abb, F, datoF);
    ok &= abb_guardar(abb, A, datoA) && abb_guardar(abb, C, datoC);
    print_test("Se guardaron todos los Simpson", ok);
    print_test("Son 5 los Simpson", abb_cantidad(abb) == 5);

    //Pruebas de pertenecer
    print_test("Bart pertenece al arbol", abb_pertenece(abb, D));
    print_test("Marge pertenece al abb", abb_pertenece(abb, B));
    print_test("Lisa pertenece al abb", abb_pertenece(abb, C));
    print_test("Patty no pertenece al abb", !abb_pertenece(abb, G));
    print_test("Abraham no pertenece al abb", !abb_pertenece(abb, E));

    //Pruebas de obtencion
    print_test("Obtener A devuelve homero", (char*)abb_obtener(abb, A) == datoA);
    print_test("Obtener D devuelve bart", (char*)abb_obtener(abb, D) == datoD);
    print_test("Obtener F, abraham, devuelve NULL", (char*)abb_obtener(abb, E) == NULL);

    //Guardar datos nuevos
    print_test("Se guardo a abraham en el abb", abb_guardar(abb, E, datoE));
    print_test("Abraham ahora pertenece al abb", abb_pertenece(abb, E));
    print_test("Obtener F ahora devuelve abraham", (char*)abb_obtener(abb, E) == datoE);
    print_test("Ahora son 6 los Simpson", abb_cantidad(abb) == 6);
    print_test("Se guardo milhouse en la clave de bart", abb_guardar(abb, D, datoH));
    print_test("Obtener D ahora devuelve milhouse", (char*)abb_obtener(abb, D) == datoH);
    print_test("Siguen siendo 6 los Simpson", abb_cantidad(abb) == 6);

    //Destruccion de la abb
    abb_destruir(abb);
    print_test("Se destruyo el abb", true);
}

//Pruebas de borrar y obtener varios elementos
static void prueba_abb_borrar_obtener(void) {
    printf("INICIO DE PRUEBAS DE BORRAR\n");

    //Claves para las pruebas
    char* A = "a", *B = "b", *C = "c", *D = "d", *E = "e", *F = "f";
    char* datoA = "bart", *datoB = "marge", *datoC = "lisa";
    char* datoD = "homero", *datoE = "maggie", *datoF = "abuelo";

    //Declaro el abb a utilizar
    abb_t* abb = abb_crear(strcmp, NULL);

    //Prueba de creacion
    print_test("Se creo el abb con exito", abb != NULL);

    //Pruebas de guardado
    bool ok = true;
    ok &= abb_guardar(abb, D, datoD) && abb_guardar(abb, B, datoB) && abb_guardar(abb, F, datoF);
    ok &= abb_guardar(abb, A, datoA) && abb_guardar(abb, C, datoC) && abb_guardar(abb, E, datoE);
    print_test("Se guardaron todos los Simpson", ok);
    print_test("Son 6 los Simpson", abb_cantidad(abb) == 6);

    //Pruebas de pertenecer
    print_test("Bart pertenece al arbol", abb_pertenece(abb, A));
    print_test("Marge pertenece al abb", abb_pertenece(abb, B));
    print_test("Lisa pertenece al abb", abb_pertenece(abb, C));

    //Pruebas de obtencion
    print_test("Obtener B devuelve marge", (char*)abb_obtener(abb, B) == datoB);
    print_test("Obtener A devuelve bart", (char*)abb_obtener(abb, A) == datoA);

    //Guardar datos nuevos
    print_test("Se borro a marge (dos hijos) del abb", (char*)abb_borrar(abb, B) == datoB);
    print_test("Marge ahora no pertenece al abb", !abb_pertenece(abb, B));
    print_test("Bart sigue en el abb", abb_pertenece(abb, A));
    print_test("Lisa sigue en el abb", abb_pertenece(abb, C));
    print_test("Ahora son 5 los Simpson", abb_cantidad(abb) == 5);
    print_test("Se borro al abuelo, hijo maggie", (char*)abb_borrar(abb, F) == datoF);
    print_test("El abuelo ahora no pertenece al abb", !abb_pertenece(abb, F));
    print_test("Maggie sigue en el abb", abb_pertenece(abb, E));
    print_test("Ahora son 4 los Simpson", abb_cantidad(abb) == 4);
    print_test("Se borro a maggie, cero hijos", (char*)abb_borrar(abb, E) == datoE);
    print_test("Maggie no esta en el abb", !abb_pertenece(abb, E));  
    print_test("Ahora son 3 los Simpson", abb_cantidad(abb) == 3);

    //Destruccion de la abb
    abb_destruir(abb);
    print_test("Se destruyo el abb", true);
}

void pruebas_abb_estudiante() {
    /*Ejecuta las pruebas*/
    prueba_abb_vacio();
    prueba_abb_guardar_obtener();
    prueba_abb_borrar_obtener();
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