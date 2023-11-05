#pragma once
#include "Paquete.h"
#include "NodoHeap.h"

/*
La clase del Min Heap, que realiza las entregas de todos los paquetes.
Posee un arreglo de nodos para el heap (solo poseen el paquete), un tama�o m�ximo y la cantidad
actual de nodos en el heap.

Como es un min heap, el dato padre ser� menor a sus dos hijos (o al �nico hijo, si no tiene un segundo).
La ra�z tiene el menor dato de todo el heap. IMPORTANTE: El criterio de organizaci�n para el min heap es 
EL TIEMPO DE ENTREGA DE UN PAQUETE. O sea, la ra�z tiene el menor tiempo de entrega y es el pr�ximo a ser
entregado.

Al insertar todos los paquetes provenientes del AVL, se realiza un orden entre todos los paquetes para que
se cumpla la condici�n de heap en todo el �rbol, mediante el tiempo de entrega del paquete.
Luego, el heap se elimina progresivamente, retirando la ra�z hasta terminar.
*/




class Heap
{
private:

	/*
	Variables privadas del heap:
	El arreglo con los nodos del heap, el tama�o m�ximo de nodos que almacenar�,
	y la cantidad actual de nodos, que siempre se inicializa en 0, y su l�mite es la tama�o m�ximo.
	*/
	NodoHeap** arreglo_nodos;
	int tamanio_maximo;
	int cantidad_actual;

public:

	/*
	M�todos p�blicos del heap:
	Constructor (con el tama�o m�ximo, como par�metro) y destructor del heap, insertar un paquete,
	min-heapify (m�todo para reordenar los nodos en base al tiempo de entrega, para que se cumpla la condici�n 
	de min-heap), extraer el paquete de la ra�z, obtenci�n de �ndices (�ndice del nodo padre, �ndice del hijo izquierdo,
	�ndice del hijo derecho), y obtener la cantidad actual de nodos en el heap.
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

