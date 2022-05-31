#ifndef __Decompression_H__
#define __Decompression_H__

#include "hlist.h"
#include "io.h"

/**
 * Devuelve un arbol creado a partir de una lista de 0s y 1s.
 * Recursivamente, si el primer elemento de la lista es un 1, creamos 
 * una hoja. Si es un 0, Mediante dos llamados recursivos parseamos el
 * subárbol izquierdo y el subárbol derecho, y armamos el arbol
 * completo con ellos.
 */
HList parse_tree(SList *structureList);

/**
 * La función asigna a los datos de las hojas del arbol los caracteres
 * de la lista.
 * La recursion es inorder.
 */
void fill_tree_sheets(HList tree, SList *charactersList);

/**
 * La función combina las funciones [parse_tree] y [fill_tree_sheets]
 * y devuelve el arbol final.
 */
HList complete_free(char *serializedString, int len);

/**
 * Devuelve un puntero a un string de la decodicación del [encodedText].
 * Iterativamente nos movemos por [encodedText] y recorremos el arbol segun
 * si encontramos un 0(->hijo izquierdo) o un 1(->hijo derecho).
 * Si en el recorrido nos encontramos una hoja, entonces encontramos un caracter
 * el cual agregamos al string decodicado.
 * Luego, comenzamos nuevamente desde la raiz y seguimos consumiendo el string
 * codificado.
 * Guardamos en [lenDecodedText] la longitud del string decoficado.
 */
char *decode_text(char *encodedText, HList huffmanTree, int lenEncodedText, int *lenDecodedText);

#endif

