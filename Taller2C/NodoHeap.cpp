#include "NodoHeap.h"

NodoHeap::~NodoHeap()
{
	delete paquete;
}

NodoHeap::NodoHeap(Paquete* paquete)
{
	this->paquete = paquete;
	this->nodo_izquierdo = nullptr;
	this->nodo_derecho = nullptr;
}

NodoHeap* NodoHeap::get_nodo_izquierdo()
{
	return this->nodo_izquierdo;
}

NodoHeap* NodoHeap::get_nodo_derecho()
{
	return this->nodo_derecho;
}

Paquete* NodoHeap::get_paquete()
{
	return this->paquete;
}

void NodoHeap::set_nodo_izquierdo(NodoHeap* nodo)
{
	this->nodo_izquierdo = nodo;
}

void NodoHeap::set_nodo_derecho(NodoHeap* nodo)
{
	this->nodo_derecho = nodo;
}

void NodoHeap::set_paquete(Paquete* paquete)
{
	this->paquete = paquete;
}
