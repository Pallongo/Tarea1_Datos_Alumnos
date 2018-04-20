#include <stdlib.h>
#include <stdio.h>
#include "structsprog.h"
#include <string.h>

//(< y >)


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
      listaL->head = CrearNodo(Rol, Nombres, Appe, AnnoIngreso, 0, 0);
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


void loadAlumnosData(char *TextFile, struct ListaAlumnos *listaL)
{
  FILE *fp;
  fp = fopen(TextFile, "r");

  char lineaUNO[4];
  int numerOfStudents;
  fgets(lineaUNO, 4, fp);
  sscanf(lineaUNO, "%d", &numerOfStudents);

  const char *delimeter = " ";
  char *token;
  char *datoActual;

  int contador = 0;
  while (contador < numerOfStudents + 1)
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

void displayCursosDat()
{
  FILE *fp = fopen("cursos.dat", "rb");

  curso read_cursos;
  int numeroCursos;

  fread(&numeroCursos, sizeof(int), 1, fp);

  for (int i = 0; i < numeroCursos; i++)
  {
    fread(&read_cursos, sizeof(curso), 1, fp);
    printf("%s , %d\n", read_cursos.sigla, read_cursos.semestre);
  }
  fclose(fp);

}


void generarTextoResultado(struct ListaAlumnos *list)
{


  //LOAD CURSOS
  FILE *fileCursos = fopen("cursos.dat", "rb");
  int numeroCursos;
  fread(&numeroCursos, sizeof(int), 1, fileCursos);
  curso read_cursos[numeroCursos];
  int cursosParaAprobarPrimerSemestre = 0;
  int cursosParaAprobarSegundoSemestre = 0;
  for (int i = 0; i < numeroCursos; i++)
  {
    fread(&read_cursos[i], sizeof(curso), 1, fileCursos);
    if (read_cursos[i].semestre == 1)
    {
      cursosParaAprobarPrimerSemestre++;
    }
    else if (read_cursos[i].semestre == 2)
    {
      cursosParaAprobarSegundoSemestre++;
    }
  }
  fclose(fileCursos);


  //LOAD NOTAS
  FILE *fileNotas = fopen("notas.dat", "rb");
  int numeroNotas;
  fread(&numeroNotas, sizeof(int), 1, fileNotas);
  nota read_notas[numeroNotas];

  for (int i = 0; i < numeroNotas; i++)
  {
    fread(&read_notas[i], sizeof(nota), 1, fileNotas);
    //printf("%s , %s, %d\n", read_notas.siglaCurso, read_notas.rolEstudiante, read_notas.nota);
  }
  fclose(fileNotas);


  struct Alumno *current = list->head;
  if(current == NULL)
    return;




  FILE *aprobados1 = fopen("aprobados-s1.txt", "w");
  FILE *aprobados2 = fopen("aprobados-s2.txt", "w");
  //VERIFICAR DATOS
  while (current->nextAlumno != NULL)
  {
      char s1[200];
      char s2[200];
      //int notasObtenidas[numeroCursos];
      int contadorNotas = 0;


      int aprobPR = 0;
      int aprobSG = 0;

      //strcpy(s1, ("Primer Semestre: %s %s %s ", current->NombreApellido, current->Apellido, current->RolUSM));
      //strcpy(s1, "Primer Semestre: ");
      sprintf(s1,"%s %s %s ", current->NombreApellido, current->Apellido, current->RolUSM);
      sprintf(s2,"%s %s %s ", current->NombreApellido, current->Apellido, current->RolUSM);
      //strcat (s1, ("Primer Semestre: %s %s %s ", current->NombreApellido, current->Apellido, current->RolUSM));

      for (int i = 0; i < numeroNotas; i++)
      {
        for (int x = 0; x < numeroCursos; x++)
        {
          /*
          printf("%s", read_notas[i].siglaCurso);
          printf("%s", read_cursos[x].sigla);*/
          if(strcmp(read_notas[i].siglaCurso, read_cursos[x].sigla) == 0)
          {
            if (strcmp(current->RolUSM, read_notas[i].rolEstudiante) == 0)
            {
              if(read_cursos[x].semestre == 1 && read_notas[i].nota > 55)
              {
                char notita[3];
                strcat(s1, read_cursos[x].sigla);
                strcat(s1, " ");
                sprintf(notita, "%d", read_notas[i].nota);
                strcat(s1, notita);
                strcat(s1, " ");
                aprobPR++;
              }
              else if (read_cursos[x].semestre == 2 && read_notas[i].nota > 55)
              {
                char notita[3];
                strcat(s2, read_cursos[x].sigla);
                strcat(s2, " ");
                sprintf(notita, "%d", read_notas[i].nota);
                strcat(s2, notita);
                strcat(s2, " ");
                aprobSG++;
              }
              contadorNotas++;
            }
          }
        }
      }

      if (aprobPR == cursosParaAprobarPrimerSemestre)
      {
        fputs(s1, aprobados1);
        fputs("\n", aprobados1);
      }
      else if(aprobSG == cursosParaAprobarSegundoSemestre)
      {
        fputs(s2, aprobados2);
        fputs("\n", aprobados2);
      }
      current = current->nextAlumno;
  }
  fclose(aprobados1);
  fclose(aprobados2);

}
/*
struct listaRamos *crearListaDeRamos()
{
  struct listaRamos* rm = (struct listaRamos*)malloc(sizeof(struct listaRamos));
  rm->head = NULL;
  return rm;
}*/
