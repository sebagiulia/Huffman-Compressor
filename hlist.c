#include "hlist.h"
#include <stdlib.h>

/**
 * Devuelve una list vacía.
 */
HList hlist_create() { return NULL; }

/**
 * Destruccion de la list.
 */
void hlist_destroy(HList list)
{
  HNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    hlist_destroy(nodeToDelete->left);
    hlist_destroy(nodeToDelete->right);
    free(nodeToDelete);
  }
}

/**
 * Determina si la list es vacía.
 */
int hlist_empty(HList list) { return list == NULL; }

/**
 * Agrega un elemento al inicio de la list.
 */
HList hlist_add_start(HList list, Pair data)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->next = list;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = data;
  return newNode;
}

HList hlist_add_end(HList list, Pair data)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if (list == NULL) {
    return newNode;
  }
  HList temp = list;
  for (; temp->next != NULL; temp = temp->next);  // Apunta al ultimo node para agregar el newNode
  temp->next = newNode;
  return list;
}

/**
 * Recorrido de la list, utilizando la funcion pasada.
 */
void hlist_traverse(HList list, visitorFunction visit)
{
  for (HNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

HList hlist_insert_inorder(HList list, Pair data, ComparisonFunction compare)
{
  HNode *newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->next = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  if (hlist_empty(list))
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

HList hlist_insert_node_inorder(HList list, HNode *node, ComparisonFunction compare)
{
  if (hlist_empty(list))
    return node;
  HNode *nodeTemp = list, *aux;
  if (compare(node->data, nodeTemp->data) < 0) {  //Notemos que no es <= 0, de esta forma, la insersion tiene que recorrer hasta encontrar
    node->next = nodeTemp;                        //un elemento menor, si no es el caso, lo coloca al final.
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

HList hlist_disconnect(HList list)
{
  if (hlist_empty(list) || hlist_empty(list->next))
    return NULL;
  HList buf = list->next;
  list->next = NULL;
  return buf;
}

HList hlist_make_tree(Pair data, HList left, HList right)
{
  HList newNode = malloc(sizeof(HNode));
  newNode->data = data;
  newNode->left = left;
  newNode->right = right;
  newNode->next = NULL;
  return newNode;
}

int hlist_tree_height(HList tree)
{
  if (hlist_empty(tree))
    return 0;
  int leftheight = 1 + hlist_tree_height(tree->left);
  int rightheight = 1 + hlist_tree_height(tree->right);
  if (rightheight >= leftheight)
    return rightheight;
  return leftheight;
}

int hlist_sheet(HList tree)  {
  if (hlist_empty(tree))
    return 0; 
  return hlist_empty(tree->left) && hlist_empty(tree->right);
}

HList hlist_create_sheet()
{
  Pair par;
  return hlist_make_tree(par, NULL, NULL);
}


