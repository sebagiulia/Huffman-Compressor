//#ifndef __COMPRIMIR_H__
//#define __COMPRIMIR_H__
//#include "hlist.h"
//
//typedef struct {
//  char caracter, *codif;
//  int lenCodif;
//} Codificacion;
//
//typedef struct {
//    int frec;
//    char caracter;
//} Par;
//
//unsigned char ascii(int n);
//
//int numAscii(unsigned char c);
//
//Par *inicializar_arregloFrec();
//
//Par *calculador_frecuencias(char *textoOriginal, int lenTexto);
//
//int comparar_frecuencias(Par dato1, Par dato2);
//
//HList crear_lista_ord (Par *arregloFrec);
//
//HList crear_arbol_huffman(HList listaOrdenada);
//
//FuncionVisitante2Extra agregar_codigo_caracter(Par dato, Codificacion *arregloCodific, SList listaBits);
//
//void recorrer_arbol(HList tree, Codificacion *arregloCodific, SList listaBits);
//
//Codificacion *codificar_datos(HList arbolHuffman);
//
//void destruir_par(Par par);
//
//void imprimir_cadena(char *cadena, int len);
//#endif