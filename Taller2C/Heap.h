#pragma once
#include "Paquete.h"

class Heap
{
private:
	Paquete** arreglo_paquetes;
	int tamanio_maximo;
	int cantidad_actual;

public:
	Heap(int tamanio_maximo);
	~Heap();
	void insertar_paquete(Paquete* paquete_agregar);
	void eliminar_paquete(int indice);
	void heapify_min(int indice);
	Paquete* retornar_paquete();
	Paquete* extraer_paquete();
	int get_padre(int indice);
	int get_hijo_izq(int indice);
	int get_hijo_der(int indice);
	void imprimir_arreglo();
};

