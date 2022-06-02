#include "compression.h"
#include "io.h"

#define ASCII_CHARACTERS  256

Pair *initialize_frecuencyArray()
{
  Pair *frecuencyArray = malloc(sizeof(Pair) * ASCII_CHARACTERS ); //Creo arreglo de frecuencias.
  for (int i = 0; i < ASCII_CHARACTERS ; i++) {                    //Inicializo el arreglo.
    frecuencyArray[i].frec = 0;
    frecuencyArray[i].character = ascii(i);        
  }
  return frecuencyArray;
}

Pair *frecuency_calculator(char *originalText, int textLen)
{
  Pair *frecuencyArray = initialize_frecuencyArray();    
  for (int i = 0, pos; i < textLen; i++) {             //Le sumo 1 a la frecuencia del caracter [originalText[i]]
    pos = numAscii(originalText[i]);                   //en la posicion [pos] del arreglo de frecuencias.
    frecuencyArray[pos].frec++;
  }
  return frecuencyArray;
}

int compare_frecuencies(Pair data1, Pair data2)
{
  if (data1.frec > data2.frec)
    return 1;
  if (data1.frec == data2.frec)
    return 0;
  return -1;
}

HList create_sorted_list(Pair *frecuencyArray)
{
  HList list = hlist_create();
  int counter = 0;
  while (counter < ASCII_CHARACTERS ) {
    list = hlist_insert_inorder(list, frecuencyArray[counter], (ComparisonFunction)compare_frecuencies);
    counter++;
  }
  return list;
}

HList become_huffman_tree(HList sortedList)
{
  if (hlist_empty(sortedList))
    return sortedList;
  while (!hlist_empty(sortedList->next)) {
    HNode *node1 = sortedList, *node2 = node1->next;  
    int frecsSum = node1->data.frec + node2->data.frec;  // sumo las frecuencias de los nodos que seran
    Pair newPair;                                        // hijos del newNode
    newPair.frec = frecsSum;
    newPair.character = ' ';
    HNode *newNode = hlist_make_tree(newPair, node1, node2);
    sortedList = hlist_disconnect(sortedList); // desconecto node1
    sortedList = hlist_disconnect(sortedList); // desconecto node2
    sortedList = hlist_insert_node_inorder(sortedList, newNode, (ComparisonFunction)compare_frecuencies); // coloca el subarbol de forma ordenada
  }                                                                                                       // (segun su "peso") en la lista nuevamente
  return sortedList;
}

void add_character_code(Pair data, Encoding *encodingsArray, SList bitsList)
{
  int pos = numAscii(data.character);  //Posicion en el arreglo de codificaciones.                  
  int len = slist_len(bitsList);
  encodingsArray[pos].encod = malloc(len);
  encodingsArray[pos].encodLen = len;
  encodingsArray[pos].character = data.character;
  slist_list_to_string(encodingsArray[pos].encod, bitsList);  //Paso lista de bits a arreglo de bits.
}


void allocate_codes(HList tree, Encoding *encodingsArray, SList *bitsList)
{

  if (hlist_empty(tree)) //Caso Base
    return;
  
  if (hlist_sheet(tree))
    add_character_code(tree->data, encodingsArray, *bitsList);

  *bitsList = slist_add_end(*bitsList, 0);              //Me voy a mover a la izquierda (0)
  allocate_codes(tree->left, encodingsArray, bitsList); //Recursion
  
  *bitsList = slist_pop(*bitsList);

  *bitsList = slist_add_end(*bitsList, 1);               //Me voy a mover a la derecha (1)
  allocate_codes(tree->right, encodingsArray, bitsList); //Recursion
  
  *bitsList = slist_pop(*bitsList);

}

Encoding *encode_characters(HList tree)
{
  Encoding *encodingsArray = malloc(sizeof(Encoding) * ASCII_CHARACTERS); //Creo el arreglo de codificaciones.
  SList list = slist_create();
  allocate_codes(tree, encodingsArray, &list);
  slist_destroy(list);
  return encodingsArray;
}

void copy_string(char *address, char *string, int len)
{
  for (int i = 0; i < len; i++) 
    address[i] = string[i];
}

char *create_binary_text(Encoding *encodingsArray , char *originalText, int textLen, int *lenEncodedText)
{
  int sz = 500, size = sz;          //Tamaño inicial del texto codificado (size).
  char *encodedText = malloc(size);
  int counter = 0, pos = 0, i = 0;

  while(counter <= textLen){

    if (i >= size - 30) {    //Me pregunto si estoy cerca de alcanzar el limite de la memoria.    
      size += sz;
      encodedText = realloc(encodedText, size); //Aumento de a (sz) bytes el tamaño del arreglo.
    }

    pos = numAscii(originalText[counter]);  //Numero ascii del character asociado.
    
    int lenCharacterCode =  encodingsArray[pos].encodLen;
    char *characterCode = encodingsArray[pos].encod;

    char *encodeTextAddress = &encodedText[i]; // Direccion a colocar el codigo del character.

    copy_string(encodeTextAddress, characterCode, lenCharacterCode);

    i += lenCharacterCode; //Reubicacion de posicion en encodedText.
    counter++;
  
  }

  *lenEncodedText = i;
  return encodedText;
}

void serialize_structure(HList tree, SList *list) 
{
  if (hlist_sheet(tree)) {                    //Caso base
    *list = slist_add_end(*list, 1);
  } else {                                    //Caso recursivo
    *list = slist_add_end(*list, 0);
    serialize_structure(tree->left, list);
    serialize_structure(tree->right, list);
  }
}

void add_characters(HList tree, SList *charactersList)
{ 
  if (hlist_empty(tree)) return;
  if (hlist_sheet(tree)) {
    char character = tree->data.character;
    *charactersList = slist_add_end(*charactersList, numAscii(character));
  }
  add_characters(tree->left, charactersList);
  add_characters(tree->right, charactersList);
}


char *serialize_tree(HList tree, int *stringLen)
{
  SList structureList = slist_create();                    //Serializacion Estructura (1)      
  serialize_structure(tree, &structureList);
  int structureListLen = slist_len(structureList);

  SList charactersList = slist_create();                    //Serializacion Caracteres (2)
  add_characters(tree, &charactersList);
  int charactersListLen = slist_len(charactersList);

  *stringLen = structureListLen + charactersListLen;   //Union de (1) y (2)
  char *serializedString = malloc(*stringLen);
  slist_list_to_string(serializedString, structureList);
  slist_characters_list_to_string(&serializedString[structureListLen], charactersList);
  
  slist_destroy(structureList);
  slist_destroy(charactersList);
  
  return serializedString; 
}
