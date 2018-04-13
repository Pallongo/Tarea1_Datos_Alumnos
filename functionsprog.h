
#include <stdlib.h>
#include <stdio.h>
#include "structsprog.h"
#include <string.h>


int listCreated = 0;

struct Alumno* Current;
struct Alumno* Head;
struct Alumno* Last;
int cnt = 0;

//CREA LA LINKED LIST
struct Alumno *crearListaDeAlumnos()
{
  struct Alumno *ptr = (struct Alumno*)malloc(sizeof(struct Alumno));

  if(ptr != NULL && listCreated == 0)
  {
    printf("-> Lista de alumnos creada.\n");
    listCreated = 1;
  }
  //ptr->nextAlumno = Head;
  Current = Head = Last = ptr;


  return ptr;
}


//AGREGA UN ALUMNO A LA LINKED LIST
struct Alumno *addAlumno(char *Rol, char *Nombres, char *Appe, char *AnnoIngreso, int aprobPrimer, int aprobSegundo)
{
    if (listCreated == 0)
    {
      printf("La lista de alumnos no se ha creado aun.\n");
      return NULL;
    }

    struct Alumno *ptr = (struct Alumno*)malloc(sizeof(struct Alumno));

    ptr->RolUSM = Rol;
    ptr->NombreApellido = Nombres;
    ptr->Apellido = Appe;
    ptr->Ingreso = AnnoIngreso;
    ptr->aproboTodoPrimerSemestre = aprobPrimer;
    ptr->aproboTodoSegundoSemestre = aprobSegundo;

    printf("-> Alumno %s %s, de rol %s agregado.\n", ptr->NombreApellido, Appe, ptr->RolUSM);

    Current = Current->nextAlumno = ptr;
    Last = Last->nextAlumno;
    cnt++;

    return ptr;
}


//BUSCA UN ALUMNO DENTRO DE LA LINKED LIST
struct Alumno *buscarAlumno(char *Nombre, char *Appe)
{
  //struct Alumno *ptr = Head;
  struct Alumno *ptr = Head->nextAlumno;

  int AlumnoEncontrado = 0; // 0 = false, 1 = true

  while(ptr != NULL)
  {
    if ((ptr->NombreApellido == Nombre) && (ptr->Apellido == Appe))
    {
      AlumnoEncontrado = 1;
      break;
    }
      printf("%s\n", ptr->RolUSM);
      ptr = ptr->nextAlumno;
  }

  if(AlumnoEncontrado == 1)
  {
    return ptr;
  }
  else {
    return NULL;
  }

}

//IMPRIME LOS DATOS DE UN ALUMNO - ES PARA PRUEBAS
struct Alumno *printAlumnoData(char *Nombre, char *Appe)
{

  struct Alumno *ptr;

  ptr = buscarAlumno(Nombre, Appe);

  if (ptr != NULL)
  {
    printf("-> %s tiene el rol : %s \n", Nombre, ptr->RolUSM);
  }
  else {
    printf("-> Alumno no encontrado.\n");
  }
}

//CARGA LOS DATOS DE ALUMNO.TXT
void loadAlumnosData(char *TextFile, int largo)
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

    addAlumno(ROLUSM, NombreAP, Apellido, AnnoDeIngreso, 0, 0);


    contador++;
  }
}

int getAlumnosLenght(char *TextFile)
{

  //ABRIMOS EL ARCHIVO
  FILE *fp;
  fp = fopen(TextFile, "r");

  //VARIABLES PARA POSTERIOR USO
  int ch; // CHAR ACTUAL LEIDO
  int lenline = 0; // TAMAÑO DE LINEA

  //CODIGO
  //OBTIENE EL NUMERO DE ALUMNOS Y LO ALMACENA EN LA VARIABLE
  int numeroTotalDeAlumnos;
  char numeroalumnos[6];

  while (ch != '\n') {
    ch = fgetc(fp);
    numeroalumnos[lenline] = ch;
    lenline++;
  }
  sscanf(numeroalumnos, "%d", &numeroTotalDeAlumnos);
  //----------
  //----------
  //----------
  //----------

  return numeroTotalDeAlumnos;

}















/*
void createAlumnosData(char *TextFile, Alumno* alumni, int alumniLength)
{
  FILE *fp;
  fp = fopen(TextFile, "r");

  char linea[256];

  printf("Se ha llegado");

  while(fgets(linea, sizeof(linea), fp))
  {
      char datos[4][32];
      char rol[12];
      char name[32];
      char lastname[32];
      int ingreso;

      char actual;

      for (int i = 0; i < alumniLength; i++)
      {
        int contador = 0;
        while ((actual = fgetc(fp))!= ' ')
        {
          datos[i][contador] = actual;
          contador++;
        }
      }

      printf("%s", datos[1]);
  }
}
*/
/*
void setAlumnosData(char *TextFile, Alumno* alumni, int alumniLength)
{
  FILE *fp;
  fp = fopen(TextFile, "r");

  Alumno *alumnado = (Alumno*)malloc(sizeof(Alumno)*alumniLength);

  char buffer[300];
  char *ptrToBuffer;
  ptrToBuffer = buffer;
  int contadorDeAlumnos = 0;

  while (fgets(buffer, 300, fp) != NULL)
  {
    printf("%s", buffer);
    char rol[12];
    char name[60];
    char lastname[60];
    int ingreso;

    int largoDeLinea;

    for (int i  = 0; i < 200; i++)
    {
      if (&buffer[i] != NULL) largoDeLinea++;
    }

    int totalDeEspacios = 3;
    int contadorEspacios = 0;

     char palabra[30];
     int contadorIndex = 0;

     for (int i = 0; i < 30; i++)
     {
       if(buffer[i] != ' ')
       {
         rol[i] = buffer[i];
         contadorIndex++;
       }
       else
       {
         break;
       }
    }

    for (int i = 0; i < 30; i++)
    {
      if(buffer[i+contadorIndex+1] != ' ')
      {
        name[i] = buffer[i+contadorIndex+1];
        contadorIndex++;
      }
      else
      {
        break;
      }
    }

    char annoIngreso[10];
    for (int i = 0; i < 30; i++)
    {
      if(buffer[i+contadorIndex+1] != ' ')
      {
        annoIngreso[i] = buffer[i+contadorIndex+1];
        contadorIndex++;
      }
      else
      {
        break;
      }
    }

    sscanf(annoIngreso, "%d", &ingreso);
    printf("%d", largoDeLinea);

    alumnado[contadorDeAlumnos]->RolUSM = ingreso;

    //size_t t = sizeof(buffer);


  }
}
*/
