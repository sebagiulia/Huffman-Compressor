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
int glist_vacia(GList list) { return list == NULL; }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, Par data) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->next = list;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = data;
  return newNode;
}

GList glist_agregar_final(GList lista, Par data){
  GNode* newNode = malloc(sizeof(GNode));
  newNode->data = data;
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

GList glist_insertar_ordenado(GList list, Par data, FuncionComparadora compare) {
  GNode *newNode = malloc(sizeof(GNode));
  newNode->data = data;
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

GList glist_insertar_nodo_ordenado(GList list, GNode *node, FuncionComparadora compare) {
  if (glist_vacia(list)) return node;
  GNode *nodeTemp = list, *aux;
  if (compare(node->data, nodeTemp->data) <= 0) {
    node->next = nodeTemp;
    return node;
  }
  for(; nodeTemp->next != NULL; nodeTemp = nodeTemp->next){
    if (compare(node->data,nodeTemp->next->data) <= 0){
      aux = nodeTemp->next;
      nodeTemp->next = node;
      node->next = aux;
      return list;
    }
  }
  if (compare(nodeTemp->data, node->data) <= 0){
    nodeTemp->next = node;
    return list;
  }
}

GList glist_pop(GList list){
  if (glist_vacia(list) || glist_vacia(list->next))
    return NULL;
  GList buf = list->next;
  list->next = NULL;
  return buf;
}


GList glist_formar_arbol(Par data, GList left, GList right) {
  GList newNode = malloc(sizeof(GNode));
  newNode->data = data;
  newNode->left = left;
  newNode->right = right;
  newNode->next = NULL;
  return newNode;
}

