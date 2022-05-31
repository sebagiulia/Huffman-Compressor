#ifndef __HList_H__
#define __HList_H__
#include "slist.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Nodos híbridos que pueden usarse como list o como tree binario.
 * data: data de tipo Pair.
 * next: puntero a node siguiente.
 * left: puntero a node hijo izquierdo.
 * right: puntero a node hijp derecho.
 */
typedef struct _HNode {
  Pair data;
  struct _HNode *next, *left, *right;
} HNode;

//Lista de nodes híbridos o tree binario de nodes híbridos.
typedef HNode *HList;

typedef void (*visitorFunction)(Pair data);
typedef int (*ComparisonFunction)(Pair data1, Pair data2);

/**
 * Devuelve una lista vacía.
 */
HList hlist_create();

/**
 * Destruccion de la lista.
 */
void hlist_destroy(HList list);

/**
 * Determina si la lista es vacía.
 */
int hlist_empty(HList list);

/**
 * Agrega un elemento al inicio de la lista.
 */
HList hlist_add_start(HList list, Pair data);

/**
 * Agrega un elemento al final de la lista.
 */
HList hlist_add_end(HList list, Pair data);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void hlist_traverse(HList list, visitorFunction visit);

/**
 * Inserta un elemento en la lista de forma ordenada.
 */
HList hlist_insert_inorder(HList list, Pair data, ComparisonFunction compare);

/**
 * Inserta un nodo en la lista de forma ordenada.
 */
HList hlist_insert_node_inorder(HList list, HNode *node, ComparisonFunction compare);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
HList hlist_make_tree(Pair data, HList left, HList right);

/**
 * Devuelve la lista sin su primer elemento, el cual no es eliminado.
 */
HList hlist_disconnect(HList list);

/**
 * Devuelve la altura del arbol.
 */
int hlist_tree_height(HList tree);

/**
 * Devuelve 1 si el arbol es una hoja, 0 sino. 
 */
int hlist_sheet(HList tree);

/**
 * Devuelve una hoja.
 */
HList hlist_create_sheet();

#endif /* __HList_H__ */
