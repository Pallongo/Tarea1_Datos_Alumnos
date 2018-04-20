#include <stdlib.h>
#include <stdio.h>
#include "funcionesP.h"
#include <time.h>


int main()
{
  //VARIABLES PARA MEDIR EL TIEMPO DE EJECUCIÓN
  clock_t start_t, end_t, total_t;
  start_t = clock();

  //LINKED LIST OF STUDENTS CREATED
  struct ListaAlumnos *list = crearListaDeAlumnos();

  //LOAD STUDENT DATA
  loadAlumnosData("alumnos.txt", list);

  //TEST DATA FOR DEBBUGING
  displayDataAlumnos(list);
  printf("-------------------\n");

  //GENERATE TEXT FILE
  generarTextoResultado(list);
  printf("Archivos de texto generados\n");
  printf("-------------------\n");

  //CALCULATE ALGORITHM SPEED
  end_t = clock();
  printf("El algoritmo se ha ejecutado a una velocidad de %lf [segundos].\n", (double)(end_t - start_t)/CLOCKS_PER_SEC);

  return 0;
}
