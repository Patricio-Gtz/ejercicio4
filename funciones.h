#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int histograma(char entrada[20], char salida[20]);
int imprimirHistograma(int histograma[], char sal[20]);
int ecualizar(int histograma[], char encabezado[50], char entr[20], long int lar, int enc);
int maximo(int histograma[]);
int minimo(int histograma[]);

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

  while(i < 3) {
    aux = fgetc(file);
    if(aux == '\n') {
      i++;
    }
    encabezado[en] = aux;
    en++;
  }

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

int ecualizar(int histograma[], char encabezado[50], char entr[20], long int lar, int enc) {

  int contador = 0, valorMax = 0, valorMin = 0, eq = 0, nuevoHistograma[256] = { 0 };
  unsigned char imprime;

  valorMax = maximo(histograma);
  valorMin = minimo(histograma);

  FILE *file = fopen("ecualizada.raw", "w+");
  FILE *file2 = fopen(entr, "r");

  fseek(file2, enc, SEEK_SET);

  fprintf(file, "%s", encabezado);

  while (contador != lar) {
    // imprime linea por linea
    imprime = fgetc(file2);
    eq = (((int)imprime - valorMin) * 255)/(valorMax - valorMin);
    fprintf(file, "%c", eq);
    nuevoHistograma[eq]++;
    contador++;
  }


  imprimirHistograma(nuevoHistograma, "histograma_ecualizado.txt");

  fclose(file);
  fclose(file2);

  return 0;
}

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

int maximo(int histograma[]) {

  int i = 255;

  while(histograma[i] == 0) {
    i--;
  }
  return i;
}

int minimo(int histograma[]) {

  int i = 0;

  while(histograma[i] == 0) {
    i++;
  }
  return i;
}
