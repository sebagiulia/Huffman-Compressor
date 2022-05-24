#ifndef __HList_H__
#define __HList_H__
#include "slist.h"
#include <stdio.h>
#include "comprimir.h"

typedef struct {
  char caracter, *codif;
  int lenCodif;
} Codificacion;

typedef struct {
  int frec;
  char caracter;
} Par;

typedef struct _HNode {
  Par data;
  struct _HNode *next, *left, *right;
} HNode;

typedef HNode *HList;

typedef void (*FuncionDestructora)(Par dato);
typedef void *(*FuncionCopia)(Par dato);
typedef void (*FuncionVisitante)(Par dato);
typedef int (*FuncionComparadora)(Par dato1, Par dato2);

/**
 * Devuelve una lista vacía.
 */
HList hlist_crear();

/**
 * Destruccion de la lista.
 */
void hlist_destruir(HList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int hlist_vacia(HList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
HList hlist_agregar_inicio(HList lista, Par dato);

/**
 * Agrega un elemento al final de la lista.
 */
HList hlist_agregar_final(HList lista, Par dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void hlist_recorrer(HList lista, FuncionVisitante visitar);

/**
 * Inserta un elemento en la lista de forma ordenada.
 */
HList hlist_insertar_ordenado(HList list, Par data, FuncionComparadora compare);

/**
 * Inserta un nodo en la lista de forma ordenada.
 */
HList hlist_insertar_nodo_ordenado(HList list, HNode *node, FuncionComparadora compare);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
HList hlist_formar_arbol(Par data, HList left, HList right);

HList hlist_pop(HList list);

int hlist_altura_arbol(HList arbol);

int hlist_nnodos(HList arbol);

#endif /* __HList_H__ */
