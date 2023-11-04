#pragma once
#include "Paquete.h"
#include "NodoHeap.h"

class Heap
{
private:
	NodoHeap** arreglo_nodos;
	int tamanio_maximo;
	int cantidad_actual;

public:
	Heap(int tamanio_maximo);
	~Heap();
	void insertar_paquete(Paquete* paquete_agregar);
	void heapify_min(int indice);
	Paquete* extraer_paquete();
	int get_padre(int indice);
	int get_hijo_izq(int indice);
	int get_hijo_der(int indice);
	int get_cantidad_actual();
};

