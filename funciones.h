#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipos de funciones;
int histograma(char entrada[20], char salida[20]);
int imprimirHistograma(int histograma[], char sal[20]);
int ecualizar(int histograma[], char encabezado[50], char entr[20], long int lar, int enc);
int maximo(int histograma[]);
int minimo(int histograma[]);

/**
 * [Funcion que genera el histograma de una imagen, leyendo caracter por caracter,
 *  mas adelante imprime el histograma y lo ecualiza]
 * @param  [entrada] [Nombre del archivo de entrada que se recibe por linea de comando]
 * @param  [salida] [Nombre del archivo de salida que se recibe por linea de comando]
 * @return        [Regresa 0 si todo funciono correctamente o hay error en el archivo]
 */
int histograma(char entrada[20], char salida[20]) {

  unsigned char imprime, aux;
  long int largo = 0;
  char encabezado[50] = { 0 };
  int histogram[256] = { 0 };
  int i = 0, valorMin = 0, en = 0, contador = 0, eq = 0;

  // Creo archivos de entrada y salida
  FILE *file = fopen(entrada, "r");

  // Asegura que los archivos esten disponibles
  if(!file) {
    printf("Error en el archivo\n");
    return 0;
  }

  // Lee el encabezado del archivo
  while(i < 3) {
    aux = fgetc(file);
    if(aux == '\n') {
      i++;
    }
    encabezado[en] = aux;
    en++;
  }

  // Guardas el encabezado de la imagen
  encabezado[en] = '\0';

  // Te vas al final del archivo
  fseek(file, 0L, SEEK_END);
  // Guardas cuantos char hay en el archivo
  largo = ftell(file) - en;
  // Regresas al inicio del archivo
  fseek(file, en, SEEK_SET);
  // Copia linea por linea al nuevo archivo
  while (contador != largo) {
    // imprime linea por linea
    imprime = fgetc(file);
    histogram[imprime]++;
    contador++;
  }
  // Cierra archivo
  fclose(file);

  imprimirHistograma(histogram, salida);
  ecualizar(histogram, encabezado, entrada, largo, en);

  return 0;
}

/**
 * [Ecualiza una imagen distribuyendo sus valores con la formula de la recta]
 * @param  histograma [Obtiene el histograma completo de la imagen]
 * @param  [encabezado]     [Obtiene el encabezado completo de la imagen]
 * @param  [ent]     [Nombre del archivo de entrada que se recibe por linea de comando]
 * @param  lar        [total de caracteres de la imagen]
 * @param  enc        [largo del encabezado de la imagen]
 * @return            [0 si hay error en el archivo o si el programa funciono correctamente]
 */
int ecualizar(int histograma[], char encabezado[50], char entr[20], long int lar, int enc) {

  int contador = 0, valorMax = 0, valorMin = 0, eq = 0, nuevoHistograma[256] = { 0 };
  unsigned char imprime;

  // Obtienes valores maximos y minimos del inidice de la imagen
  valorMax = maximo(histograma);
  valorMin = minimo(histograma);

  // Genero archivos de entrada y salida
  FILE *file = fopen("ecualizada.raw", "w+");
  FILE *file2 = fopen(entr, "r");

  // Colo mi apuntador al principio de la imagen
  fseek(file2, enc, SEEK_SET);

  while (contador != lar) {
    // imprime linea por linea
    imprime = fgetc(file2);
    // Formula que ecualiza la imagen
    eq = (((int)imprime - valorMin) * 255)/(valorMax - valorMin);
    fprintf(file, "%c", eq);
    nuevoHistograma[eq]++;
    contador++;
  }

  // Imprimo nuevo histograma
  imprimirHistograma(nuevoHistograma, "histograma_ecualizado.txt");

  // Cierras los archivos
  fclose(file);
  fclose(file2);

  return 0;
}

/**
 * [Imprime el histograma de una imagen]
 * @param  histograma [Obtiene el histograma completo de la imagen]
 * @param  [sal]     [Nombre del archivo de salida que se recibe por linea de comando]
 * @return            [0 si hay error en el archivo o si el programa funciono correctamente]
 */
int imprimirHistograma(int histograma[], char sal[20]) {

  int i = 0;

  FILE *file = fopen(sal, "w");

  if(!file) {
    printf("Error en el archivo\n");
    return 0;
  }

  for(i = 0; i < 256; i++) {
    fprintf(file, "%d\t%d\n", i, histograma[i]);
  }

  fclose(file);

  return 0;
}

/**
 * [Obtiene el valoro maximo del indice en le histograma]
 * @param  histograma [Obtiene el histograma completo]
 * @return            [regresa el valor del indice donde su valor fue != 0]
 */
int maximo(int histograma[]) {

  int i = 255;

  // Lee el histograma hasta que su valor es == 0
  while(histograma[i] == 0) {
    i--;
  }

  return i;
}

/**
 * [Obtiene el valoro minimo del indice en le histograma]
 * @param  histograma [Obtiene el histograma completo]
 * @return            [regresa el valor del indice donde su valor fue != 0]
 */
int minimo(int histograma[]) {

  int i = 0;

  // Lee el histograma hasta que su valor es == 0
  while(histograma[i] == 0) {
    i++;
  }
  return i;
}
