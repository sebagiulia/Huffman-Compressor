#ifndef __BSTREE_H__
#define __BSTREE_H__


typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;


typedef struct _BST_Nodo *BSTree;

/**
 * Retorna un arbol de busqueda binaria vacio.
 */
BSTree bstee_crear();

/**
 * Destruye el arbol y sus datos.
 */
void bstree_destruir(BSTree, FuncionDestructora);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario.
 */
int bstree_buscar(BSTree, void *, FuncionComparadora);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad del arbol
 * de busqueda binaria.
 */
BSTree bstree_insertar(BSTree, void *, FuncionCopiadora, FuncionComparadora);

/**
 * Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree tree, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit,
                     void *extra);

/**
 * Elimina, si es posible, un elemento del arbol.
 */
BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora comp, FuncionDestructora dest);

void bstree_k_esimo_menor(BSTree root, int *k, FuncionVisitanteExtra visit);

int bstree_validar(BSTree root, FuncionComparadora comp);

#endif //__BSTREE_H__