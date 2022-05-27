#include "hlist.h"
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
HList hlist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void hlist_destruir(HList list)
{
  HNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    hlist_destruir(nodeToDelete->left);
    hlist_destruir(nodeToDelete->right);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int hlist_vacia(HList list) { return list == NULL; }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
HList hlist_agregar_inicio(HList list, Par data)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->next = list;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = data;
  return newNode;
}

HList hlist_agregar_final(HList lista, Par data)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if (lista == NULL) {
    return newNode;
  }
  HList temp = lista;
  for (; temp->next != NULL; temp = temp->next);
  temp->next = newNode;
  return lista;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void hlist_recorrer(HList list, FuncionVisitante visit)
{
  for (HNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

HList hlist_insertar_ordenado(HList list, Par data, FuncionComparadora compare)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if (hlist_vacia(list))
    return newNode;
  HNode *nodeTemp = list, *aux;
  if (compare(newNode->data, nodeTemp->data) <= 0) {
    newNode->next = nodeTemp;
    return newNode;
  }
  for (; nodeTemp->next != NULL; nodeTemp = nodeTemp->next) {
    if (compare(newNode->data, nodeTemp->next->data) <= 0) {
      aux = nodeTemp->next;
      nodeTemp->next = newNode;
      newNode->next = aux;
      return list;
    }
  }
  nodeTemp->next = newNode;
  return list;
}

HList hlist_insertar_nodo_ordenado(HList list, HNode *node, FuncionComparadora compare)
{
  if (hlist_vacia(list))
    return node;
  HNode *nodeTemp = list, *aux;
  if (compare(node->data, nodeTemp->data) <= 0) {
    node->next = nodeTemp;
    return node;
  }
  for (; nodeTemp->next != NULL; nodeTemp = nodeTemp->next) {
    if (compare(node->data, nodeTemp->next->data) < 0) { 
      aux = nodeTemp->next;
      nodeTemp->next = node;
      node->next = aux;
      return list;
    }
  }
  nodeTemp->next = node;
  return list;
  
}

HList hlist_pop(HList list)
{
  if (hlist_vacia(list) || hlist_vacia(list->next))
    return NULL;
  HList buf = list->next;
  list->next = NULL;
  return buf;
}

HList hlist_formar_arbol(Par data, HList left, HList right)
{
  HList newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->left = left;
  newNode->right = right;
  newNode->next = NULL;
  return newNode;
}

int hlist_altura_arbol(HList arbol)
{
  if (hlist_vacia(arbol))
    return 0;
  int leftheight = 1 + hlist_altura_arbol(arbol->left);
  int rightheight = 1 + hlist_altura_arbol(arbol->right);
  if (rightheight >= leftheight)
    return rightheight;
  return leftheight;
}

int hlist_nnodos(HList arbol)
{
  if (arbol == NULL)
    return 1;
  return 1 + hlist_nnodos(arbol->left) + hlist_nnodos(arbol->right);
}

int hlist_hoja(HList arbol)  {
  return hlist_vacia(arbol->left) && hlist_vacia(arbol->right);
}
