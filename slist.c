#include "slist.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

SList slist_create()
{
  return NULL;
}

void slist_destroy(SList list)
{
  SNodo *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    free(nodeToDelete);
  }
}

int slist_empty(SList list)
{
  return list == NULL;
}

SList slist_add_end(SList list, int data)
{
  SNodo *newNode = malloc(sizeof(SNodo));
  newNode->data = data;
  newNode->next = NULL;

  if (list == NULL)
    return newNode;

  SList node = list;
  for (; node->next != NULL; node = node->next);
  /* ahora 'node' apunta al ultimo elemento en la list */

  node->next = newNode;
  return list;
}

SList slist_add_start(SList list, int data)
{
  SNodo *newNode = malloc(sizeof(SNodo));
  newNode->data = data;
  newNode->next = list;
  return newNode;
}

void slist_traverse(SList list, FuncionVisit visit)
{
  for (SNodo *node = list; node != NULL; node = node->next)
    visit(node->data);
}

int slist_len(SList list)
{
  if (slist_empty(list)) return 0;
  return 1 + slist_len(list->next);
}

void slist_list_to_string(char *string, SList list)
{
  SNodo *temp = list;
  for (int i = 0; temp != NULL; temp = temp->next, i++)
    string[i] = temp->data + '0';
}

SList slist_pop(SList list)
{
  if (slist_empty(list))
    return NULL;
  if (slist_empty(list->next)) {
    free(list);
    return NULL;
  }
  SList temp = list;
  for (; temp->next->next != NULL; temp = temp->next);
  SList nodeEliminado = temp->next;
  temp->next = NULL;
  free(nodeEliminado);
  return list;
}

SList slist_dequeue(SList list)
{
  if (list == NULL) 
    return NULL;
  if (list->next == NULL) {
    free(list);
    return NULL;
  }
  SList listNueva = list->next;
  free(list);
  return listNueva;
}


SList slist_string_to_list(char *string, int len)
{
  SList list = slist_create();
  for (int i = 0; i < len; i++) 
    list = slist_add_end(list, string[i] - '0');
  return list;
}

SList slist_characters_string_to_list(char *string, int len)
{
  SList list = slist_create();
  for (int i = 0; i < len; i++) 
    list = slist_add_end(list, numAscii(string[i]));
  return list;
}

void slist_characters_list_to_string(char *string, SList list)
{
  SNodo *temp = list;
  for (int i = 0; temp != NULL; temp = temp->next, i++) {
    string[i] = ascii(temp->data);
  }
}
