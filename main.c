#include "comprimir.h"
#include "io.h"
#define CARACTERES_TOTALES 256

int main()
{

  ////////////////////////////////////// comprimir ////////////////////////////////////////////////////////////
  int largoTexto = 0;
  char pathTextoEntrada[] = "f.txt";
  char *buffer = readfile(pathTextoEntrada, &largoTexto);

  Par *arregloFrec = calculador_frecuencias(buffer, largoTexto); //Creo el arreglo de frecuencias (arregloFrec) 

  HList listaOrdenada = crear_lista_ord(arregloFrec); //Creo la lista ordenada segun frecuencias (listaOrdenada) 

  HList arbolHuffman = formar_arbol_Huffman(listaOrdenada); // La lista ordenada pasa a ser un arbol de huffman (arbolHuffman)
  Codificacion *arregloCodific = codificar_datos(arbolHuffman);

  
  int largoTextoCodificado = 0;
  char *textoCodificado = crear_texto_binario(arregloCodific, buffer, largoTexto, &largoTextoCodificado); //Creo el texto codificado 
  
  int largoTextoCodificadoImplode = 0;
  char *textoCodificadoImplode = implode(textoCodificado, largoTextoCodificado, &largoTextoCodificadoImplode);//Implosiono el texto codificado
  
  int largoStringArbolSerializado = 0;
  char *stringArbolSerializado = serializar_arbol(arbolHuffman, &largoStringArbolSerializado); //Creo el texto del arbol de Huffman serializado

  char pathTextoCodificadoImplode[] = "f.txt.hf", pathStringArbolSerializado[] = "f.txt.arbol";

  writefile(pathTextoCodificadoImplode, textoCodificadoImplode, largoTextoCodificadoImplode);
  writefile(pathStringArbolSerializado, stringArbolSerializado, largoStringArbolSerializado);

  for(int i = 0; i < CARACTERES_TOTALES; i++) 
    free(arregloCodific[i].codif);
  hlist_destruir(arbolHuffman);
  free(arregloFrec);
  free(buffer);
  free(textoCodificado);
  ////////////////////////////////////////////////////// descomprimir ///////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  return 0;
}