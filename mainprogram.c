#include <stdlib.h>
#include <stdio.h>
#include "funcionesP.h"


int main()
{
  struct ListaAlumnos *list = crearListaDeAlumnos();
  loadAlumnosData("alumnos.txt", 5, list);
  displayDataAlumnos(list);

  return 0;
}
