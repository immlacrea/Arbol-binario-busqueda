#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <string.h>
#include "abb.h"


typedef struct abb abb_t;

typedef struct nodo nodo_t;


struct abb {
    nodo_t* raiz;
    size_t cantidad;
    abb_comparar_clave_t comparar;
    abb_destruir_dato_t destruir_dato;
};

struct nodo {
    char* clave;
    void* dato;
    nodo_t* izq;
    nodo_t* der;
};


nodo_t* nodo_crear(const char* clave, void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) return NULL;

    nodo->dato = dato;
    nodo->clave = strdup(clave);
    nodo->izq = NULL;
    nodo->der = NULL;

    return nodo;
}

//Cambiar implementacion
void* buscar(const char* clave, void* _nodo, abb_comparar_clave_t cmp) {

    nodo_t** nodo = _nodo;

    if (*nodo == NULL) return nodo;

    int comparar = cmp(clave, (*nodo)->clave);

    if ( comparar == 0) return nodo;

    return comparar < 0 ? buscar(clave, &(*nodo)->izq, cmp) : buscar(clave, &(*nodo)->der, cmp);

}

void destruir(nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
    if (nodo != NULL) {
        if (destruir_dato) destruir_dato(nodo->dato);
        
        free(nodo->clave);
        destruir(nodo->izq, destruir_dato);
        destruir(nodo->der, destruir_dato);
        free(nodo);
    }
}

nodo_t* *sucesor(nodo_t* *nodo) {
    if ((*nodo)->izq == NULL) return nodo;
    return sucesor(&(*nodo)->izq);
}

void* borrado_simple(nodo_t* *nodo, abb_destruir_dato_t destruir_dato) {
    void* dato = (*nodo)->dato;
    free((*nodo)->clave);
    nodo_t* nodo_a_borrar = *nodo;

    if ((*nodo)->izq != NULL) {
        *nodo = (*nodo)->izq;
    } else {
        *nodo = (*nodo)->der;
    }
    free(nodo_a_borrar);
    return dato;
}

void* borrar_dos_hijos(nodo_t* *nodo, abb_destruir_dato_t destruir_dato) {
    nodo_t* *reemplazo = sucesor(&(*nodo)->der);
    void* dato = (*nodo)->dato;
    free((*nodo)->clave);

    (*nodo)->dato = (*reemplazo)->dato;
    (*nodo)->clave = strdup((*reemplazo)->clave);
    borrado_simple(reemplazo, destruir_dato);
    return dato;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t* abb = malloc(sizeof(abb_t));

    if (abb == NULL) return NULL;

    abb->raiz = NULL;
    abb->cantidad = 0;
    abb->destruir_dato = destruir_dato;
    abb->comparar = cmp;

    return abb;
}

size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cantidad;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    nodo_t* *nodo = buscar(clave, (void*)&arbol->raiz, arbol->comparar);

    if (*nodo == NULL) {
        *nodo = nodo_crear(clave, dato);
        if (*nodo == NULL) return false;
        arbol->cantidad++;
    } else {
        if (arbol->destruir_dato) arbol->destruir_dato((*nodo)->dato);
        (*nodo)->dato = dato;
    }

    return true;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    nodo_t* *nodo = buscar(clave, &arbol->raiz, arbol->comparar);
    void* dato;
    if (*nodo == NULL) return NULL;

    if ((*nodo)->izq == NULL) {
        dato = borrado_simple(nodo, arbol->destruir_dato);
    } else if ((*nodo)->der == NULL) {
        dato = borrado_simple(nodo, arbol->destruir_dato);
    } else {
        dato = borrar_dos_hijos(nodo, arbol->destruir_dato);
    }
    arbol->cantidad--;
    return dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    nodo_t* const* nodo = buscar(clave, (void*)&arbol->raiz, arbol->comparar);
    
    if (*nodo == NULL) return false;
    return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    nodo_t* const* nodo = buscar(clave, (void*)&arbol->raiz, arbol->comparar);

    if (*nodo == NULL) return NULL;
    return (*nodo)->dato;
}

void abb_destruir(abb_t *arbol) {
    destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}

/* iteradores */

struct abb_iter{
    pila_t* pila;
};

void apilar_hijos_izquierdos(nodo_t* nodo, pila_t* pila){
    while(nodo){
        pila_apilar(pila, nodo);
        nodo = nodo->izq;
    }
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* it = malloc(sizeof(abb_iter_t));
    if(!it) return NULL;
    it->pila = pila_crear();
    apilar_hijos_izquierdos(arbol->raiz, it->pila);
    return it;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(pila_esta_vacia(iter->pila)) return false;
    nodo_t* nodo = pila_desapilar(iter->pila);
    apilar_hijos_izquierdos(nodo->der, iter->pila);
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(pila_esta_vacia(iter->pila)) return NULL;

    nodo_t* nodo = pila_ver_tope(iter->pila);

    return nodo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    if (!arbol->raiz) return ;

    pila_t* pila = pila_crear();

    apilar_hijos_izquierdos(arbol->raiz, pila);

    bool ok = true;

    while(ok && !pila_esta_vacia(pila)){
        nodo_t* nodo = pila_desapilar(pila);
        ok = visitar(nodo->clave,nodo->dato,extra);
        if(!ok) continue;
        apilar_hijos_izquierdos(nodo->der, pila);
    }

    pila_destruir(pila);

}
