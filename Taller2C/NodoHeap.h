#pragma once
#include "Paquete.h"
class NodoHeap
{
private:
	Paquete* paquete;
	NodoHeap* nodo_izquierdo;
	NodoHeap* nodo_derecho;

public:
	~NodoHeap();
	NodoHeap(Paquete* paquete);
	NodoHeap* get_nodo_izquierdo();
	NodoHeap* get_nodo_derecho();
	Paquete* get_paquete();
	void set_nodo_izquierdo(NodoHeap* nodo);
	void set_nodo_derecho(NodoHeap* nodo);
	void set_paquete(Paquete* paquete);
};

