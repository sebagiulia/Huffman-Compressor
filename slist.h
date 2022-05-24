#ifndef __SLIST_H__
#define __SLIST_H__



typedef void (*FuncionVisit) (int dato);

typedef int (*FuncionComparables) (int dato1, int dato2); 

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisit visit);

int slist_longitud(SList lista);

void slist_concatenar(SList lista1, SList lista2);

void slist_insertar(SList *lista,int dato, int posicion);

void slist_eliminar(SList *lista, int posicion);

int slist_contiene(SList lista, int elemento);

SList slist_intersecar(SList lista1, SList lista2);

void slist_ordenar(SList lista, FuncionComparables comparar);

void slist_reverso(SList lista);

void slist_lista_a_string(char *string, SList list);

int slist_len(SList list);

#endif /* __SLIST_H__ */
