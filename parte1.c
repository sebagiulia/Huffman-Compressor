#include "glist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARACTERES_TOTALES 256

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char ascii(int n) {
  char c = n;
  return c;
}

int numAscii(char c) {
  int n = c;
  return n;
}

Par *inicializar_arregloFrec() {
  Par *arregloFrec = malloc(sizeof(Par) * CARACTERES_TOTALES);
  for (int i = 0; i < CARACTERES_TOTALES; i++) {
    arregloFrec[i].frec = 0;
    arregloFrec[i].caracter = ascii(i);
  }
  return arregloFrec;
}

Par *calculador_frecuencias(char *textoOriginal, int lenTexto) {
  Par *arregloFrec = inicializar_arregloFrec();
  for (int i = 0, pos; i < lenTexto; i++) {
    pos = numAscii(textoOriginal[i]);
    arregloFrec[pos].frec++;
  }
  return arregloFrec;
}


int comparar_frecuencias(Par dato1, Par dato2) {
  if (dato1.frec > dato2.frec)
    return 1;
  if (dato1.frec == dato2.frec) 
    return strcmp(&dato1.caracter, &dato2.caracter);
  if (dato1.frec < dato2.frec)
    return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GList crear_lista_ord (Par *arregloFrec) {
  GList lista = glist_crear();
  int contador = 0;
  while (contador < CARACTERES_TOTALES) {
    lista = glist_insertar_ordenado(lista, arregloFrec[contador], (FuncionComparadora)comparar_frecuencias);
    contador++;
  }
  return lista;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GList crear_arbol_huffman(GList listaOrdenada) {
  if (glist_vacia(listaOrdenada))
    return listaOrdenada;
  while (!glist_vacia(listaOrdenada->next)) {
    GNode *nodo1 = listaOrdenada, *nodo2 = nodo1->next;
    int sumaFrecs = nodo1->data.frec + nodo2->data.frec;
    Par parNuevo;
    parNuevo.frec = sumaFrecs;
    parNuevo.caracter = ' ';
    GNode *nodoNuevo = glist_formar_arbol(parNuevo, nodo1, nodo2);
    listaOrdenada = glist_pop(listaOrdenada); // desconecto nodo1
    listaOrdenada = glist_pop(listaOrdenada); // desconecto nodo2
    listaOrdenada = glist_insertar_nodo_ordenado(listaOrdenada, nodoNuevo, (FuncionComparadora)comparar_frecuencias);
  }
  return listaOrdenada;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//FuncionVisitante2Extra agregar_codigo_caracter(Par dato, Codificacion *arregloCodific, SList listaBits) {
//  int pos = numAscii(dato.caracter);
//  int len = slist_len(listaBits);
//  (arregloCodific[pos]).codif = malloc(sizeof(char) * len);
//  (arregloCodific[pos]).lenCodif = len;
//  (arregloCodific[pos]).caracter = dato.caracter;
//  slist_lista_a_string(arregloCodific[pos].codif, listaBits);
//  
//}
//
//void recorrer_arbol(GList tree, FuncionVisitante2Extra visit, Codificacion *arregloCodific, ) {
//  if (tree == NULL) return;
//  recorrer_arbol(tree->left, visit, arregloCodific, );
//  if (tree->left == NULL && tree->right == NULL)
//    visit(tree->data, arregloCodific, );
//  recorrer_arbol(tree->right, visit, arregloCodific, );
//}
//
//Codificacion *codificar_datos(GList arbolHuffman) {
//  Codificacion *arregloCodific = malloc(sizeof(Codificacion) * CARACTERES_TOTALES);
//  recorrer_arbol(arbolHuffman, (FuncionVisitante2Extra)agregar_codigo_caracter, arregloCodific, );
//  return arregloCodific;
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destruir_par(Par par) {
}

void imprimir_cadena(char *cadena, int len) {
  for (int i = 0; i < len; i++)
    printf("%c", cadena[i]);
  printf("\n");
}

int main() {
  char texto[] = "Licenciatura en Ciencias de la Computacion";
  Par *arregloFrec = calculador_frecuencias(texto, 42);
  assert(arregloFrec[99].frec == 4);       // letra c
  assert(arregloFrec[72].caracter == 'H'); // letra H
  assert(arregloFrec[65].frec == 0);       // letra A

  GList listaOrdenada = crear_lista_ord(arregloFrec), temp = listaOrdenada;
  for (; temp != NULL; temp = temp->next) 
    printf("[ %c ] -> [ %d ]\n", temp->data.caracter, temp->data.frec);
  


  GList arbolHuffman = crear_arbol_huffman(listaOrdenada);
  
  
  //recorrer_arbol(arbolHuffman, (FuncionVisitante)visit);
  //puts("Lista Codificada:");
  //Codificacion *arregloCodific = codificar_datos(arbolHuffman);
  
  //for (int i = 0; i < CARACTERES_TOTALES; i++) {
  // printf(" %d [ %c ] -- ", i, arregloCodific[i].caracter);
  //  imprimir_cadena(arregloCodific[i].codif, arregloCodific[i].lenCodif);
  //}
    
  glist_destruir(listaOrdenada, (FuncionDestructora)destruir_par);
  return 0;
}