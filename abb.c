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
nodo_t* *buscar(const char* clave, nodo_t* *nodo, abb_comparar_clave_t cmp) {
    if (*nodo == NULL) return nodo;

    int comparar = cmp(clave, (*nodo)->clave);
    if (comparar <0) {
        return buscar(clave, &(*nodo)->izq, cmp);
    } else if (comparar >0) {
        return buscar(clave, &(*nodo)->der, cmp);
    } else {
        return nodo;
    }
}

nodo_t* encontrar(const char* clave, nodo_t* nodo, abb_comparar_clave_t cmp) {
    if (nodo == NULL) return nodo;

    int comparar = cmp(clave, nodo->clave);
    if (comparar <0) {
        return encontrar(clave, nodo->izq, cmp);
    } else if (comparar >0) {
        return encontrar(clave, nodo->der, cmp);
    } else {
        return nodo;
    }
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
    nodo_t* const* nodo = buscar_2(clave, &arbol->raiz, arbol->comparar);

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
    nodo_t* *nodo = buscar_2(clave, &arbol->raiz, arbol->comparar);
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
    nodo_t* nodo = encontrar(clave,  arbol->raiz, arbol->comparar);

    if (nodo == NULL) return false;
    return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    nodo_t* nodo = encontrar(clave, arbol->raiz, arbol->comparar);

    if (nodo == NULL) return NULL;
    return (nodo)->dato;
}

void abb_destruir(abb_t *arbol) {
    destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}