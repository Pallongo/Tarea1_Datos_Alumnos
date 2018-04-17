#include <stdlib.h>
#include <stdio.h>
#include "funcionesP.h"


int main()
{
  struct ListaAlumnos *list = crearListaDeAlumnos();
  struct listaRamos *rlist = crearListaDeRamos();

  loadAlumnosData("alumnos.txt", 5, list);
  displayDataAlumnos(list);
  displayNotasDat(4*3);
  displayCursosDat();

  return 0;
}
