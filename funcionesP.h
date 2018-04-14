#include <stdlib.h>
#include <stdio.h>
#include "structsprog.h"
#include <string.h>


struct ListaAlumnos *crearListaDeAlumnos()
{
  struct ListaAlumnos *listaL = (struct ListaAlumnos*)malloc(sizeof(struct ListaAlumnos));
  listaL->head = NULL;
  return listaL;
}

struct Alumno *CrearNodo(char *Rol, char *Nombres, char *Appe, char *AnnoIngreso, int aprobPrimer, int aprobSegundo)
{
    struct Alumno *current = (struct Alumno*)malloc(sizeof(struct Alumno));
    strcpy(current->RolUSM, Rol);
    strcpy(current->NombreApellido, Nombres);
    strcpy(current->Apellido, Appe);
    strcpy(current->Ingreso, AnnoIngreso);
    current->aproboTodoPrimerSemestre = aprobPrimer;
    current->aproboTodoSegundoSemestre = aprobSegundo;
    /*
    current->NombreApellido = Nombres;
    current->Apellido = Appe;
    current->Ingreso = AnnoIngreso;
    current->aproboTodoPrimerSemestre = aprobPrimer;
    current->aproboTodoSegundoSemestre = aprobSegundo;
    */
    current->nextAlumno = NULL;
    return current;
}

void displayDataAlumnos(struct ListaAlumnos *listaL) {
  struct Alumno *current = listaL->head;
  if(listaL->head == NULL)
    return;
  while(current->nextAlumno != NULL){
    printf("Nombre del alumno: %s, cuyo rol es %s\n", current->NombreApellido, current->RolUSM);
    current = current->nextAlumno;
  }
}

void addAlumno(struct ListaAlumnos *listaL, char *Rol, char *Nombres, char *Appe, char *AnnoIngreso, int aprobPrimer, int aprobSegundo)
{
    struct Alumno *current = NULL;

    if(listaL->head == NULL){
      listaL->head = CrearNodo("test", "test", "test", "test", 0,0);
    }
    else
    {
      current = listaL->head;
      while(current->nextAlumno != NULL)
      {
        current = current->nextAlumno;
      }
      current->nextAlumno = CrearNodo(Rol, Nombres, Appe, AnnoIngreso, 0, 0);

    }


}


void loadAlumnosData(char *TextFile, int largo, struct ListaAlumnos *listaL)
{
  FILE *fp;
  fp = fopen(TextFile, "r");

  char lineaUNO;
  fgets(&lineaUNO, 10, fp);

  const char *delimeter = " ";
  char *token;
  char *datoActual;

  int contador = 0;
  while (contador < largo)
  {
    char ROLUSM[12];
    char NombreAP[30];
    char AnnoDeIngreso[14];
    char Apellido[30];

    char linea[256];
    fgets(linea, 256, fp);
    int dataAmodificar = 0;  // ROL 0, nombre 1, Apellido 2, Año ingreso 3;
    datoActual = strtok(linea, delimeter);

    while (datoActual != NULL)
    {
      switch (dataAmodificar)
      {
        case 0:
          memcpy(ROLUSM, datoActual, sizeof(ROLUSM));
        case 1:
          memcpy(NombreAP, datoActual, sizeof(NombreAP));
        case 2:
          memcpy(Apellido, datoActual, sizeof(Apellido));
        case 3:
          memcpy(AnnoDeIngreso, datoActual, sizeof(AnnoDeIngreso));
      }
      datoActual = strtok(NULL, delimeter);
      dataAmodificar++;
    }


    addAlumno(listaL, ROLUSM, NombreAP, Apellido, AnnoDeIngreso, 0, 0);
    contador++;

  }

  fclose(fp);
}
