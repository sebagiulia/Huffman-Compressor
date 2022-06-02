#include "decompression.h"
#include <assert.h>

#define ASCII_CHARACTERS  256


HList parse_tree(SList *structureList) 
{
  if ((*structureList)->data) //Si es igual a 1
    return hlist_create_sheet();       
                              //Si no:
  HList tree = hlist_create_sheet();

  *structureList = slist_dequeue(*structureList);  //Quito el caracter ya utilizado.
  tree->left = parse_tree(structureList);  //Recursión.      
                                                   
  *structureList = slist_dequeue(*structureList);  //Quito el caracter ya utilizado.
  tree->right = parse_tree(structureList);  //Recursión.

  return tree;
}

void fill_tree_sheets(HList tree, SList *charactersList)
{
  if (hlist_sheet(tree)) {                                    // Caso base
    tree->data.character = ascii((*charactersList)->data);
    *charactersList = slist_dequeue(*charactersList);         //Quito el caracter ya utilizado.   
    return;
  }
  fill_tree_sheets(tree->left, charactersList);   // Recursion en ambos sub-arboles
  fill_tree_sheets(tree->right, charactersList);
}

HList complete_tree(char *serializedString, int len)
{
  SList structureList = slist_string_to_list(serializedString, len - ASCII_CHARACTERS ); //Paso string-estructura a lista.
  HList treeStructure = parse_tree(&structureList);
  SList charactersList = slist_characters_string_to_list(&serializedString[len - ASCII_CHARACTERS ], ASCII_CHARACTERS ); //Paso string-caracteres a lista.
  
  fill_tree_sheets(treeStructure, &charactersList); //Completamos el arbol

  slist_destroy(charactersList);
  slist_destroy(structureList);

  return treeStructure;
}


char *decode_text(char *encodedText, HList huffmanTree, int lenEncodedText, int *lenDecodedText) 
{
  int sz = 20, size = sz;          
  char *txt = encodedText;
  char *txtDec = malloc(size);       //Memoria inicial, (size) bytes.
  HList temp = huffmanTree;
  int count = 0;
  for (int i = 0; i < lenEncodedText; i++) {  //Recorro el texto codificado.
    if (hlist_sheet(temp)) {           

      if (count == size) {      //Si alcanzo el limite de la memoria:
        size += sz;
        txtDec = realloc(txtDec, size); //Aumento la memoria de [txtDec] (sz) bytes.
      } 

      txtDec[count] = temp->data.character;  //Agrego el caracter a [txtDec[count]]
      count++;
      temp = huffmanTree; //Inicio desde la raiz nuevamente.
    }

    if (txt[i] == '1')
      temp = temp->right;
    else
      temp = temp->left;
  }

  *lenDecodedText = count;

  return txtDec;
}
