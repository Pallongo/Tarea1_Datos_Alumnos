#include <stdio.h>
#include <stdlib.h>


struct Nodo {
  int data;
  struct Nodo *nextNodo;
};

struct listaNodos {
  struct Nodo *head;
};

struct listaNodos *inicializarLista()
{
  struct listaNodos *lsstt = (struct listaNodos*)malloc(sizeof(struct listaNodos));
  lsstt->head = NULL;
  return lsstt;
}


struct Nodo *crearNodo(int dato)
{
    struct Nodo *nodoActual = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodoActual->data = dato;
    nodoActual->nextNodo = NULL;
    return nodoActual;
}

void AddDato(struct listaNodos *list, int dataEntregado)
{
  struct Nodo *current = NULL;


  if (list->head == NULL)
  {
    list->head = crearNodo(dataEntregado);
  }
  else
  {
    current = list->head;
    while(current->nextNodo != NULL)
    {
      current = current->nextNodo;
    }
      current->nextNodo = crearNodo(dataEntregado);
  }

}

void printDatosDeNodos(struct listaNodos *lsst)
{
  struct Nodo *current = lsst->head;
  if (current == NULL)
  {
    return;
  }
  while (current->nextNodo != NULL)
  {
    printf("Numero inicial: %d\n", current->data);
    current = current->nextNodo;
  }
}



int main()
{
  struct listaNodos *listaDeNodos = inicializarLista();
  AddDato(listaDeNodos, 2);
  AddDato(listaDeNodos, 3);
  AddDato(listaDeNodos, 2);
  AddDato(listaDeNodos, 5);
  AddDato(listaDeNodos, 8);
  printDatosDeNodos(listaDeNodos);



  return 0;
}
