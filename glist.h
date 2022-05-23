#ifndef __GLIST_H__
#define __GLIST_H__


typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);


typedef struct _GNode {
  void *data;
  struct _GNode *next, *left, *right;
} GNode;

typedef GNode *GList;

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
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);


/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Inserta un elemento en la lista de forma ordenada.
 */
GList glist_insertar_ordenado(GList list, void *data, FuncionCopia copy, FuncionComparadora compare)



#endif /* __GLIST_H__ */


