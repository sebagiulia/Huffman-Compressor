#ifndef __GLIST_H__
#define __GLIST_H__
#include "slist.h"

typedef struct {
  char caracter, *codif;
  int lenCodif;
} Codificacion;

typedef struct {
    int frec;
    char caracter;
} Par;



typedef struct _GNode {
  Par data;
  struct _GNode *next, *left, *right;
} GNode;

typedef GNode *GList;

typedef void (*FuncionDestructora)(Par dato);
typedef void *(*FuncionCopia)(Par dato);
typedef void (*FuncionVisitante)(Par dato);
typedef void (*FuncionVisitante2Extra)(Par dato, Codificacion *extra1, SList extra2);
typedef int (*FuncionComparadora)(Par dato1, Par dato2);

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, Par dato);


/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, Par dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Inserta un elemento en la lista de forma ordenada.
 */
GList glist_insertar_ordenado(GList list, Par data, FuncionComparadora compare);

/**
 * Inserta un nodo en la lista de forma ordenada.
 */
GList glist_insertar_nodo_ordenado(GList list, GNode *node, FuncionComparadora compare);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
GList glist_formar_arbol(Par data, GList left, GList right);

GList glist_pop(GList list);


#endif /* __GLIST_H__ */


