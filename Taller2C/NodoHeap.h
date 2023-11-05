#pragma once
#include "Paquete.h"

/*
Clase del nodo del Min Heap.
Solamente almacena el paquete, posee su constructor y destructor,
y su get-set para el paquete.
*/


class NodoHeap
{
private:
	Paquete* paquete; //Paquete almacenado.
public:

	/*
	Métodos públicos para el nodo del min heap.
	Constructor y destructor del heap, obtener y designar el paquete.
	*/

	~NodoHeap(); 
	NodoHeap(Paquete* paquete);
	Paquete* get_paquete();
	void set_paquete(Paquete* paquete);
};

