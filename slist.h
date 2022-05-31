#ifndef __SLIST_H__
#define __SLIST_H__

typedef void (*FuncionVisit) (int data);
typedef int (*FuncionComparables) (int data1, int data2); 


/**
 * data: Numero entero.
 * sig: Puntero a node siguiente.
 */
typedef struct _SNodo {
  int data;
  struct _SNodo *next;
} SNodo;

//Lista de SNodos.
typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_create();

/**
 * Destruccion de la lista.
 */
void slist_destroy(SList list);

/**
 * Determina si la lista es vacía.
 */
int slist_empty(SList list);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_add_end(SList list, int data);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_add_start(SList list, int data);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_traverse(SList list, FuncionVisit visit);

/**
 * Longitud de la lista.
 */
int slist_len(SList list);

/**
 * Devuelve una lista sin su ultimo nodo.
 */
SList slist_pop(SList list);

/**
 * Devuelve una lista sin su primer nodo.
 */
SList slist_dequeue(SList list);


/**
 * Devuelve una lista con los elementos de un string pasado.
 */
SList slist_string_to_list(char *string, int len);

/**
 * Devuelve una lista con el codigo Ascii de los caracteres del string pasado.
 */
SList slist_characters_string_to_list(char *string, int len);

/**
 * Asigna los valores de una lista pasada, como caracteres en un string pasado.
 */
void slist_list_to_string(char *string, SList list);

/**
 * Asigna los codigos Ascii de una lista pasada, como caracteres en un string pasado.
 */
void slist_characters_list_to_string(char *string, SList list);

#endif 
