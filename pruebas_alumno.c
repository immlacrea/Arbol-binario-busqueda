#include "abb.h"
#include "hash.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CANTIDAD_PRUEBAS_VOLUMEN 5000

static void prueba_crear_abb_vacio()
{
  printf("INICIANDO PRUEBAS ABB VACIO\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio()
{
  printf("INICIANDO PRUEBAS ITERAR ABB VACIO\n");
    abb_t* abb = abb_crear(strcmp,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar()
{
  printf("INICIANDO PRUEBAS ABB INSERTAR\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "chancho", *valor4 = "oing";
    char *clave = "", *valor = NULL;


    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave4 es valor1", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave4, es valor1", abb_borrar(abb, clave4) == valor4);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar()
{
  printf("INICIANDO PRUEBAS ABB REEMPLAZAR\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir()
{
  printf("INICIANDO PRUEBAS ABB REEMPLAZAR CON DESTRUIR\n");
    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar()
{
  printf("INICIANDO PRUEBAS ABB BORRAR\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_volumen()
{
  printf("INICIANDO PREUBAS ABB VOLUMEN\n");
    abb_t* arbol = abb_crear(strcmp,NULL);
    hash_t* hash = hash_crear(NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(CANTIDAD_PRUEBAS_VOLUMEN * largo_clave);

    unsigned valores[CANTIDAD_PRUEBAS_VOLUMEN];

    bool ok = true;
    for (unsigned i = 0; i < CANTIDAD_PRUEBAS_VOLUMEN; i++){
      srand(i);
      sprintf(claves[i], "%d", rand() % 300000);

      if (hash_pertenece(hash, claves[i])){
        bool pertenece = true;
        unsigned k = 0;

        while (pertenece){
          srand(k * (unsigned)time(NULL) + 13);
          sprintf(claves[i], "%d", rand() % 300000);

          if (hash_pertenece(hash, claves[i])){
            k++;
            continue;
          }

          pertenece = false;
        }

      }

      valores[i] = i;
      ok = hash_guardar(hash, claves[i], &valores[i]);
      ok = abb_guardar(arbol, claves[i], &valores[i]);

      if (!ok) break;

    }

    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(arbol) == CANTIDAD_PRUEBAS_VOLUMEN);

    for (int i = 0; i<CANTIDAD_PRUEBAS_VOLUMEN; i++){
      ok = abb_pertenece(arbol, claves[i]);
      ok = *(unsigned*)abb_obtener(arbol, claves[i]) == valores[i];

      if (!ok) break;

    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(arbol) == CANTIDAD_PRUEBAS_VOLUMEN);

    for (int i = 0; i<CANTIDAD_PRUEBAS_VOLUMEN; i++){
      ok = *(unsigned*)abb_borrar(arbol, claves[i]) == valores[i];

      if (!ok) break;

    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    free(claves);
    hash_destruir(hash);
    abb_destruir(arbol);
}

bool imprimir_todas(const char* clave,void* dato,void* extra){
  printf("Clave: %s\n",clave);
  return true;
}

bool imprimir_algunas(const char* clave,void* dato,void* extra){
  if (*(size_t*)extra>=4){
    return false;
  }
  *(size_t*)extra+=1;
  printf("Clave: %s\n",clave);
  return true;
}

static void prueba_abb_iter_interno_imprimir_claves(){
  printf("INICIO DE PRUEBAS ITERADOR INTERNO IMPRIMIR TODAS LAS CLAVES\n");
	abb_t* abb = abb_crear(strcmp,NULL);

	char *claves[] = {"perro", "gato", "vaca"};
	char *valores[] = {"guau", "miau", "mu"};

	/* Inserta 3 valores */
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
	print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
	print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));
	abb_in_order(abb,imprimir_todas,NULL);

  abb_destruir(abb);
}

void pruebas_abb_iter_interno_imprimir_algunas_claves(){
  printf("INICIO DE PRUEBAS ITERADOR INTERNO IMPRIMIR ALGUNAS CLAVES\n");
	abb_t* abb = abb_crear(strcmp,NULL);

	char *claves[] = {"perro","gato","vaca","telefono","leo","martin","casino","auto"};
	char *valores[] = {"guau","miau","mu","ring","Rolon","Stefanelli","ruleta","motor"};

	/* Inserta 8 valores */
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
	print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
	print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));
	print_test("Prueba abb insertar clave4", abb_guardar(abb, claves[3], valores[3]));
	print_test("Prueba abb insertar clave5", abb_guardar(abb, claves[4], valores[4]));
	print_test("Prueba abb insertar clave6", abb_guardar(abb, claves[5], valores[5]));
	print_test("Prueba abb insertar clave7", abb_guardar(abb, claves[6], valores[6]));
	print_test("Prueba abb insertar clave8", abb_guardar(abb, claves[7], valores[7]));
	size_t contador=0;
	abb_in_order(abb,imprimir_algunas,&contador);

  abb_destruir(abb);
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar()
{
  printf("INICIANDO PRUEBAS ABB ITERADOR EXTERNO\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    /* Se anula esta prueba por diferencias de criterios */
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_abb_alumno(){
	prueba_crear_abb_vacio();
	prueba_iterar_abb_vacio();
	prueba_abb_insertar();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_volumen();
	prueba_abb_iter_interno_imprimir_claves();
	pruebas_abb_iter_interno_imprimir_algunas_claves();
	prueba_abb_iterar();
}

int main(){
  pruebas_abb_alumno();
  return 0;
}
