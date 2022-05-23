#ifndef __GLIST_H__
#define __GLIST_H__


typedef void (*FuncionDestructora)(Par dato);
typedef void *(*FuncionCopia)(Par dato);
typedef void (*FuncionVisitante)(Par dato);
typedef int (*FuncionComparadora)(Par dato1, Par dato2);


typedef struct {
    int frec;
    char caracter;
} Par;

typedef struct _GNode {
  Par data;
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
GList glist_agregar_inicio(GList lista, Par dato, FuncionCopia copiar);


/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, Par dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

/**
 * Inserta un elemento en la lista de forma ordenada.
 */
GList glist_insertar_ordenado(GList list, Par data, FuncionCopia copy, FuncionComparadora compare)



#endif /* __GLIST_H__ */


