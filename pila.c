#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL_ARREGLO 10
#define MODIFICAR_TAMANIO 2
#define COEFICIENTE_ACHICAR 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del ARREGLO 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
pila_t* pila_crear(void){
  pila_t * pila = malloc( sizeof(pila_t) );
  if (!pila) return NULL;
  pila->datos = malloc (sizeof(void*) * CAPACIDAD_INICIAL_ARREGLO);
  if (!pila->datos){
    free(pila);
    return NULL;
  }
  pila->cantidad = 0;
  pila->capacidad = CAPACIDAD_INICIAL_ARREGLO;
  return pila;
}

void pila_destruir(pila_t *pila){
  free(pila->datos);
  free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
  return pila->cantidad == 0;
}

bool redimensionar_pila(pila_t* pila, size_t tamanio){
  void **datos_redimencionados = realloc(pila->datos, tamanio * sizeof(void *));
  if (!datos_redimencionados) return false;
  pila->datos = datos_redimencionados;
  pila->capacidad = tamanio;
  return true;
}

bool pila_apilar(pila_t *pila, void* valor){
  if (pila->capacidad == pila->cantidad){
    bool ok = redimensionar_pila(pila,pila->capacidad * MODIFICAR_TAMANIO);
    if (!ok) return NULL;
  }
  pila->datos[pila->cantidad++] = valor;
  return true;
}

void* pila_ver_tope(const pila_t *pila){
  return pila_esta_vacia(pila) ? NULL : pila->datos[pila->cantidad -1] ;
}

void* pila_desapilar(pila_t *pila){
  if (pila_esta_vacia(pila)) return NULL;
  bool reducir_tamanio_ok = (pila->cantidad * COEFICIENTE_ACHICAR) <= pila->capacidad && (pila->capacidad / MODIFICAR_TAMANIO) >= CAPACIDAD_INICIAL_ARREGLO ;
  if (reducir_tamanio_ok ) redimensionar_pila(pila,pila->capacidad / MODIFICAR_TAMANIO);
  return pila->datos[--pila->cantidad] ;
}
