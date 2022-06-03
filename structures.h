#ifndef __typedefs_h__
#define __typedefs_h__

/**
 * character: Caracter de la tabla Ascii.
 * encod: Codificacion del caracter.
 * encodLen: longitud del arreglo encod.
 */
typedef struct {
  char character, *encod;
  int encodLen;
} Encoding;

/**
 * character: Caracter de la tabla Ascii.
 * frec: Frecuencia del caracter en un texto.
 */
typedef struct {
  int frec;
  char character;
} Pair;

#endif