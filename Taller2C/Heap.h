#pragma once
#include "Paquete.h"
#include "NodoHeap.h"

/*
La clase del Min Heap, que realiza las entregas de todos los paquetes.
Posee un arreglo de nodos para el heap (solo poseen el paquete), un tamaño máximo y la cantidad
actual de nodos en el heap.

Como es un min heap, el dato padre será menor a sus dos hijos (o al único hijo, si no tiene un segundo).
La raíz tiene el menor dato de todo el heap. IMPORTANTE: El criterio de organización para el min heap es 
EL TIEMPO DE ENTREGA DE UN PAQUETE. O sea, la raíz tiene el menor tiempo de entrega y es el próximo a ser
entregado.

Al insertar todos los paquetes provenientes del AVL, se realiza un orden entre todos los paquetes para que
se cumpla la condición de heap en todo el árbol, mediante el tiempo de entrega del paquete.
Luego, el heap se elimina progresivamente, retirando la raíz hasta terminar.
*/




class Heap
{
private:

	/*
	Variables privadas del heap:
	El arreglo con los nodos del heap, el tamaño máximo de nodos que almacenará,
	y la cantidad actual de nodos, que siempre se inicializa en 0, y su límite es la tamaño máximo.
	*/
	NodoHeap** arreglo_nodos;
	int tamanio_maximo;
	int cantidad_actual;

public:

	/*
	Métodos públicos del heap:
	Constructor (con el tamaño máximo, como parámetro) y destructor del heap, insertar un paquete,
	min-heapify (método para reordenar los nodos en base al tiempo de entrega, para que se cumpla la condición 
	de min-heap), extraer el paquete de la raíz, obtención de índices (índice del nodo padre, índice del hijo izquierdo,
	índice del hijo derecho), y obtener la cantidad actual de nodos en el heap.
	*/

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

