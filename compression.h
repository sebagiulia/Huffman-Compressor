#ifndef __Compression_H__
#define __Compression_H__

#include "hlist.h"
#include "structures.h"

/**
 * Devuelve un arreglo de Pares con todos los caracteres inicializados a frecuencia 0.
 * Cada character se ubica en la posicion relativa al codigo ascii del mismo caracter.
 * Ejemplo: numAscii('a') = 97, entonces frecuencyArray[97].caracter = 'a'
 */
Pair *initialize_frecuencyArray();

/**
 * Devuele un arreglo de Pares con la frecuencia de cada caracter calculada y asignada.
 */
Pair *frecuency_calculator(char *originalText, int textLen);

/**
 * Devuelve la comparación de dos Pares según su frecuencia, retorna 1 si el primero
 * frecuenta mas que el 2do, -1 caso contrario y 0 si tienen la misma frecuencia.
 */
int compare_frecuencies(Pair data1, Pair data2);

/**
 * Devuele una lista ordenada de pares segun la frecuencia de cada uno.
 * En este caso se aprovecha el nodo siguiente de la lista híbrida.
 */
HList create_sorted_list(Pair *frecuencyArray);

/**
 * Transforma la lista ordenada a un arbol de Huffman
 * En este caso se aprovechan los nodos hijos de la lista híbrida.
 * Devuelve el mismo puntero de la lista.
 */
HList become_huffman_tree(HList sortedList);

/**
 * Agrega la codificación de un caracter en el arreglo de codificaciones.
 * Cada caracter y su codificación se ubican en la posicion del código ascii del mismo
 * caracter en el arreglo de codificaciones. (Ejemplo linea 10).
 * [bitsList] es la que lleva la codificación del caracter, que luego se transforma a string.
 */
void add_character_code(Pair data, Encoding *encodingsArray, SList bitsList);

/**
 * La función asigna recursivamente la codificación de cada caracter
 * en el arreglo de codificaciones.
 * A medida que se mueve por el arbol, se agrega un 0 o un 1 al final
 * de [bitsList] dependiendo de la dirección de la recursión en el arbol. 
 * La recursión del tree es inorder.
 */
void allocate_codes(HList tree, Encoding *encodingsArray, SList *bitsList);

/**
 * La función crea un arreglo de codificaciones, y le agrega la codificacioń a cada caracter
 * mediante la función <allocate_codes>.
 */
Encoding *encode_characters(HList tree);

/**
 * La función copia un arreglo dado en una dirección dada.
 */
void copy_string(char *address, char *string, int len);

/**
 * Devuelve un arreglo con todas las codificaciones de todos los caracteres del texto original.
 * A medida que recorre el texto original, va agregando la codificación de cada caracter al
 * arreglo final.
 */
char *create_binary_text(Encoding *encodingsArray , char *originalText, int textLen, int *lenEncodedText);

/**
 * Agrega 0 o 1 al final de [*list] a medida que va recorriendo recursivamente el arbol.
 * El recorrido es inorder. Si se topa con una hoja(caso base) agrega un 1, sino agrega
 * un 0. 
 */
void serialize_structure(HList tree, SList *list);

/**
 * La función recorre recursivamente el arbol, si encuentra una hoja, le asigna el primer
 * elemento de [charactersList] a su dato, sino, sigue recursionando de manera inorder.
 */
void add_characters(HList tree, SList *charactersList);

/**
 * Devuelve un puntero al string serializado de [tree].
 * Primero crea los strings serializados de estructura y caracteres y luego los concatena.
 * Guarda en [stringLen] la longitud del mismo.
 */
char *serialize_tree(HList treeDeHuffman, int *stringLen);

#endif