#include "slist.h"
#include<stdio.h>
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisit visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista){
  int contador = 1;
  SNodo *inicio = lista, *temp;
  if (inicio == NULL) return 0;
  temp = inicio;
  for (;temp->sig != NULL; temp = temp->sig, contador++);
  return contador;
}

void slist_concatenar(SList lista1, SList lista2){
  SNodo *inicio = lista1, *temp;
  if (inicio == NULL) lista1 = lista2;
  else{
    temp = inicio;
    for (; temp->sig != NULL; temp = temp->sig);
    temp->sig = lista2;
  }
}

void slist_insertar(SList *lista, int dato, int posicion){
  SNodo *inicio = *lista, *nodoNuevo = malloc(sizeof(SNodo)), *nodosig, *temp = inicio;
  nodoNuevo->dato = dato;
  int contador = 1;
  if (posicion == 1){
    nodoNuevo->sig = *lista;
    *lista = nodoNuevo;
  } else {
    for (; temp->sig != NULL && contador != posicion - 1; temp = temp->sig, contador++);
    if (contador == posicion - 1){
      nodoNuevo->sig = temp->sig;
      temp->sig = nodoNuevo;
    }
  }
}

void slist_eliminar(SList *lista, int posicion){
  int contador = 1; 
  SNodo *inicio = *lista, *nodoEliminado = malloc(sizeof(SNodo));
  if (inicio != NULL){
    if(posicion != 1){
      SNodo *nodo = inicio;
      for (;nodo->sig != NULL && contador != posicion - 1; nodo = nodo->sig, contador++);
      if (contador == posicion - 1 && nodo->sig != NULL){
        nodoEliminado = nodo->sig;
        nodo->sig = nodoEliminado->sig;
        free(nodoEliminado);
      }
    } else {
      nodoEliminado = *lista;
      *lista = nodoEliminado->sig;
      free(nodoEliminado);
    }
  }
}

int slist_contiene(SList lista, int elemento){
  SNodo *inicio = lista;
  if (inicio == NULL) return 0;
  SNodo *nodo = inicio;
  for (;nodo->sig != NULL; nodo = nodo->sig){
    if(nodo->dato == elemento) return 1;
  }
  if (nodo->dato == elemento) return 1;
  return 0;
}

SList slist_intersecar(SList lista1, SList lista2){
  SNodo *inicio1 = lista1, *inicio2 = lista2;
  if(inicio1 == NULL || inicio2 == NULL) return NULL;
  SList listaInterseccion = NULL;
  SNodo *nodo1 = inicio1, *nodo2 = inicio2;
  for (;nodo1 != NULL; nodo1 = nodo1->sig) {
    for (nodo2 = inicio2 ;nodo2 != NULL; nodo2 = nodo2->sig) {
      if (nodo1->dato == nodo2->dato){
        if(!slist_contiene(listaInterseccion, nodo1->dato)) 
          listaInterseccion = slist_agregar_final(listaInterseccion, nodo1->dato);
      }
    }
  }
  return listaInterseccion;
}

void slist_ordenar(SList lista, FuncionComparables comparar){
  if (lista != NULL){
    SNodo *nodo1 = lista, *nodo2;
    int aux;
    for (; nodo1->sig != NULL; nodo1 = nodo1->sig) {
      for (nodo2 = lista; nodo2->sig != NULL; nodo2 = nodo2->sig) {
        if (comparar(nodo2->dato, nodo2->sig->dato)){
          aux = nodo2->sig->dato;
          nodo2->sig->dato = nodo2->dato;
          nodo2->dato = aux;
        }
      }
    }
  } 
}


void slist_reverso(SList lista){
    SNodo *inicio = lista;
    if (inicio != NULL){
      SNodo *temp = inicio, *temp2, *limite = NULL;
      int aux;
      for (; temp->sig != NULL; temp = temp->sig){
        for (temp2 = inicio; temp2->sig != limite; temp2 = temp2->sig){
          aux = temp2->dato;
          temp2->dato = temp2->sig->dato;
          temp2->sig->dato = aux;
        }
        limite = temp2;
      }
    }
}

void slist_lista_a_string(char *string, SList list) {
  SNodo *temp = list;
  for (int i = 0; temp != NULL; temp = temp->sig, i++)
    string[i] = temp->dato + '0';
}

int slist_len(SList list) {
  int contador = 1;
  if (slist_vacia(list)) return 0;
  for (; list != NULL; list = list->sig, contador++);
  return contador;
}