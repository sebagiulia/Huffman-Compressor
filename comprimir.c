#include "comprimir.h"
#include "io.h"

#define CARACTERES_TOTALES 256



/////////////////////////////////////////// CREAR ARREGLO DE FRECUENCIAS ////////////////////////////////////////////////

unsigned char ascii(int n)
{
  unsigned char c = n;
  return c;
}

int numAscii(unsigned char c)
{
  int n = c;
  return n;
}

Par *inicializar_arregloFrec()
{
  Par *arregloFrec = malloc(sizeof(Par) * CARACTERES_TOTALES);
  for (int i = 0; i < CARACTERES_TOTALES; i++) {
    arregloFrec[i].frec = 0;
    arregloFrec[i].caracter = ascii(i);
  }
  return arregloFrec;
}

Par *calculador_frecuencias(char *textoOriginal, int lenTexto)
{
  Par *arregloFrec = inicializar_arregloFrec();
  for (int i = 0, pos; i < lenTexto; i++) {
    pos = numAscii(textoOriginal[i]);
    arregloFrec[pos].frec++;
  }
  return arregloFrec;
}

/////////////////////////////////////////// CREAR LISTA ORDENADA ////////////////////////////////////////////////////

int comparar_frecuencias(Par dato1, Par dato2)
{
  if (dato1.frec > dato2.frec)
    return 1;
  if (dato1.frec == dato2.frec)
    return 0;
  return -1;
}

HList crear_lista_ord(Par *arregloFrec)
{
  HList lista = hlist_crear();
  int contador = 0;
  while (contador < CARACTERES_TOTALES) {
    lista = hlist_insertar_ordenado(lista, arregloFrec[contador], (FuncionComparadora)comparar_frecuencias);
    contador++;
  }
  return lista;
}

/////////////////////////////////////// FORMAR ARBOL DE HUFFMAN ////////////////////////////////////////////////////

HList formar_arbol_Huffman(HList listaOrdenada)
{
  if (hlist_vacia(listaOrdenada))
    return listaOrdenada;
  while (!hlist_vacia(listaOrdenada->next)) {
    HNode *nodo1 = listaOrdenada, *nodo2 = nodo1->next;
    int sumaFrecs = nodo1->data.frec + nodo2->data.frec;
    Par parNuevo;
    parNuevo.frec = sumaFrecs;
    parNuevo.caracter = ' ';
    HNode *nodoNuevo = hlist_formar_arbol(parNuevo, nodo1, nodo2);
    listaOrdenada = hlist_pop(listaOrdenada); // desconecto nodo1
    listaOrdenada = hlist_pop(listaOrdenada); // desconecto nodo2
    listaOrdenada = hlist_insertar_nodo_ordenado(listaOrdenada, nodoNuevo, (FuncionComparadora)comparar_frecuencias);
  }
  return listaOrdenada;
}

///////////////////////////////////// CREAR ARREGLO DE CODIFICACIONES //////////////////////////////////////////////////////////

void agregar_codigo_caracter(Par dato, Codificacion *arregloCodific, SList listaBits)
{
  int pos = numAscii(dato.caracter);
  int len = slist_len(listaBits);
  arregloCodific[pos].codif = malloc(len);
  arregloCodific[pos].lenCodif = len;
  arregloCodific[pos].caracter = dato.caracter;
  slist_lista_a_string(arregloCodific[pos].codif, listaBits);
}


void asignar_codigos(HList arbol, Codificacion *arregloCodific, SList listaBits)
{
  if (hlist_vacia(arbol)) //Caso Base
    return;

  asignar_codigos(arbol->left, arregloCodific, slist_agregar_final(listaBits, 0)); //Recursion
  
  if (hlist_hoja(arbol))
    agregar_codigo_caracter(arbol->data, arregloCodific, listaBits);
  
  listaBits = slist_desapilar(listaBits);

  asignar_codigos(arbol->right, arregloCodific, slist_agregar_final(listaBits, 1)); //Recursion
  
  listaBits = slist_desapilar(listaBits);
}


Codificacion *codificar_datos(HList arbolHuffman)
{
  Codificacion *arregloCodific = malloc(sizeof(Codificacion) * CARACTERES_TOTALES);
  SList list = slist_crear();
  asignar_codigos(arbolHuffman, arregloCodific, list);
  slist_destruir(list);
  return arregloCodific;
}

////////////////////////////////////// CREAR TEXTO BINARIO //////////////////////////////////////////////////////

void copiar_cadena(char *direccion, char *string, int len)
{
  for (int i = 0; i < len; i++) 
    direccion[i] = string[i];
}

char *crear_texto_binario(Codificacion *arregloCodific , char *textoOriginal, int largoTexto, int *largoTextoCodificado)
{
  int sz = 500, size = sz;      //Tamaño inicial del texto codificado (size)
  char *textoCodificado = malloc(size);
  int contador = 0, pos = 0, i = 0;

  while(contador <= largoTexto){
    
    if (i >= size - 30) {       
      size += sz;
      textoCodificado = realloc(textoCodificado, size); //Aumento de a (sz) bytes el tamaño del arreglo
    }

    pos = numAscii(textoOriginal[contador]);  //Numero ascii del caracter asociado

    char *codigoCaracter = arregloCodific[pos].codif; 
    int largoCodigoCaracter =  arregloCodific[pos].lenCodif;
    char *direccionEnTextoCodificado = &textoCodificado[i]; // Direccion a colocar el codigo del caracter

    copiar_cadena(direccionEnTextoCodificado, codigoCaracter, largoCodigoCaracter);

    i += largoCodigoCaracter; //Reubicacion de posicion en textoCodificado
    contador++;
  }
  *largoTextoCodificado = i;
  return textoCodificado;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void serializar_estructura(HList arbolDeHuffman, SList *lista) 
{
  if (hlist_hoja(arbolDeHuffman)) {          //Caso base
    *lista = slist_agregar_final(*lista, 1);
  } else {
    *lista = slist_agregar_final(*lista, 0);
    serializar_estructura(arbolDeHuffman->left, lista);
    serializar_estructura(arbolDeHuffman->right, lista);
  }
}

void slist_listaCaracteres_a_string(char *string, SList list)
{
  SNodo *temp = list;
  for (int i = 0; temp != NULL; temp = temp->sig, i++) {
    string[i] = ascii(temp->dato);
  }
}

void agregar_numAscii_caracter(Par par, SList *lista) 
{
  *lista = slist_agregar_final(*lista, numAscii(par.caracter));
}

void agregar_caracteres(HList arbolDeHuffman, SList *listaCaracteres)
{ 
  if (hlist_vacia(arbolDeHuffman)) return;
  agregar_caracteres(arbolDeHuffman->left, listaCaracteres);
  if (hlist_hoja(arbolDeHuffman))
    agregar_numAscii_caracter(arbolDeHuffman->data, listaCaracteres);
  agregar_caracteres(arbolDeHuffman->right, listaCaracteres);
}


char *serializar_arbol(HList arbolDeHuffman, int *largoString)
{
  SList listaEstructura = slist_crear();                    //Serializacion Estructura (1)      
  serializar_estructura(arbolDeHuffman, &listaEstructura);
  int largoListaEstruct = slist_len(listaEstructura);

  SList listaCaracteres = slist_crear();                    //Serializacion Caracteres (2)
  agregar_caracteres(arbolDeHuffman, &listaCaracteres);
  int largoListaCaracteres = slist_len(listaCaracteres);

  *largoString = largoListaEstruct + largoListaCaracteres;   //Union de (1) y (2)
  char *stringSerio = malloc(*largoString);
  slist_lista_a_string(stringSerio, listaEstructura);
  slist_listaCaracteres_a_string(&stringSerio[largoListaEstruct], listaCaracteres);
  return stringSerio; 
}

//void imprimir_cadena(char *cadena, int len)
//{
//  for (int i = 0; i < len; i++)
//    printf("%c", cadena[i]);
//  printf("\n");
//}



//for (int i = 0; i < CARACTERES_TOTALES; i++) {
//     printf(" %d [ %c ] -- [%d] -- ", i, arregloCodific[i].caracter, arregloCodific[i].lenCodif);
//     imprimir_cadena(arregloCodific[i].codif, arregloCodific[i].lenCodif);
// }





/*
assert(arregloFrec[99].frec == 4);       // letra c   
assert(arregloFrec[72].caracter == 'H'); // letra H
assert(arregloFrec[65].frec == 0);       // letra A



printf("\n\n");
imprimir_cadena(textoCodificado, largoTextoCodificado);

printf("\n\n");
imprimir_cadena(textoCodificadoImplode, largoTextoCodificadoImplode);
*/
/*

*/