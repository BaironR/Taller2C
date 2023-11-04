#include "NodoHeap.h"

/*
Constructor del nodo del heap.
El atributo de paquete lo inicializa por el que recibe por parámetro.
*/

NodoHeap::NodoHeap(Paquete* paquete)
{
	this->paquete = paquete;
}

/*
Destructor del nodo de heap.
Recursivamente destruye el paquete contenido.
*/
NodoHeap::~NodoHeap()
{
	delete paquete;
}

/*
Retorna el paquete.
*/
Paquete* NodoHeap::get_paquete()
{
	return this->paquete;
}

/*
Designa el paquete, recibido por parámetro.
*/
void NodoHeap::set_paquete(Paquete* paquete)
{
	this->paquete = paquete;
}
