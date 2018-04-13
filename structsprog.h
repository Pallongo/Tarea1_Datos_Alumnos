typedef struct {
  char sigla[7];
  int semestre; /* 1er o 2do semestre*/
} curso;
typedef struct {
  char rolEstudiante[12];
  char siglaCurso[7];
  int nota;
} nota;


typedef struct
{
  char Sigla[7];
  int NotaRamo;
} Ramo;

struct Alumno
{
  char *RolUSM;
  char *NombreApellido;
  char *Apellido;
  char *Ingreso;
  int aproboTodoPrimerSemestre; // 0 = reprobado
  int aproboTodoSegundoSemestre; // 1 = aprobado
  struct Alumno *nextAlumno;
};
