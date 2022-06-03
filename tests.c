#include "compression.h"
#include "decompression.h"
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
  HList temp = list;
  for (; temp->next != NULL; temp = temp->next)       // Chequeamos que los datos Pares estan ordenados
    assert(temp->data.frec <= temp->next->data.frec); // de menor a mayor segun la frecuencia.

  printf("[ test_create_sorted_list ] - SUCCESS\n");

  hlist_destroy(list);
  free(array);
}

void test_encode_characters()
{
  Pair a, b, c, d, i1, i2, i3;
  a.character = 'a'; b.character = 'b';
  c.character = 'c'; d.character = 'd';

  HList sheeta = hlist_make_tree(a, NULL, NULL);                     // Creamos un arbol de la forma:  //    
  HList sheetb = hlist_make_tree(b, NULL, NULL);                     //                                //     
  HList sheetc = hlist_make_tree(c, NULL, NULL);                     //              i1                //    
  HList sheetd = hlist_make_tree(d, NULL, NULL);                     //             /  \               //     
  HList right = hlist_make_tree(i1, sheeta, sheetd);                 //           i2    i3             //   
  HList left = hlist_make_tree(i2, sheetc, sheetb);                  //           /\    /\             //   
  HList root = hlist_make_tree(i3, left, right);                     //          c  b  a  d            //   

  Encoding *array = encode_characters(root);                          // Las codificaciones deberían quedar: 
                                                                      // a: 10
  char reala[] = "10", realb[] = "01", realc[] = "00", reald[] = "11";// b: 01     (izquierda: 0, derecha: 1)
                                                                      // c: 00
                                                                      // d: 11
  for (int i = 0; i < array[numAscii('a')].encodLen; i++)
    assert(array[numAscii('a')].encod[i] == reala[i]);

  for (int i = 0; i < array[numAscii('b')].encodLen; i++)
    assert(array[numAscii('b')].encod[i] == realb[i]);

  for (int i = 0; i < array[numAscii('c')].encodLen; i++)
    assert(array[numAscii('c')].encod[i] == realc[i]);

  for (int i = 0; i < array[numAscii('d')].encodLen; i++)
    assert(array[numAscii('d')].encod[i] == reald[i]); 
                         
  printf("[ test_encode_characters ] - SUCCESS\n");

  hlist_destroy(root);
  free(array[numAscii('a')].encod);
  free(array[numAscii('b')].encod);
  free(array[numAscii('c')].encod);
  free(array[numAscii('d')].encod);
  free(array);
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

void test_decode_text() 
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

  char encodedText[] = "1100100101100011";                  //Con "1100100101100011", el texto
  int lenEncodedText = 16;                                  //debería ser "dcbaabcd"

  int lenDecodedText = 0;

  char *decodedText = decode_text(encodedText, root, lenEncodedText, &lenDecodedText);

  char real[] = "dcabbacd";

  for (int i = 0; i < lenDecodedText; i++)
    assert(decodedText[i] == real[i]);

  printf("[ test_decodeText ] - SUCCESS\n");

  free(decodedText);
  hlist_destroy(root);

}

int main() {
  test_initialize_frecuencyArray();
  test_frecuency_calculator();
  test_create_sorted_list();
  test_create_binary_text();
  test_serialize_tree();
  test_encode_characters();
  test_decode_text();
  return 0;
}
