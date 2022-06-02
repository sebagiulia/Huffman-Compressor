#include "decompression.h"
#include <assert.h>

#define ASCII_CHARACTERS  256


HList parse_tree(SList *structureList) 
{
  if ((*structureList)->data) //Si es igual a 1
    return hlist_create_sheet();
  
  HList tree = hlist_create_sheet();

  *structureList = slist_dequeue(*structureList);
  tree->left = parse_tree(structureList);
                                                   // Casos recursivos sobre los sub-arboles (left and right)
  *structureList = slist_dequeue(*structureList);
  tree->right = parse_tree(structureList);

  return tree;
}

void fill_tree_sheets(HList tree, SList *charactersList)
{
  if (hlist_sheet(tree)) {                                    // Caso base
    tree->data.character = ascii((*charactersList)->data);
    *charactersList = slist_dequeue(*charactersList);       
    return;
  }
  fill_tree_sheets(tree->left, charactersList);   // Recursion en ambos sub-arboles
  fill_tree_sheets(tree->right, charactersList);
}

HList complete_free(char *serializedString, int len)
{
  SList structureList = slist_string_to_list(serializedString, len - ASCII_CHARACTERS );
  HList treeStructure = parse_tree(&structureList);
  SList charactersList = slist_characters_string_to_list(&serializedString[len - ASCII_CHARACTERS ], ASCII_CHARACTERS );
  
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
  for (int i = 0; i < lenEncodedText; i++) {
    if (hlist_sheet(temp)) {           

      if (count == size) {
        size += sz;
        txtDec = realloc(txtDec, size); //Aumento la memoria de [txtDec] (sz) bytes.
      }

      txtDec[count] = temp->data.character;
      count++;
      temp = huffmanTree;
    }

    if (txt[i] == '1')
      temp = temp->right;
    else
      temp = temp->left;
  }

  *lenDecodedText = count;

  return txtDec;
}
