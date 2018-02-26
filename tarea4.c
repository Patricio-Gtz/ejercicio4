#include "funciones.h"


int main(int argc, char const *argv[]) {

  char argumento1[20];
  char argumento2[20];

  if(argc < 2) {
    printf("Muy pocos argumentos\n");
    return 0;
  } else if (argc > 3) {
    printf("Muchos argumentos\n");
    return 0;
  }

  sscanf(argv[1], "%s", argumento1);
  sscanf(argv[2], "%s", argumento2);

  histograma(argumento1, argumento2);
  return 0;
}
