#include "hlist.h"
#include "comprimir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARACTERES_TOTALES 256

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char ascii(int n)
{
  unsigned char c = n;
  return c;
}

int numAscii(unsigned char c)
{
  int n = c;
  return n;
}

Par *inicializar_arregloFrec()
{
  Par *arregloFrec = malloc(sizeof(Par) * CARACTERES_TOTALES);
  for (int i = 0; i < CARACTERES_TOTALES; i++) {
    arregloFrec[i].frec = 0;
    arregloFrec[i].caracter = ascii(i);
  }
  return arregloFrec;
}

Par *calculador_frecuencias(char *textoOriginal, int lenTexto)
{
  Par *arregloFrec = inicializar_arregloFrec();
  for (int i = 0, pos; i < lenTexto; i++) {
    pos = numAscii(textoOriginal[i]);
    arregloFrec[pos].frec++;
  }
  return arregloFrec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int comparar_frecuencias(Par dato1, Par dato2)
{
  if (dato1.frec > dato2.frec)
    return 1;
  if (dato1.frec == dato2.frec)
    return strcmp(&dato1.caracter, &dato2.caracter);
  if (dato1.frec < dato2.frec)
    return -1;
}

HList crear_lista_ord(Par *arregloFrec)
{
  HList lista = hlist_crear();
  int contador = 0;
  while (contador < CARACTERES_TOTALES) {
    lista = hlist_insertar_ordenado(lista, arregloFrec[contador], (FuncionComparadora)comparar_frecuencias);
    contador++;
  }
  return lista;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HList crear_arbol_huffman(HList listaOrdenada)
{
  if (hlist_vacia(listaOrdenada))
    return listaOrdenada;
  while (!hlist_vacia(listaOrdenada->next)) {
    HNode *nodo1 = listaOrdenada, *nodo2 = nodo1->next;
    int sumaFrecs = nodo1->data.frec + nodo2->data.frec;
    Par parNuevo;
    parNuevo.frec = sumaFrecs;
    parNuevo.caracter = ' ';
    HNode *nodoNuevo = hlist_formar_arbol(parNuevo, nodo1, nodo2);
    listaOrdenada = hlist_pop(listaOrdenada); // desconecto nodo1
    listaOrdenada = hlist_pop(listaOrdenada); // desconecto nodo2
    listaOrdenada = hlist_insertar_nodo_ordenado(listaOrdenada, nodoNuevo, (FuncionComparadora)comparar_frecuencias);
  }
  return listaOrdenada;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void *agregar_codigo_caracter(Par dato, Codificacion *arregloCodific, SList listaBits)
{
  int pos = numAscii(dato.caracter);
  int len = slist_len(listaBits);
  (arregloCodific[pos]).codif = malloc(sizeof(char) * len);
  (arregloCodific[pos]).lenCodif = len;
  (arregloCodific[pos]).caracter = dato.caracter;
  slist_lista_a_string(arregloCodific[pos].codif, listaBits);
}

void recorrer_arbol(HList tree, Codificacion *arregloCodific, SList listaBits)
{
  if (tree == NULL)
    return;
  recorrer_arbol(tree->left, arregloCodific, slist_agregar_final(listaBits, 0));
  if (tree->left == NULL && tree->right == NULL)
    agregar_codigo_caracter(tree->data, arregloCodific, listaBits);
  listaBits = slist_desapilar(listaBits);
  recorrer_arbol(tree->right, arregloCodific, slist_agregar_final(listaBits, 1));
  listaBits = slist_desapilar(listaBits);
}

Codificacion *codificar_datos(HList arbolHuffman)
{
  Codificacion *arregloCodific = malloc(sizeof(Codificacion) * CARACTERES_TOTALES);
  SList list = slist_crear();
  recorrer_arbol(arbolHuffman, arregloCodific, list);
  return arregloCodific;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destruir_par(Par par) { }

void imprimir_cadena(char *cadena, int len)
{
  for (int i = 0; i < len; i++)
    printf("%c", cadena[i]);
  printf("\n");
}

int main()
{
  char texto[] = "Licenciatura en Ciencias de la Computacion";
  Par *arregloFrec = calculador_frecuencias(texto, 42);
  assert(arregloFrec[99].frec == 4);       // letra c
  assert(arregloFrec[72].caracter == 'H'); // letra H
  assert(arregloFrec[65].frec == 0);       // letra A

  HList listaOrdenada = crear_lista_ord(arregloFrec), temp = listaOrdenada;
  for (; temp != NULL; temp = temp->next)
    printf("[ %c ] -> [ %d ]\n", temp->data.caracter, temp->data.frec);

  HList arbolHuffman = crear_arbol_huffman(listaOrdenada);
  puts("Lista Codificada:");
  Codificacion *arregloCodific = codificar_datos(arbolHuffman);

  for (int i = 0; i < CARACTERES_TOTALES; i++) {
    printf(" %d [ %c ] -- [%d] -- ", i, arregloCodific[i].caracter, arregloCodific[i].lenCodif);
    imprimir_cadena(arregloCodific[i].codif, arregloCodific[i].lenCodif);
  }

  hlist_destruir(listaOrdenada, (FuncionDestructora)destruir_par);
  return 0;
}