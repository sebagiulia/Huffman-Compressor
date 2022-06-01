#include "compression.h"
#include "io.h"
#include <assert.h>
#include<string.h>
#define ASCII_CHARACTERS 256

void test_initialize_frecuencyArray()
{
  Pair *array = initialize_frecuencyArray();
  for (int i = 0; i < ASCII_CHARACTERS; i++) {
    assert(numAscii(array[i].character) == i);
    assert(array[i].frec == 0);
  }
  printf("[ test_initialize_frecuency ] - SUCCESS\n");
  free(array);
}

void test_frecuency_calculator()
{
  char texto1[] = "Licenciatura en Ciencias de la Computación.";
  Pair *array1 = frecuency_calculator(texto1, 43);
  
  char texto2[] = "\0";
  Pair *array2 = frecuency_calculator(texto2, 1);
  
  char texto3[] = "";
  Pair *array3 = frecuency_calculator(texto3, 0);

  ///test texto1////
  assert(array1[111].frec == 1); // Caracter o. 
  assert(array1[76].frec == 1); // Caracter L.
  assert(array1[67].frec == 2); // Caracter C.
  assert(array1[99].frec == 4); // Caracter c.
  assert(array1[101].frec == 4); // Caracter e.
  assert(array1[105].frec == 5); // Caracter i.

  ///test texto2///
  assert(array2[0].frec == 1); //Caracter \0

  ///test texto3///
  for (int i = 0; i < ASCII_CHARACTERS; i++) 
    assert(array3[i].frec == 0);

  printf("[ test_frecuency_calculator ] - SUCCESS\n");
  
  free(array1);
  free(array2);
  free(array3);
}

void test_create_sorted_list()
{
  char texto[] = "Licenciatura en Ciencias de la Computación.";
  Pair *array = frecuency_calculator(texto, 43);
  HList list = create_sorted_list(array);
  for (; list->next != NULL; list = list->next)       // Chequeamos que los datos Pares estan ordenados
    assert(list->data.frec <= list->next->data.frec); // de menor a mayor segun la frecuencia.

  printf("[ test_create_sorted_list ] - SUCCESS\n");

  free(array);
  hlist_destroy(list);
}

void test_become_huffman_tree()
{

}

void test_encode_characters()
{

}

void test_create_binary_text()
{
  Encoding a, b, c;                                     // Creo un arreglo de codificaciones de 256 caracteres.                   //
  a.character = 'a'; a.encod = "00"; a.encodLen = 2;    // No le daremos importancia a los caracteres distintos de a, b o c.      // 
  b.character = 'b'; b.encod = "01"; b.encodLen = 2;    // Las codificaciones dadas representan un arbol de la forma:             //
  c.character = 'c'; c.encod = "1"; c.encodLen = 1;     //                   /\                                                   //
  Encoding abc[ASCII_CHARACTERS];                       //                  /\ c        ignorando los caracteres que no aparecen. //                                         //
  abc[numAscii(a.character)] = a;                       //                 a  b                                                   //
  abc[numAscii(b.character)] = b;                         
  abc[numAscii(c.character)] = c;                       

  char text[] = "cacbc"; 
  int lenBinaryText = 0;

  char *binaryText = create_binary_text(abc, text, 5, &lenBinaryText);

  //El texto binario deberia ser: c->1 a->00 c->1 b->01 c->1, entonces: 1001011 (largo = 7) 
  char real[] = "1001011";

  assert(lenBinaryText == 7);

  for (int i = 0; i < lenBinaryText; i++) 
    assert(binaryText[i] == real[i]);

  printf("[ test_create_binary_text ] - SUCCESS\n");
  
  free(binaryText);
}

void test_serialize_tree()
{
  Pair a, b, c, d, i1, i2, i3;
  a.character = 'a'; b.character = 'b';
  c.character = 'c'; d.character = 'd';

  HList sheeta = hlist_make_tree(a, NULL, NULL);            // Creamos un arbol de la forma:  //    
  HList sheetb = hlist_make_tree(b, NULL, NULL);            //                                //     
  HList sheetc = hlist_make_tree(c, NULL, NULL);            //              i1                //    
  HList sheetd = hlist_make_tree(d, NULL, NULL);            //             /  \               //     
  HList right = hlist_make_tree(i1, sheeta, sheetd);        //           i2    i3             //   
  HList left = hlist_make_tree(i2, sheetc, sheetb);         //           /\    /\             //   
  HList root = hlist_make_tree(i3, left, right);            //          c  b  a  d            //   

  int stringLen = 0;
  
  char *string = serialize_tree(root, &stringLen);          // La serializacion deberia quedar: 0011011cbad (largo = 11)
  char real[] =  "0011011cbad";

  assert(stringLen == 11);

  for (int i = 0; i < stringLen; i++)
    assert(string[i] == real[i]);

  printf("[ test_serialize_tree ] - SUCCESS\n");
  
  hlist_destroy(root);
  free(string);

}

int main() {
  test_initialize_frecuencyArray();
  test_frecuency_calculator();
  test_create_sorted_list();
  test_create_binary_text();
  test_serialize_tree();
  return 0;
}
