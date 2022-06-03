#include "io.h"
#include "compression.h"
#include "decompression.h"
#include <string.h>
#define ASCII_CHARACTERS  256
#define COMPRESS 'C'
#define DECOMPRESS 'D'


int main(int argc, char **argv)
{
  if (*argv[1] == COMPRESS && argc == 3) {

    char inputTextPath[50];
    strcpy(inputTextPath, argv[2]);
    
    int textLen = 0;
    char *inputText = readfile(inputTextPath, &textLen);

    Pair *frecuencyArray = frecuency_calculator(inputText, textLen); //Creo el arreglo de frecuencias (frecuencyArray) 

    HList sortedList = create_sorted_list(frecuencyArray); //Creo la lista ordenada segun frecuencias (sortedList) 
    
    free(frecuencyArray); //[frecuencyArray] no es mas utilizado.

    HList huffmanTree = become_huffman_tree(sortedList); // La lista ordenada pasa a ser un tree de huffman (huffmanTree)
    
    Encoding *encodingsArray = encode_characters(huffmanTree);


    int lenEncodedText = 0;
    char *encodedText = create_binary_text(encodingsArray, inputText, textLen, &lenEncodedText); //Creo el texto encodicado 
    
    free(inputText); // [inputText] no es mas utilizado.

    for(int i = 0; i < ASCII_CHARACTERS ; i++)  //
      free(encodingsArray[i].encod);             // [encodingsArray] no es mas utilizado.
    free(encodingsArray);                        //

    int lenEncodedTextImplode = 0;
    char *encodedTextImplode = implode(encodedText, lenEncodedText, &lenEncodedTextImplode);//Implosiono el texto encodicado

    free(encodedText); // [encodedText] no es mas utilizado.

    int serializedTreeTextLen = 0;
    char *serializedTreeText = serialize_tree(huffmanTree, &serializedTreeTextLen); //Creo el texto del tree de Huffman serializado
    
    hlist_destroy(huffmanTree); // [huffmanTree] no es mas utilizado.
    
    char implodeEncodedTextPath[] = "f.txt.hf", serializedTreeTextPath[] = "f.txt.tree";

    writefile(implodeEncodedTextPath, encodedTextImplode, lenEncodedTextImplode);

    free(encodedTextImplode); //[encodedTextImplode] no es mas utilizado. 

    writefile(serializedTreeTextPath, serializedTreeText, serializedTreeTextLen);
    
    free(serializedTreeText); // [TextoArbolSerializado] no es mas utilizado.

  } else if (*argv[1] == DECOMPRESS && argc == 2) {
   
    char serializedTreePath[] = "f.txt.tree", encodedTextPath[] = "f.txt.hf";
    
    int serializedStringLen = 0;
    char *serializedString = readfile(serializedTreePath, &serializedStringLen);
    
    HList huffmanTree = complete_tree(serializedString, serializedStringLen);

    free(serializedString); // [serializedString] no es mas utilizado.
    
    int implodeEncodedTextLen = 0;
    char *implodeEncodedText = readfile(encodedTextPath, &implodeEncodedTextLen);
    
    int lenEncodedText = 0;
    char *encodedText = explode(implodeEncodedText, implodeEncodedTextLen, &lenEncodedText); 

    free(implodeEncodedText); // [implodeEncodedText] no es mas utilizado.

    int decodedTextLen = 0;
    char *decodedText = decode_text(encodedText, huffmanTree, lenEncodedText, &decodedTextLen);

    hlist_destroy(huffmanTree); // [huffmanTree] no es mas utilizado.
    free(encodedText);        // [encodedText] no es mas utilizado.

    char decodedFilePath[] = "f.txt.dec";
    writefile(decodedFilePath, decodedText, decodedTextLen);

    free(decodedText);    // [decodedText] no es mas utilizado.

  } else {

    printf("Wrong parameters.\n");

  }

  return 0;
}