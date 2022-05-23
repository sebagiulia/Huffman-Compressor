#include "glist.h"
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    glist_destruir(nodeToDelete->left, destroy);
    glist_destruir(nodeToDelete->right, destroy);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = list;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = copy(data);
  return newNode;
}

GList glist_agregar_final(GList lista, void* data, FuncionCopia copy){
  GNode* newNode = malloc(sizeof(GNode));
  newNode->data = copy(data);
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if(lista == NULL){
    return newNode;
  }
  GList temp = lista;
  for(; temp->next != NULL; temp = temp->next);
  temp->next = newNode;
  return lista;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_insertar_ordenado(GList list, void *data, FuncionCopia copy, FuncionComparadora compare) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->data = copy(data);
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if (glist_vacia(list)) return newNode;
  GNode *nodeTemp = list, *aux;
  if (compare(newNode->data, nodeTemp->data) <= 0) {
    newNode->next = nodeTemp;
    return newNode;
  }
  for(; nodeTemp->next != NULL; nodeTemp = nodeTemp->next){
    if (compare(newNode->data,nodeTemp->next->data) <= 0){
      aux = nodeTemp->next;
      nodeTemp->next = newNode;
      newNode->next = aux;
      return list;
    }
  }
  if (compare(nodeTemp->data, newNode->data) <= 0){
    nodeTemp->next = newNode;
    return list;
  }
}