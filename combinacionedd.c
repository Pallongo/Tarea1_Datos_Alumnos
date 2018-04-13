#include <stdlib.h>
#include <stdio.h>
#include "functionsprog.h"


int main()
{
  //VARIABLES
  //NUMERO DE ESTUDIANTES
  int numberOfStudents;

  //PUNTEROS A VARIABLES
  int *ptrEstudiantes;


  //ASIGNACION DE PUNTEROS A VARIABLES
  ptrEstudiantes = &numberOfStudents;


  //DECLARACION DE STRUCTS ALUMNOS
  struct Alumno *alumnos;//[numberOfStudents];

  //PROCESAMIENTO DE DATOS
  //setNumberofAlumnos("alumnos.txt", ptrEstudiantes);
  //alumnos = setDataAlumnos("alumnos.txt", alumnos);
  alumnos = crearListaDeAlumnos();

  //leerDatosAlumnos("alumnos.txt", getAlumnosLenght("alumnos.txt"));
  loadAlumnosData("alumnos.txt", getAlumnosLenght("alumnos.txt"));
  printAlumnoData("Alejandro", "Saldias");
  printAlumnoData("Abdel", "Tampe");

  //printf("%d", numberOfStudents);
  //printf("%d", numberOfStudents);


  //createAlumnosData("alumnos.txt", alumnos, numberOfStudents);
  //setAlumnosData("alumnos.txt", alumnos, numberOfStudents);


  return 0;
}
