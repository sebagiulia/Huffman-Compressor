#ifndef __Comprimir_H__
#define __Comprimir_H__

#include "hlist.h"
#include "estructuras.h"

unsigned char ascii(int n);

int numAscii(unsigned char c);

Par *inicializar_arregloFrec();

Par *calculador_frecuencias(char *textoOriginal, int lenTexto);

int comparar_frecuencias(Par dato1, Par dato2);

HList crear_lista_ord(Par *arregloFrec);

HList formar_arbol_Huffman(HList listaOrdenada);

void agregar_codigo_caracter(Par dato, Codificacion *arregloCodific, SList listaBits);

void asignar_codigos(HList arbol, Codificacion *arregloCodific, SList listaBits);

Codificacion *codificar_datos(HList arbolHuffman);

void copiar_cadena(char *direccion, char *string, int len);

char *crear_texto_binario(Codificacion *arregloCodific , char *textoOriginal, int largoTexto, int *largoTextoCodificado);

void serializar_estructura(HList arbolDeHuffman, SList *lista);

void slist_listaCaracteres_a_string(char *string, SList list);

void agregar_numAscii_caracter(Par par, SList *lista);

void agregar_caracteres(HList arbolDeHuffman, SList *listaCaracteres);

char *serializar_arbol(HList arbolDeHuffman, int *largoString);

#endif